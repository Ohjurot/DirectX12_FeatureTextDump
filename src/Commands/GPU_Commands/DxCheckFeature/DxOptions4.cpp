#include "DxOptions4.h"

DxFeatures::Command::CmdOptions4 DxFeatures::Command::CmdOptions4::s_instance = DxFeatures::Command::CmdOptions4();

std::stringstream DxFeatures::Command::CmdOptions4::operator()(ID3D12Device* ptrDevice){
    // Create Output stream
    std::stringstream ss;

    // Return if device is null
    if (ptrDevice == nullptr) {
        return ss;
    }

    // Query Options4
    D3D12_FEATURE_DATA_D3D12_OPTIONS4 opt4;
    ZeroMemory(&opt4, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS4));
    if (FAILED(ptrDevice->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS4, &opt4, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS4)))) {
        // Return without warning or error
        return ss;
    }

    // Echo the single (currently) required node
    ss << "MSAA64KB Support: ";
    if (opt4.MSAA64KBAlignedTextureSupported) {
        ss << "Yes" << std::endl;
    } else {
        ss << "No" << std::endl;
    }

    // Return stream
    return ss;
}

DxFeatures::Command::ICommand& DxFeatures::Command::CmdOptions4::getInstance(){
    // Return static instance
    return s_instance;
}
