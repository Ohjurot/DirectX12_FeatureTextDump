#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <dxgi.h>

namespace DxFeatures {
	namespace Data {
		struct AdapterDesc {
			UINT index;
			DXGI_ADAPTER_DESC description;
		};
	}
}