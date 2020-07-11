#include "FeatureLevels.h"

DxFeatures::Command::CmdFeatureLevels DxFeatures::Command::CmdFeatureLevels::s_instance = DxFeatures::Command::CmdFeatureLevels();

std::stringstream DxFeatures::Command::CmdFeatureLevels::operator()(ID3D12Device* ptrDevice){
    // Create Output stream
    std::stringstream ss;

    // Return if device is null
    if (ptrDevice == nullptr) {
        return ss;
    }

    // Print fist
    ss << "Feature level: ";

    // Query Feature levels
    D3D_FEATURE_LEVEL arr[] = {
        D3D_FEATURE_LEVEL_12_0,
        D3D_FEATURE_LEVEL_12_1
    };
    
    D3D12_FEATURE_DATA_FEATURE_LEVELS fLevels;
    fLevels.NumFeatureLevels = 2;
    fLevels.pFeatureLevelsRequested = arr;
 
    HRESULT hr;
    if (FAILED(hr = ptrDevice->CheckFeatureSupport(D3D12_FEATURE_FEATURE_LEVELS, &fLevels, sizeof(D3D12_FEATURE_DATA_FEATURE_LEVELS)))) {
        ss << "n/a (Error code: " << (int)hr << ")" << std::endl;
        return ss;
    }

    // Echo level
    switch (fLevels.MaxSupportedFeatureLevel) {
        case D3D_FEATURE_LEVEL_12_0:
            ss << "12.0" << std::endl;
            break;
        case D3D_FEATURE_LEVEL_12_1:
            ss << "12.1" << std::endl;
            break;
        // D3D_FEATURE_LEVEL_12_2 will likley be published with the final release of Dx12 Ultimate (I think when AMD and NVIDIA role out the new cards)
    }

    // Return stream
    return ss;
}

DxFeatures::Command::ICommand& DxFeatures::Command::CmdFeatureLevels::getInstance(){
    // Return static instance
    return s_instance;
}
