#include "DxOptions1.h"

DxFeatures::Command::CmdOptions1 DxFeatures::Command::CmdOptions1::s_instance = DxFeatures::Command::CmdOptions1();

std::stringstream DxFeatures::Command::CmdOptions1::operator()(ID3D12Device* ptrDevice){
    // Create Output stream
    std::stringstream ss;

    // Return if device is null
    if (ptrDevice == nullptr) {
        return ss;
    }

    // Query Options1
    D3D12_FEATURE_DATA_D3D12_OPTIONS1 opt1;
    ZeroMemory(&opt1, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS1));
    if (FAILED(ptrDevice->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS1, &opt1, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS1)))) {
        // Return without warning or error
        return ss;
    }

    // Echo result
    ss << "Wave lane count min / max: " << opt1.WaveLaneCountMin << "/" << opt1.WaveLaneCountMax << std::endl;
    ss << "Total lane count: " << opt1.TotalLaneCount << std::endl;
    ss << "Int64 support: ";
    if (opt1.Int64ShaderOps) {
        ss << "Yes" << std::endl;
    } else {
        ss << "No" << std::endl;
    }

    // Return stream
    return ss;
}

DxFeatures::Command::ICommand& DxFeatures::Command::CmdOptions1::getInstance(){
    // Return const reference
    return s_instance;
}
