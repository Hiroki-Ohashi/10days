#include "GameOver.h"

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Initialize()
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
	titleModel_->SetLight(false);

	titleWorldtransform.translate = titleTransform.translate;
	titleWorldtransform.rotate = titleTransform.rotate;
	titleWorldtransform.scale = titleTransform.scale;
	titleWorldtransform.UpdateMatrix();

	titleModel_2 = std::make_unique<Model>();
	titleModel_2->Initialize("board.obj", titleTransform);
	titleModel_2->SetLight(false);

	titleWorldtransform2.translate = titleTransform2.translate;
	titleWorldtransform2.rotate = titleTransform2.rotate;
	titleWorldtransform2.scale = titleTransform2.scale;
	titleWorldtransform2.UpdateMatrix();

	titleTexture = textureManager_->Load("resources/gameOver.png");
	titleTexture1 = textureManager_->Load("resources/gameOverLog.png");

	sceneBGM = audio_->SoundLoadWave("resources/rpg_village.wav");
	audio_->SoundPlayLoop(sceneBGM);

}

void GameOverScene::Update()
{
	camera_.Update();

	if (titleWorldtransform.translate.y < 2.0f) {
		speed += 0.001f;
	}
	else if (titleWorldtransform.translate.y >= 2.0f) {
		speed -= 0.001f;
	}

	titleWorldtransform.translate.y += speed;

	titleWorldtransform2.translate.y += speed;

	titleWorldtransform.UpdateMatrix();
	titleModel_->SetWorldTransform(titleWorldtransform);

	titleWorldtransform2.UpdateMatrix();
	titleModel_2->SetWorldTransform(titleWorldtransform2);

	if (input_->TriggerKey(DIK_A)) {
		audio_->SoundPlayStop(sceneBGM);
		sceneNo = TITLE;
	}

	XINPUT_STATE joyState;

	if (Input::GetInsTance()->GetJoystickState(joyState)) {

		if (Input::GetInsTance()->PressedButton(joyState, XINPUT_GAMEPAD_A)) {
			audio_->SoundPlayStop(sceneBGM);
			sceneNo = TITLE;
		}

	}

	if (ImGui::TreeNode("log")) {
		ImGui::DragFloat3("Transform", &titleWorldtransform2.translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &titleWorldtransform2.rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &titleWorldtransform2.scale.x, 0.01f);
		ImGui::TreePop();
	}
}

void GameOverScene::Draw()
{
	skydome_->Draw(&camera_);

	stage_->Draw(&camera_);

	titleModel_->Draw(&camera_, titleTexture);
	titleModel_2->Draw(&camera_, titleTexture1);
}

void GameOverScene::PostDraw()
{
	postProcess_->Draw();
}
