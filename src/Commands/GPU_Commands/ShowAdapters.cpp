#include "ShowAdapters.h"

DxFeatures::Command::CmdShowAdapters DxFeatures::Command::CmdShowAdapters::s_instance = DxFeatures::Command::CmdShowAdapters();

std::stringstream DxFeatures::Command::CmdShowAdapters::operator()(ID3D12Device* ptrDevice){
    // Create Output stream
    std::stringstream ss;

    // Return empty stream if already called
    if (m_bCalled)
        return ss;

    // Create Factory
    IDXGIFactory* ptrFactory = nullptr;
    HRESULT hr = S_OK;
    if (FAILED(hr = CreateDXGIFactory(IID_PPV_ARGS(&ptrFactory)))) {
        // Log and return
        ss << "Failed to create DXGI Factory with code " << (int)hr << std::endl;
        return ss;
    }

    // Iterate through gpu adapters
    IDXGIAdapter* ptrAdapter = nullptr;
    UINT adapterIndex = 0;
    while ((hr =ptrFactory->EnumAdapters(adapterIndex, &ptrAdapter)) == S_OK) {
        // = Get and store adapter information =
        // Create and write index
        DxFeatures::Data::AdapterDesc desc;
        desc.index = adapterIndex;

        // Read adapter info
        ptrAdapter->GetDesc(&desc.description);

        // Safe to local vector
        m_vecAdapterInfo.push_back(desc);

        // = Print adapter information =
        // Create WSTR to STR Converter
        std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> wideToNarrowConverter;

        // Print info
        ss << "[GPULIST|" << desc.index << "]" << std::endl;
        ss << "Description: " << wideToNarrowConverter.to_bytes(desc.description.Description) << std::endl;
        ss << "VendorId: " << desc.description.VendorId << std::endl;
        ss << "DeviceId: " << desc.description.DeviceId << std::endl;
        ss << "SubSysId: "  << desc.description.SubSysId << std::endl;
        ss << "Revision: " << desc.description.Revision << std::endl;
        ss << "Video Memory (dedicated): " << desc.description.DedicatedVideoMemory << " Bytes" << std::endl;
        ss << "System Memory (dedicated): " << desc.description.DedicatedSystemMemory << " Bytes" << std::endl;
        ss << "System Memory (shared): " << desc.description.SharedSystemMemory << " Bytes" << std::endl;
        ss << std::endl;

        // = Release adpater =
        ptrAdapter->Release();
        ptrAdapter = nullptr;

        // Increment
        adapterIndex++;
    }

    // Catch any other error than last adapter (aka. 
    if (hr != DXGI_ERROR_NOT_FOUND) {
        // Log and return
        ss << "Faild to enum adapters index " << adapterIndex <<  " with code " << (int)hr << std::endl;
        return ss;
    }

    // Release factory
    ptrFactory->Release();

    // Set as called and return stream
    m_bCalled = true;
    return ss;
}

bool DxFeatures::Command::CmdShowAdapters::createNextDevice(ID3D12Device** ppDevice, UINT* currentIndex){
    // Return if command not called
    if (!m_bCalled)
        return false;
    
    // Release old device
    if (*ppDevice != nullptr) {
        (*ppDevice)->Release();
        *ppDevice = nullptr;
    }

    while (true) {
        (*currentIndex) = m_indexCurrentAdapter;

        // Return false if current adapter was the last one
        if (m_indexCurrentAdapter >= m_vecAdapterInfo.size())
            return false;

        // Continue if current index is Microsoft Basic Render Driver                                                                                      FALSE <- Dont Ignore MS Software renderer
        if (m_vecAdapterInfo[m_indexCurrentAdapter].description.VendorId == 5140 && m_vecAdapterInfo[m_indexCurrentAdapter].description.DeviceId == 140 && FALSE) {
            m_indexCurrentAdapter++;
            (*currentIndex)++;
            continue;
        }

        // Load Adapter
        HRESULT hr = S_OK;
        IDXGIFactory* ptrFactory = nullptr;
        IDXGIAdapter* ptrAdapter = nullptr;
        
        // Create Factory and return if failed
        if (FAILED(hr = CreateDXGIFactory(IID_PPV_ARGS(&ptrFactory)))) {
            return false;
        }

        // Create Adapter
        if (FAILED(hr = ptrFactory->EnumAdapters(m_indexCurrentAdapter, &ptrAdapter))) {
            // Rlease factory and return
            ptrFactory->Release();
            return false;
        }
        
        // Create device
        hr = D3D12CreateDevice(ptrAdapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(ppDevice));

        // Rlease D3D Elemnts (NOT DEVICE)
        ptrAdapter->Release();
        ptrFactory->Release();

        // Increment and return true
        m_indexCurrentAdapter++;
        
        // Check if last call was not sucessfull
        if(FAILED(hr))
            return false;

        // Return true
        return true;
    }

    // If while fails without returning return false
    return false;
}

DxFeatures::Command::ICommand& DxFeatures::Command::CmdShowAdapters::getInstance(){
    // Return static instance
    return s_instance;
}
