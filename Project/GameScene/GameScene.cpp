#include "GameScene.h"

GameScene::~GameScene(){
}

void GameScene::Initialize() {
	camera_.Initialize();

	postProcess_ = std::make_unique<PostProcess>();
	postProcess_->Initialize(NONE);

	// player
	player_ = std::make_unique<Player>();
	player_->Initialize();
}

void GameScene::Update(){
	camera_.Update();

	player_->Update();

	if (input_->PushKey(DIK_SPACE)) {
		sceneNo = CLEAR;
	}
}

void GameScene::Draw()
{
	player_->Draw(&camera_);
}


void GameScene::PostDraw()
{
	postProcess_->Draw();
}

void GameScene::Release() {
}