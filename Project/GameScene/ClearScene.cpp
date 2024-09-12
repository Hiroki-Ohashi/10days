#include "ClearScene.h"

ClearScene::~ClearScene()
{
}

void ClearScene::Initialize()
{
	camera_.Initialize();
	textureManager_->Initialize();

	postProcess_ = std::make_unique<PostProcess>();
	postProcess_->Initialize(NONE);

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

	titleTexture = textureManager_->Load("resources/clearLog.png");
}

void ClearScene::Update()
{
	camera_.Update();

	titleModel_->SetWorldTransform(titleWorldtransform);

	if (input_->TriggerKey(DIK_RETURN)) {
		sceneNo = TITLE;
	}
	
}

void ClearScene::Draw()
{
	skydome_->Draw(&camera_);

	stage_->Draw(&camera_);

	titleModel_->Draw(&camera_, titleTexture);
}

void ClearScene::PostDraw()
{
	postProcess_->Draw();
}
