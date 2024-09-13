#include "titleObject.h"

TitleObject::~TitleObject()
{
}

void TitleObject::Initialize()
{
	titleLog = std::make_unique<Model>();
	titleLog->Initialize("board.obj", logTransform);
	titleLog->SetLight(false);

	logWorldtransform.translate = logTransform.translate;
	logWorldtransform.rotate = logTransform.rotate;
	logWorldtransform.scale = logTransform.scale;
	logWorldtransform.UpdateMatrix();

	// 撃
	titleModel_1 = std::make_unique<Model>();
	titleModel_1->Initialize("board.obj", titleTransform_1);

	titleWorldtransform_1.translate = titleTransform_1.translate;
	titleWorldtransform_1.rotate = titleTransform_1.rotate;
	titleWorldtransform_1.scale = titleTransform_1.scale;
	titleWorldtransform_1.UpdateMatrix();

	// 墜
	titleModel_2 = std::make_unique<Model>();
	titleModel_2->Initialize("board.obj", titleTransform_2);

	titleWorldtransform_2.translate = titleTransform_2.translate;
	titleWorldtransform_2.rotate = titleTransform_2.rotate;
	titleWorldtransform_2.scale = titleTransform_2.scale;
	titleWorldtransform_2.UpdateMatrix();

	// せ
	titleModel_3 = std::make_unique<Model>();
	titleModel_3->Initialize("board.obj", titleTransform_3);

	titleWorldtransform_3.translate = titleTransform_3.translate;
	titleWorldtransform_3.rotate = titleTransform_3.rotate;
	titleWorldtransform_3.scale = titleTransform_3.scale;
	titleWorldtransform_3.UpdateMatrix();

	// よ
	titleModel_4 = std::make_unique<Model>();
	titleModel_4->Initialize("board.obj", titleTransform_4);

	titleWorldtransform_4.translate = titleTransform_4.translate;
	titleWorldtransform_4.rotate = titleTransform_4.rotate;
	titleWorldtransform_4.scale = titleTransform_4.scale;
	titleWorldtransform_4.UpdateMatrix();

	titleTex1 = textureManager_->Load("resources/geki.png");
	titleTex2 = textureManager_->Load("resources/tui.png");
	titleTex3 = textureManager_->Load("resources/se.png");
	titleTex4 = textureManager_->Load("resources/yo.png");

	logTex = textureManager_->Load("resources/titleLog.png");
}

void TitleObject::Update()
{
	if (titleWorldtransform_1.translate.y < 0.0f) {
		speed1 += 0.001f;
	}
	else if(titleWorldtransform_1.translate.y >= 0.0f) {
		speed1 -= 0.001f;
	}

	titleWorldtransform_1.translate.y += speed1;
	titleWorldtransform_1.UpdateMatrix();
	titleModel_1->SetWorldTransform(titleWorldtransform_1);

	if (titleWorldtransform_1.translate.y >= 1.2f) {
		isUp1 = true;
	}

	if (isUp1) {
		if (titleWorldtransform_2.translate.y < 0.0f) {
			speed2 += 0.001f;
		}
		else if (titleWorldtransform_2.translate.y >= 0.0f) {
			speed2 -= 0.001f;
		}

		titleWorldtransform_2.translate.y += speed2;
	}
	titleWorldtransform_2.UpdateMatrix();
	titleModel_2->SetWorldTransform(titleWorldtransform_2);

	if (titleWorldtransform_2.translate.y >= 1.2f) {
		isUp2 = true;
	}

	if (isUp2) {
		if (titleWorldtransform_3.translate.y < 0.0f) {
			speed3 += 0.001f;
		}
		else if (titleWorldtransform_3.translate.y >= 0.0f) {
			speed3 -= 0.001f;
		}

		titleWorldtransform_3.translate.y += speed3;
	}
	titleWorldtransform_3.UpdateMatrix();
	titleModel_3->SetWorldTransform(titleWorldtransform_3);

	if (titleWorldtransform_3.translate.y >= 1.2f) {
		isUp3 = true;
	}
	if (isUp3) {
		if (titleWorldtransform_4.translate.y < 0.0f) {
			speed4 += 0.001f;
		}
		else if (titleWorldtransform_4.translate.y >= 0.0f) {
			speed4 -= 0.001f;
		}
		titleWorldtransform_4.translate.y += speed4;
	}
	titleWorldtransform_4.UpdateMatrix();
	titleModel_4->SetWorldTransform(titleWorldtransform_4);

	logWorldtransform.UpdateMatrix();
	titleLog->SetWorldTransform(logWorldtransform);

	if (ImGui::TreeNode("geki")) {
		ImGui::DragFloat3("Transform", &titleWorldtransform_1.translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &titleWorldtransform_1.rotate.x, 0.01f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("tui")) {
		ImGui::DragFloat3("Transform", &titleWorldtransform_2.translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &titleWorldtransform_2.rotate.x, 0.01f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("se")) {
		ImGui::DragFloat3("Transform", &titleWorldtransform_3.translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &titleWorldtransform_3.rotate.x, 0.01f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("yo")) {
		ImGui::DragFloat3("Transform", &titleWorldtransform_4.translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &titleWorldtransform_4.rotate.x, 0.01f);
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("log")) {
		ImGui::DragFloat3("Transform", &logWorldtransform.translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &logWorldtransform.rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &logWorldtransform.scale.x, 0.01f);
		ImGui::TreePop();
	}
}

void TitleObject::Draw(Camera* camera_)
{
	titleModel_1->Draw(camera_, titleTex1);
	titleModel_2->Draw(camera_, titleTex2);
	titleModel_3->Draw(camera_, titleTex3);
	titleModel_4->Draw(camera_, titleTex4);

	titleLog->Draw(camera_, logTex);
}
