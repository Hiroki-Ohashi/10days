#pragma once
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <cstdint>

#include "WinApp.h"
#include "Function.h"
#include "MathFunction.h"
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "Mesh.h"

class Sphere {
public:
	void Initialize(TextureManager* texture_);

	void Update();

	void Draw(uint32_t index, const Matrix4x4& transformationMatrixData);

	void Release();

	void CreateVertexResourceSphere();
	void CreateMaterialResourceSphere();
	void CreateTransformationMatrixResourceSphere();
	void CreateDirectionalResource();
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(Microsoft::WRL::ComPtr<ID3D12Device> device, size_t sizeInbytes);


	Material* GetMaterialDataSphere() { return materialDataSphere; }
	DirectionalLight* GetDirectionalLightData(){return directionalLightData;}

private:
	TextureManager* texture_;

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResourceSphere;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResourceSphere;
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResourceSphere;
	Microsoft::WRL::ComPtr<ID3D12Resource> directionalLightResource;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferViewSphere{};

	VertexData* vertexDataSphere;
	Material* materialDataSphere;
	TransformationMatrix* wvpResourceDataSphere;

	Transform transformSphere;
	Transform uvTransformSphere;
	TransformationMatrix* worldMatrixSphere;

	const uint32_t kSubdivision = 64; //分割数
	uint32_t vertexIndex = (kSubdivision * kSubdivision) * 6;

	bool isSphere = true;
	bool useMoon = false;

	DirectionalLight* directionalLightData;
};