#pragma once

#include <d3d12.h>
#include <sstream>

namespace DxFeatures {
	namespace Command {
		class ICommand {
			public:
				/// <summary>
				/// A command need to implement the "execution" operator
				/// </summary>
				/// <param name="ptrDevice">By default we need a ID3D12Device* (can be nullpointer when called; needs to be catched by command)</param>
				/// <returns>Composed output stream</returns>
				virtual std::stringstream operator()(ID3D12Device* ptrDevice) = 0;
		};
	}
}