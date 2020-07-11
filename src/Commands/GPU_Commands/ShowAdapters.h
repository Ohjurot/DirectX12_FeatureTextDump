#pragma once

#include <Windows.h>
#include <dxgi.h>
#include <d3d12.h>

#include <vector>
#include <string>
#include <locale>
#include <codecvt>

#include <Commands/ICommand.h>
#include <Data/AdapterDesc.h>

namespace DxFeatures {
	namespace Command {
		class CmdShowAdapters : public DxFeatures::Command::ICommand {
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
				CmdShowAdapters() {};

				// Boolean to prevent multiple calls to command
				bool m_bCalled = false;
				std::vector<DxFeatures::Data::AdapterDesc> m_vecAdapterInfo;

			private:
				// Declaration of CmdCPUI's instance 
				static CmdShowAdapters s_instance;
		};
	}
}