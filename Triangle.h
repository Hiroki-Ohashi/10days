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

class Mesh;

class Triangle {
public:

	// 初期化
	void Initialize(DirectXCommon* dir, Mesh* mesh, Vector4* pos);
	// 読み込み
	void Update(const Matrix4x4& transformationMatrixData);
	// 描画
	void Draw();
	// 解放
	void Release();

	void CreateVertexResource(Vector4* pos);
	void CreateMaterialResource();
	void CreateWVPResource();

	Material* GetMaterialData() { return materialData; }

private:

	DirectXCommon* dir_;
	Mesh* mesh_;

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView{};

	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource;
	Microsoft::WRL::ComPtr<ID3D12Resource> wvpResource;

	VertexData* vertexData;
	Material* materialData;
	TransformationMatrix* wvpData;

	Transform transform;

	Matrix4x4 worldMatrix;

	static inline HRESULT hr_;
};