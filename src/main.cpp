#include <Windows.h>
#include <iostream>

#include <d3d12.h>
#include <dxgi.h>

int main(int argc, char** argv) {
	// Echo out application information
	std::cout << "DirectX 12 Feature to text dump - 2020 Ludwig Fuechsl" << std::endl;

	// TODO: Insert fancy application

	// Just a simple Hello DirectX Test
	// Using NULL for nullptr here!
	ID3D12Device* ptrDevice = NULL;

	// Hresult only for debug break (More diagnostics coming soon)
	HRESULT hr;

	// Create D3D 12.0 Device on default adapter
	if (FAILED(hr = D3D12CreateDevice(NULL, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&ptrDevice)))) {
		return -1;
	}

	// Test Feature
	D3D12_FEATURE_DATA_D3D12_OPTIONS5 featureSet;
	ZeroMemory(&featureSet, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS5));
	if (FAILED(hr = ptrDevice->CheckFeatureSupport(D3D12_FEATURE_D3D12_OPTIONS5, &featureSet, sizeof(D3D12_FEATURE_DATA_D3D12_OPTIONS5)))) {
		ptrDevice->Release();
		return -1;
	}

	// Sample output
	std::cout << "RayTracing: ";
	switch (featureSet.RaytracingTier) {
		case D3D12_RAYTRACING_TIER_NOT_SUPPORTED:
			std::cout << "Not Supported" << std::endl;
			break;
		case D3D12_RAYTRACING_TIER_1_0:
			std::cout << "Tier 1.0 supported" << std::endl;
			break;
		case D3D12_RAYTRACING_TIER_1_1:
			std::cout << "Tier 1.1 supported" << std::endl;
			break;
	}

	// Release Device
	ptrDevice->Release();

	// Return zero by default
	return 0;
}