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
        ss << "[GPULIST | " << desc.index << "]" << std::endl;
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

DxFeatures::Command::ICommand& DxFeatures::Command::CmdShowAdapters::getInstance(){
    // Return static instance
    return s_instance;
}
