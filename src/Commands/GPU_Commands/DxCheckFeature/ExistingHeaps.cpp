#include "ExistingHeaps.h"

DxFeatures::Command::CmdExistingHeaps DxFeatures::Command::CmdExistingHeaps::s_instance = DxFeatures::Command::CmdExistingHeaps();

std::stringstream DxFeatures::Command::CmdExistingHeaps::operator()(ID3D12Device* ptrDevice){
    // Create Output stream
    std::stringstream ss;

    // Return if device is null
    if (ptrDevice == nullptr) {
        return ss;
    }

    // Query D3D12_FEATURE_DATA_SHADER_CACHE 
    D3D12_FEATURE_DATA_EXISTING_HEAPS  ehR;
    if (FAILED(ptrDevice->CheckFeatureSupport(D3D12_FEATURE_EXISTING_HEAPS, &ehR, sizeof(D3D12_FEATURE_DATA_EXISTING_HEAPS)))) {
        // Return without warning or error
        return ss;
    }

    // Echo out
    ss << "Existing heaps support: ";
    if (ehR.Supported) {
        ss << "Yes" << std::endl;
    } else {
        ss << "No" << std::endl;
    }

    // Return stream
    return ss;
}

DxFeatures::Command::ICommand& DxFeatures::Command::CmdExistingHeaps::getInstance(){
    // Return static reference
    return s_instance;
}
