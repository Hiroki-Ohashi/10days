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
	titleModel_->SetLight(false);

	titleWorldtransform.translate = titleTransform.translate;
	titleWorldtransform.rotate = titleTransform.rotate;
	titleWorldtransform.scale = titleTransform.scale;
	titleWorldtransform.UpdateMatrix();

	titleTexture = textureManager_->Load("resources/clearLog.png");

	sceneBGM = audio_->SoundLoadWave("resources/opening-reggae.wav");
	audio_->SoundPlayLoop(sceneBGM);
}

void ClearScene::Update()
{
	camera_.Update();

	if (titleWorldtransform.translate.y < 2.0f) {
		speed += 0.001f;
	}
	else if (titleWorldtransform.translate.y >= 2.0f) {
		speed -= 0.001f;
	}

	titleWorldtransform.translate.y += speed;

	titleWorldtransform.UpdateMatrix();
	titleModel_->SetWorldTransform(titleWorldtransform);

	if (input_->TriggerKey(DIK_A)) {
		audio_->SoundPlayStop(sceneBGM);
		sceneNo = TITLE;
	}
	
	XINPUT_STATE joyState;

	if (Input::GetInsTance()->GetJoystickState(joyState)) {

		if (Input::GetInsTance()->PressedButton(joyState, XINPUT_GAMEPAD_A)) {
			audio_->SoundPlayStop(sceneBGM);
			sceneNo = STAGE;
		}

	}

	if (ImGui::TreeNode("log")) {
		ImGui::DragFloat3("Transform", &titleWorldtransform.translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &titleWorldtransform.rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &titleWorldtransform.scale.x, 0.01f);
		ImGui::TreePop();
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
