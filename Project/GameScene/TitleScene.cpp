#include "TitleScene.h"

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	camera_.Initialize();
	textureManager_->Initialize();

	postProcess_ = std::make_unique<PostProcess>();
	postProcess_->Initialize(NONE);

	// player
	player_ = std::make_unique<Player>();
	player_->Initialize();

	stage_ = std::make_unique<Stage>();
	stage_->Initialize();

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize();

	titleObject_ = std::make_unique<TitleObject>();
	titleObject_->Initialize();
}


void TitleScene::Update()
{
	camera_.Update();

	player_->Update();

	titleObject_->Update();

	if (input_->TriggerKey(DIK_RETURN)) {
		sceneNo = STAGE;
	}
}

void TitleScene::Draw()
{
	skydome_->Draw(&camera_);

	stage_->Draw(&camera_);

	titleObject_->Draw(&camera_);

	player_->Draw(&camera_);
}

void TitleScene::PostDraw()
{
	postProcess_->Draw();
}
