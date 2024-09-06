#include "TitleScene.h"

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	camera_.Initialize();

	postProcess_ = std::make_unique<PostProcess>();
	postProcess_->Initialize(NONE);
}


void TitleScene::Update()
{
	camera_.Update();
	
	if (input_->TriggerKey(DIK_RETURN)) {
		sceneNo = STAGE;
	}
}

void TitleScene::Draw()
{
}

void TitleScene::PostDraw()
{
	postProcess_->Draw();
}
