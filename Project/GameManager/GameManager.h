#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "Input.h"

#include "IScene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include <ClearScene.h>
#include "GameOver.h"

#include "ImGuiManeger.h"
#include "imgui.h"
#include "Light.h"
#include "../../Engine/Audio/audio.h"


class GameManager {
public:
	GameManager();
	~GameManager();

	static GameManager* GetInsTance();

	void Run();

private:
	WinApp* winapp = nullptr;
	DirectXCommon* directX = nullptr;
	Mesh* mesh = nullptr;
	Input* input = nullptr;
	ImGuiManeger* imgui = nullptr;
	Light* light_ = nullptr;
	Audio* audio_ = nullptr;


	// シーンを保持
	std::unique_ptr<IScene> sceneArr_[4];

	int currentSceneNo_ = TITLE;
	int prvSceneNo_ = 0;
	int sceneNo = 0;

};