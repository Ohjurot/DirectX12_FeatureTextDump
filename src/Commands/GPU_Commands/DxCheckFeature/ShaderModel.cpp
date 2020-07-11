#include "ShaderModel.h"

DxFeatures::Command::CmdShaderModel DxFeatures::Command::CmdShaderModel::s_instance = DxFeatures::Command::CmdShaderModel();

std::stringstream DxFeatures::Command::CmdShaderModel::operator()(ID3D12Device* ptrDevice){
    // Create Output stream
    std::stringstream ss;

    // Return if device is null
    if (ptrDevice == nullptr) {
        return ss;
    }

    // Print fist
    ss << "Shader modell: ";

    // Check shader model
    HRESULT hr;
    D3D12_FEATURE_DATA_SHADER_MODEL shaderModell;
    shaderModell.HighestShaderModel = D3D_SHADER_MODEL_6_6;
    if (FAILED(hr = ptrDevice->CheckFeatureSupport(D3D12_FEATURE_SHADER_MODEL, &shaderModell, sizeof(D3D12_FEATURE_DATA_SHADER_MODEL)))) {
        ss << "n/a (Error code: " << (int)hr << ")" << std::endl;
    }

    // Print shader modell
    switch (shaderModell.HighestShaderModel) {
        case D3D_SHADER_MODEL_5_1:
            ss << "5.1" << std::endl;
            break;
        case D3D_SHADER_MODEL_6_0:
            ss << "6.0" << std::endl;
            break;
        case D3D_SHADER_MODEL_6_1:
            ss << "6.1" << std::endl;
            break;
        case D3D_SHADER_MODEL_6_2:
            ss << "6.2" << std::endl;
            break;
        case D3D_SHADER_MODEL_6_3:
            ss << "6.3" << std::endl;
            break;
        case D3D_SHADER_MODEL_6_4:
            ss << "6.4" << std::endl;
            break;
        case D3D_SHADER_MODEL_6_5:
            ss << "6.5" << std::endl;
            break;
        case D3D_SHADER_MODEL_6_6:
            ss << "6.6" << std::endl;
            break;
    }
    
    // Return stream
    return ss;
}

DxFeatures::Command::ICommand& DxFeatures::Command::CmdShaderModel::getInstance(){
    // Return static instance
    return s_instance;
}
