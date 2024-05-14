#pragma once

#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <cassert>
#include <cstdint>
#include <fstream>
#include <sstream>

#include "WinApp.h"
#include "Function.h"
#include "MathFunction.h"
#include "DirectXCommon.h"
#include "TextureManager.h"
#include "Mesh.h"
#include "Camera.h"
#include "WorldTransform.h"

class Model {
public:
	void Initialize(const std::string& filename, EulerTransform transform);

	void Update();

	void Draw(Camera* camera, uint32_t index);
	void DrawAnimation(Skeleton skeleton, Animation animation, Camera* camera, uint32_t index);

	ModelData GetModelData() { return modelData; }

private:

	void CreateVertexResource();
	void CreateMaterialResource();
	void CreateWVPResource();
	void CreateDirectionalResource();

	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(Microsoft::WRL::ComPtr<ID3D12Device> device, size_t sizeInbytes);

private:

	WinApp* winapp_ = WinApp::GetInsTance();
	TextureManager* texture_ = TextureManager::GetInstance();

	WorldTransform worldTransform_;

	ModelData modelData;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> cameraResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> directionalLightResource;

	VertexData* vertexData;
	Material* materialData;
	TransformationMatrix* wvpData;
	DirectionalLight directionalLightData;

	EulerTransform transform;
	EulerTransform uvTransform;

	bool isModel;

	CameraForGpu camera;

};
