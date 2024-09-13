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
#include <PostProcess.h>
#include "Animation.h"
#include "Json.h"
#include "SkyBox.h"
#include <Skydome.h>
#include <Stage/Stage.h>
#include <Player/Player.h>
#include <Enemy/Enemy.h>
#include "../../Engine/Audio/audio.h"



#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")

class GameScene : public IScene {
public:
	~GameScene();

	// 初期化
	void Initialize() override;
	// 読み込み
	void Update() override;
	// 描画
	void Draw() override;
	// ポストエフェクト
	void PostDraw() override;

	// 解放
	void Release();

	void CheckAllCollisions();

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

	void EnemySpown(Vector3 pos);
	void AddEnemy(Enemy* enemy);

private:
	Camera camera_;
	TextureManager* textureManager_ = TextureManager::GetInstance();
	std::unique_ptr<PostProcess> postProcess_ = nullptr;
	Audio* audio_ = Audio::GetInstance();

	//UI 時間                          scale            rotate           translate
	EulerTransform timeTransform = { {3.5f,1.1f,1.5f},{0.0f,0.0f,0.0f},{21.0f,12.5f,10.0f} };
	WorldTransform timeWorldtransform;
	std::unique_ptr<Model> timeModel_;

	EulerTransform timeblockTransform = { {-6.8f,0.95f,1.5f},{0.0f,0.0f,0.0f},{24.35f,10.45f,10.0f} };
	WorldTransform timeblockWorldtransform;
	std::unique_ptr<Model> timeblockModel_;

	std::unique_ptr<Sprite> sprite_[4];

	// プレイヤー
	std::unique_ptr<Player> player_;

	// 敵
	std::list<Enemy*> enemys_;

	std::unique_ptr<Stage> stage_;

	std::unique_ptr<Skydome> skydome_;
private:
	// 待機タイマー
	int32_t waitTimer_;
	// 待機フラグ
	bool isWait_;

	// 敵発生コマンド
	std::stringstream enemyPopCommands;

	int ClearCount = 0;

	int Interval = 0;

	//種類
	TYPE type_;

	uint32_t sceneBGM = 0;
	uint32_t timeTexture;

	uint32_t timeblockTexture;

	uint32_t bulletColor[3];
	int frame;
	uint32_t bulletColorSpare[3];
};