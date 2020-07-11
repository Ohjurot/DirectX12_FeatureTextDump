#include "DxOptions7.h"

DxFeatures::Command::CmdOptions7 DxFeatures::Command::CmdOptions7::s_instance = DxFeatures::Command::CmdOptions7();

std::stringstream DxFeatures::Command::CmdOptions7::operator()(ID3D12Device* ptrDevice){
    // Create Output stream
    std::stringstream ss;

    // Return if device is null
    if (ptrDevice == nullptr) {
        return ss;
    }

    // Query Options6
    D3D12_FEATURE_DATA_D3D12_OPTIONS7 opt7;
    HRESULT hr;
    if (FAILED(ptrDevice->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS7, &opt7, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS7)))) {
        // Return without warning or error
        return ss;
    }

    // D3D12_MESH_SHADER_TIER 
    ss << "Mesh shader support: ";
    switch (opt7.MeshShaderTier) {
        case D3D12_MESH_SHADER_TIER_NOT_SUPPORTED:
            ss << "Not supported" << std::endl;
            break;
        case D3D12_MESH_SHADER_TIER_1:
            ss << "Tier 1" << std::endl;
            break;
    }

    // D3D12_SAMPLER_FEEDBACK_TIER
    ss << "Sampler feedback support: ";
    switch (opt7.SamplerFeedbackTier) {
        case D3D12_SAMPLER_FEEDBACK_TIER_NOT_SUPPORTED:
            ss << "Not supported" << std::endl;
            break;
        case D3D12_SAMPLER_FEEDBACK_TIER_0_9:
            ss << "Tier 0.9" << std::endl;
            break;
        case D3D12_SAMPLER_FEEDBACK_TIER_1_0:
            ss << "Tier 1.0" << std::endl;
            break;
    }


    // Return stream
    return ss;
}

DxFeatures::Command::ICommand& DxFeatures::Command::CmdOptions7::getInstance(){
    // Return static reference
    return s_instance;
}
