#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <string>
#include <sstream>
#include <iostream>

#include <Commands/ICommand.h>

namespace DxFeatures {
	namespace Command {
		class CommandExecutor {
			public:
				static void executeCommand(DxFeatures::Command::ICommand& refCommand, ID3D12Device* ptrDevice, HANDLE handleOutFile);
			};
	}
}