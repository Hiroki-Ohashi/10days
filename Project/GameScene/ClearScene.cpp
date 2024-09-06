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
}

void ClearScene::Update()
{
	camera_.Update();

	if (input_->TriggerKey(DIK_RETURN)) {
		sceneNo = TITLE;
	}
	
}

void ClearScene::Draw()
{
}

void ClearScene::PostDraw()
{
	postProcess_->Draw();
}
