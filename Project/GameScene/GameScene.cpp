#include "GameScene.h"

GameScene::~GameScene(){
}

void GameScene::Initialize() {
	camera_.Initialize();

	postProcess_ = std::make_unique<PostProcess>();
	postProcess_->Initialize(NONE);
}

void GameScene::Update(){
	camera_.Update();

	if (input_->PushKey(DIK_SPACE)) {
		sceneNo = CLEAR;
	}
}

void GameScene::Draw()
{
}


void GameScene::PostDraw()
{
	postProcess_->Draw();
}

void GameScene::Release() {
}