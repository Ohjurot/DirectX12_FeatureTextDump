#include "DxOptions6.h"

DxFeatures::Command::CmdOptions6 DxFeatures::Command::CmdOptions6::s_instance = DxFeatures::Command::CmdOptions6();

std::stringstream DxFeatures::Command::CmdOptions6::operator()(ID3D12Device* ptrDevice){
    // Create Output stream
    std::stringstream ss;

    // Return if device is null
    if (ptrDevice == nullptr) {
        return ss;
    }

    // Query Options6
    D3D12_FEATURE_DATA_D3D12_OPTIONS6 opt6;
    HRESULT hr;
    ZeroMemory(&opt6, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS6));
    if (FAILED(ptrDevice->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS6, &opt6, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS6)))) {
        // Return without warning or error
        return ss;
    }

    // VariableShadingRateTier
    ss << "Variable shading rate: ";
    switch (opt6.VariableShadingRateTier) {
        case D3D12_VARIABLE_SHADING_RATE_TIER_NOT_SUPPORTED:
            ss << "Not supported" << std::endl;
            break;
        case D3D12_VARIABLE_SHADING_RATE_TIER_1:
            ss << "Tier 1" << std::endl;
            break;
        case D3D12_VARIABLE_SHADING_RATE_TIER_2:
            ss << "Tier 2" << std::endl;
            break;
    }

    // AdditionalShadingRatesSupported
    ss << "Additional shading rates: ";
    if (opt6.AdditionalShadingRatesSupported) {
        ss << "Yes" << std::endl;
    }else {
        ss << "No" << std::endl;
    }

    // PerPrimitiveShadingRateSupportedWithViewportIndexing
    ss << "Per primitive shading rate with indexing: ";
    if (opt6.PerPrimitiveShadingRateSupportedWithViewportIndexing) {
        ss << "Yes" << std::endl;
    } else {
        ss << "No" << std::endl;
    }

    // Return stream
    return ss;
}

DxFeatures::Command::ICommand& DxFeatures::Command::CmdOptions6::getInstance(){
    // Return static reference
    return s_instance;
}
