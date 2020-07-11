#include "ShaderCache.h"

DxFeatures::Command::CmdShaderCache DxFeatures::Command::CmdShaderCache::s_instance = DxFeatures::Command::CmdShaderCache();

std::stringstream DxFeatures::Command::CmdShaderCache::operator()(ID3D12Device* ptrDevice){
    // Create Output stream
    std::stringstream ss;

    // Return if device is null
    if (ptrDevice == nullptr) {
        return ss;
    }

    // Query D3D12_FEATURE_DATA_SHADER_CACHE 
    D3D12_FEATURE_DATA_SHADER_CACHE scR;
    HRESULT hr;
    if (FAILED(ptrDevice->CheckFeatureSupport(D3D12_FEATURE_SHADER_CACHE, &scR, sizeof(D3D12_FEATURE_DATA_SHADER_CACHE)))) {
        // Return without warning or error
        return ss;
    }

    // Echo to temp stream
    std::stringstream ssC;
    ssC << "Shader cache support: ";
    if (CHECK_BIT(scR.SupportFlags, D3D12_SHADER_CACHE_SUPPORT_NONE)) {
        ssC << "None, ";
    }
    if (CHECK_BIT(scR.SupportFlags, D3D12_SHADER_CACHE_SUPPORT_SINGLE_PSO)) {
        ssC << "Single PSO, ";
    }
    if (CHECK_BIT(scR.SupportFlags, D3D12_SHADER_CACHE_SUPPORT_LIBRARY)) {
        ssC << "Library, ";
    }
    if (CHECK_BIT(scR.SupportFlags, D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_INPROC_CACHE)) {
        ssC << "Automatic inproc cache, ";
    }
    if (CHECK_BIT(scR.SupportFlags, D3D12_SHADER_CACHE_SUPPORT_AUTOMATIC_INPROC_CACHE)) {
        ssC << "Automatic disc cache, ";
    }

    // Substring to stream
    ss << ssC.str().substr(0, ssC.str().length() - 2) << std::endl;


    // Return stream
    return ss;
}

DxFeatures::Command::ICommand& DxFeatures::Command::CmdShaderCache::getInstance(){
    // Return static reference
    return s_instance;
}
