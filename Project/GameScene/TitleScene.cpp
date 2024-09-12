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

	titleModel_ = std::make_unique<Model>();
	titleModel_->Initialize("board.obj", titleTransform);

	titleWorldtransform.translate = titleTransform.translate;
	titleWorldtransform.rotate = titleTransform.rotate;
	titleWorldtransform.scale = titleTransform.scale;
	titleWorldtransform.UpdateMatrix();

	titleTexture = textureManager_->Load("resources/title.png");
}


void TitleScene::Update()
{
	camera_.Update();

	player_->Update();
	
	titleModel_->SetWorldTransform(titleWorldtransform);

	if (input_->TriggerKey(DIK_RETURN)) {
		sceneNo = STAGE;
	}
}

void TitleScene::Draw()
{
	skydome_->Draw(&camera_);

	stage_->Draw(&camera_);

	titleModel_->Draw(&camera_, titleTexture);

	player_->Draw(&camera_);
}

void TitleScene::PostDraw()
{
	postProcess_->Draw();
}
