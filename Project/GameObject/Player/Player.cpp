#include "Player.h"

Player::~Player() {
	
}

void Player::Initialize()
{
	transform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,-3.0f,5.0f} };

	model_ = std::make_unique<Model>();
	model_->Initialize("cube.obj", transform_);

	worldtransform_.Initialize();
	worldtransform_.scale = transform_.scale;
	worldtransform_.rotate = transform_.rotate;
	worldtransform_.translate = transform_.translate;
	worldtransform_.UpdateMatrix();

	playerTex = textureManager_->Load("resources/white.png");
}

void Player::Update()
{
	if (ImGui::TreeNode("Player")) {
		ImGui::DragFloat3("Transform", &worldtransform_.translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &worldtransform_.rotate.x, 0.01f);
		ImGui::TreePop();
	}

	worldtransform_.UpdateMatrix();
}

void Player::Draw(Camera* camera_)
{
	model_->Draw(camera_, playerTex);
}