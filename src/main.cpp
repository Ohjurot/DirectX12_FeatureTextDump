#include <Windows.h>
#include <iostream>

#include <Commands/ICommand.h>
#include <Commands/CommandExecuter.h>

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

	// Open file
	HANDLE hFile = CreateFile(
		L"./dxFeatures.txt",
		GENERIC_WRITE,
		NULL,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	// Check if file is invalid
	if (hFile == INVALID_HANDLE_VALUE) {
		std::cout << "Error open file ./dxFeatures.txt!" << std::endl;
		return -1;
	}

	// Write generic information
	DxFeatures::Command::CommandExecutor::executeCommand(DxFeatures::Command::CmdCPUID::getInstance(), nullptr, hFile);
	DxFeatures::Command::CommandExecutor::executeCommand(DxFeatures::Command::CmdSystemInfo::getInstance(), nullptr, hFile);
	DxFeatures::Command::CommandExecutor::executeCommand(DxFeatures::Command::CmdShowAdapters::getInstance(), nullptr, hFile);

	// Write GPU Info
	ID3D12Device* ptrDevice = nullptr;
	UINT curentIndex = 0;
	while (static_cast<DxFeatures::Command::CmdShowAdapters*>(&DxFeatures::Command::CmdShowAdapters::getInstance())->createNextDevice(&ptrDevice, &curentIndex)) {
		// Stream header
		std::stringstream ss;
		ss << "[FEATURE|" << curentIndex << "]" << std::endl;

		// Write header
		std::cout << ss.str();
		SetFilePointer(hFile, 0, 0, FILE_END);
		WriteFile(hFile, ss.str().data(), ss.str().size(), NULL, NULL);

		// Call commands
		DxFeatures::Command::CommandExecutor::executeCommand(DxFeatures::Command::CmdShaderModel::getInstance(), ptrDevice, hFile);
		DxFeatures::Command::CommandExecutor::executeCommand(DxFeatures::Command::CmdFeatureLevels::getInstance(), ptrDevice, hFile);
		DxFeatures::Command::CommandExecutor::executeCommand(DxFeatures::Command::CmdRootSignature::getInstance(), ptrDevice, hFile);
		DxFeatures::Command::CommandExecutor::executeCommand(DxFeatures::Command::CmdShaderCache::getInstance(), ptrDevice, hFile);
		DxFeatures::Command::CommandExecutor::executeCommand(DxFeatures::Command::CmdExistingHeaps::getInstance(), ptrDevice, hFile);
		DxFeatures::Command::CommandExecutor::executeCommand(DxFeatures::Command::CmdOptions1::getInstance(), ptrDevice, hFile);
		DxFeatures::Command::CommandExecutor::executeCommand(DxFeatures::Command::CmdOptions4::getInstance(), ptrDevice, hFile);
		DxFeatures::Command::CommandExecutor::executeCommand(DxFeatures::Command::CmdOptions5::getInstance(), ptrDevice, hFile);
		DxFeatures::Command::CommandExecutor::executeCommand(DxFeatures::Command::CmdOptions6::getInstance(), ptrDevice, hFile);
		DxFeatures::Command::CommandExecutor::executeCommand(DxFeatures::Command::CmdOptions7::getInstance(), ptrDevice, hFile);

		// Manual newline
		CHAR newLine = '\n';
		std::cout << std::endl;
		SetFilePointer(hFile, 0, 0, FILE_END);
		WriteFile(hFile, &newLine, 1, NULL, NULL);
	}

	// Release if not already released (Should never happen)
	if (ptrDevice != nullptr) {
		ptrDevice->Release();
	}

	// Close file
	CloseHandle(hFile);

	// Return zero by default
	return 0;
}
