#include "CommandExecuter.h"

void DxFeatures::Command::CommandExecutor::executeCommand(DxFeatures::Command::ICommand& refCommand, ID3D12Device* ptrDevice, HANDLE handleOutFile){
	// Set file pointer to end
	SetFilePointer(handleOutFile, 0, 0, FILE_END);

	// Create string from command output
	std::string strOut = refCommand(ptrDevice).str();

	// Write to std out
	std::cout << strOut;

	// Write to file
	WriteFile(handleOutFile, strOut.data(), strOut.size(), NULL, NULL);
	
	// Flush file
	FlushFileBuffers(handleOutFile);
}
