#pragma once

#include <Commands/ICommand.h>
#include <Data/CPUID.h>

#define	SSTREAM_OUT(condition, stream, text) if(condition) {stream << text;}

namespace DxFeatures {
	namespace Command {
		class CmdCPUID : public DxFeatures::Command::ICommand{
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
				CmdCPUID() {};

				// Boolean to prevent multiple calls to command
				bool m_bCalled = false;

			private:
				// Declaration of CmdCPUI's instance 
				static CmdCPUID s_instance;
		};
	}
}