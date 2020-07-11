#include <Windows.h>
#include <iostream>

#include <Commands/CPU_Commands/CPUIDQuery.h>
#include <Commands/CPU_Commands/SystemInfo.h>
#include <Commands/GPU_Commands/ShowAdapters.h>
#include <Commands/GPU_Commands/DxCheckFeature/ShaderModel.h>
#include <Commands/GPU_Commands/DxCheckFeature/FeatureLevels.h>
#include <Commands/GPU_Commands/DxCheckFeature/RootSignature.h>
#include <Commands/GPU_Commands/DxCheckFeature/ShaderCache.h>
#include <Commands/GPU_Commands/DxCheckFeature/ExistingHeaps.h>
#include <Commands/GPU_Commands/DxCheckFeature/DxOptions1.h>
#include <Commands/GPU_Commands/DxCheckFeature/DxOptions4.h>
#include <Commands/GPU_Commands/DxCheckFeature/DxOptions5.h>
#include <Commands/GPU_Commands/DxCheckFeature/DxOptions6.h>
#include <Commands/GPU_Commands/DxCheckFeature/DxOptions7.h>

int main(int argc, char** argv) {
	// Echo out application information
	std::cout << "DirectX 12 Feature to text dump - 2020 Ludwig Fuechsl" << std::endl << std::endl;

	// TODO: Insert fancy application

	// === Testing own commands ===
	std::cout << DxFeatures::Command::CmdCPUID::getInstance()(nullptr).str();
	std::cout << DxFeatures::Command::CmdSystemInfo::getInstance()(nullptr).str();
	std::cout << DxFeatures::Command::CmdShowAdapters::getInstance()(nullptr).str();

	ID3D12Device* ptrDevice = nullptr;
	UINT curentIndex = 0;
	while (static_cast<DxFeatures::Command::CmdShowAdapters*>(&DxFeatures::Command::CmdShowAdapters::getInstance())->createNextDevice(&ptrDevice, &curentIndex)) {
		std::cout << "[FEATURE|" << curentIndex << "]" << std::endl;

		std::cout << DxFeatures::Command::CmdShaderModel::getInstance()(ptrDevice).str();
		std::cout << DxFeatures::Command::CmdFeatureLevels::getInstance()(ptrDevice).str();
		std::cout << DxFeatures::Command::CmdRootSignature::getInstance()(ptrDevice).str();
		std::cout << DxFeatures::Command::CmdShaderCache::getInstance()(ptrDevice).str();
		std::cout << DxFeatures::Command::CmdExistingHeaps::getInstance()(ptrDevice).str();
		std::cout << DxFeatures::Command::CmdOptions1::getInstance()(ptrDevice).str();
		std::cout << DxFeatures::Command::CmdOptions4::getInstance()(ptrDevice).str();
		std::cout << DxFeatures::Command::CmdOptions5::getInstance()(ptrDevice).str();
		std::cout << DxFeatures::Command::CmdOptions6::getInstance()(ptrDevice).str();
		std::cout << DxFeatures::Command::CmdOptions7::getInstance()(ptrDevice).str();

		std::cout << std::endl;
	}

	// Release if not already released (Should never happen)
	if (ptrDevice != nullptr) {
		ptrDevice->Release();
	}

	// Return zero by default
	return 0;
}
