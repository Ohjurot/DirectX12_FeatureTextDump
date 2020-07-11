#include "RootSignature.h"

DxFeatures::Command::CmdRootSignature DxFeatures::Command::CmdRootSignature::s_instance = DxFeatures::Command::CmdRootSignature();

std::stringstream DxFeatures::Command::CmdRootSignature::operator()(ID3D12Device* ptrDevice){
    // Create Output stream
    std::stringstream ss;

    // Return if device is null
    if (ptrDevice == nullptr) {
        return ss;
    }

    // Query D3D12_FEATURE_DATA_ROOT_SIGNATURE
    D3D12_FEATURE_DATA_ROOT_SIGNATURE rsD;
    HRESULT hr;
    rsD.HighestVersion = D3D_ROOT_SIGNATURE_VERSION_1_1;
    if (FAILED(ptrDevice->CheckFeatureSupport(D3D12_FEATURE_ROOT_SIGNATURE, &rsD, sizeof(D3D12_FEATURE_DATA_ROOT_SIGNATURE)))) {
        // Return without warning or error
        return ss;
    }

    // Echo out
    ss << "Root signature version: ";
    switch (rsD.HighestVersion) {
        // Equal to D3D_ROOT_SIGNATURE_VERSION_1
        case D3D_ROOT_SIGNATURE_VERSION_1_0:
            ss << "1.0" << std::endl;
            break;
        case D3D_ROOT_SIGNATURE_VERSION_1_1:
            ss << "1.1" << std::endl;
            break;
    }

    // Return stream
    return ss;
}

DxFeatures::Command::ICommand& DxFeatures::Command::CmdRootSignature::getInstance(){
    // Return static reference
    return s_instance;
}
