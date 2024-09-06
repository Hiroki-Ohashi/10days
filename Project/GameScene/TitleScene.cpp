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
	
	if (input_->PushKey(DIK_SPACE)) {
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
