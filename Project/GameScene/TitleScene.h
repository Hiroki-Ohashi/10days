#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>
#include <format>

#include "Function.h"
#include "Triangle.h"
#include "Sprite.h"
#include "ImGuiManeger.h"
#include "MathFunction.h"
#include "Camera.h"
#include "Sphere.h"
#include "Model.h"
#include "TextureManager.h"
#include "imgui.h"

#include "Particle.h"
#include "IScene.h"
#include "PostProcess.h"
#include <Json.h>
#include <Skydome.h>
#include <Player/Player.h>
#include <Stage/Stage.h>
#include "../../titleObject.h"
#include "../../Engine/Audio/audio.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")



class TitleScene : public IScene {
public:
	~TitleScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void PostDraw() override;

private:
	Camera camera_;
	TextureManager* textureManager_ = TextureManager::GetInstance();
	Audio* audio_ = Audio::GetInstance();

	std::unique_ptr<PostProcess> postProcess_ = nullptr;

	// プレイヤー
	std::unique_ptr<Player> player_;

	std::unique_ptr<Stage> stage_;
	std::unique_ptr<Skydome> skydome_;

	std::unique_ptr<TitleObject> titleObject_;

private:
	uint32_t sceneBGM = 0;
};