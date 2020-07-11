#pragma once

#include <Windows.h>
#include <dxgi.h>
#include <d3d12.h>
#include <d3dcommon.h>

#include <Commands/ICommand.h>

#define CHECK_BIT(reg, bit) ((reg) & (1 << (bit)))

namespace DxFeatures {
	namespace Command {
		class CmdShaderCache : public DxFeatures::Command::ICommand {
			public:
				/// <summary>
				/// A command need to implement the "execution" operator
				/// </summary>
				/// <param name="ptrDevice">By default we need a ID3D12Device* (can be nullpointer when called; needs to be catched by command)</param>
				/// <returns>Composed output stream</returns>
				std::stringstream operator()(ID3D12Device* ptrDevice);

				/// <summary>
				/// Reference to private static object
				/// </summary>
				/// <returns>const reference to command</returns>
				static DxFeatures::Command::ICommand& getInstance();
			private:
				// Private constructor for singelton
				CmdShaderCache() {};

			private:
				// Declaration of CmdCPUI's instance 
				static CmdShaderCache s_instance;
		};
	}
}