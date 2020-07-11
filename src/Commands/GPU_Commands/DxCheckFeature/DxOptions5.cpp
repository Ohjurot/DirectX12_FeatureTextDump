#include "DxOptions5.h"

DxFeatures::Command::CmdOptions5 DxFeatures::Command::CmdOptions5::s_instance = DxFeatures::Command::CmdOptions5();

std::stringstream DxFeatures::Command::CmdOptions5::operator()(ID3D12Device* ptrDevice){
    // Create Output stream
    std::stringstream ss;

    // Return if device is null
    if (ptrDevice == nullptr) {
        return ss;
    }

    // Query Options5
    D3D12_FEATURE_DATA_D3D12_OPTIONS5 opt5;
    HRESULT hr;
    ZeroMemory(&opt5, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS5));
    if (FAILED(ptrDevice->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &opt5, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS5)))) {
        // Return without warning or error
        return ss;
    }

    // Render pass tier
    ss << "Render passes tier: ";
    switch (opt5.RenderPassesTier) {
        case D3D12_RENDER_PASS_TIER_0:
            ss << "0" << std::endl;
            break;
        case D3D12_RENDER_PASS_TIER_1:
            ss << "1" << std::endl;
            break;
        case D3D12_RENDER_PASS_TIER_2:
            ss << "2" << std::endl;
            break;
    }

    // Raytracing tier
    ss << "Raytracing support: ";
    switch (opt5.RaytracingTier) {
        case D3D12_RAYTRACING_TIER_NOT_SUPPORTED:
            ss << "Not supported" << std::endl;
            break;
        case D3D12_RAYTRACING_TIER_1_0:
            ss << "Tier 1.0" << std::endl;
            break;
        case D3D12_RAYTRACING_TIER_1_1:
            ss << "Tier 1.1" << std::endl;
            break;
    }

    // Return stream
    return ss;
}

DxFeatures::Command::ICommand& DxFeatures::Command::CmdOptions5::getInstance(){
    // Return static reference
    return s_instance;
}
