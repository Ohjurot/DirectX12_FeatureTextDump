#pragma once

#include <Commands/ICommand.h>

/***************************************************************************************************************
 * These files (SystemInfo.h and SystemInfo.cpp) where written using the Mircosoft dokumentation               *
 * This code here follows the microsoft example but has been adapted "to my c++ style"	                       *
 * The Microsoft dokumentation is release under CC BY 4.0													   *
 * https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getlogicalprocessorinformation  *
 * https://creativecommons.org/licenses/by/4.0/deed.de                                                         *
 ***************************************************************************************************************/

namespace DxFeatures {
	namespace Command {
		class CmdSystemInfo : public DxFeatures::Command::ICommand {
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
				
				/// <summary>
				/// Helper function form microsoft documentation
				/// https://docs.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getlogicalprocessorinformation
				/// </summary>
				/// <param name="bitMask">Bit Mask</param>
				/// <returns>Numer of set bits in mask</returns>
				static DWORD CountSetBits(ULONG_PTR bitMask);
			private:
				// Private constructor for singelton
				CmdSystemInfo() {};

				// Boolean to prevent multiple calls to command
				bool m_bCalled = false;

			private:
				// Declaration of CmdCPUI's instance 
				static CmdSystemInfo s_instance;
		};
	}
}