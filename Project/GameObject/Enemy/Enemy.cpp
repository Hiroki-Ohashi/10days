#include "Enemy.h"

void Enemy::Initialize(Vector3 pos)
{
	transform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{pos.x,pos.y,pos.z} };

	model_ = std::make_unique<Model>();
	model_->Initialize("cube.obj", transform_);

	worldtransform_.scale = transform_.scale;
	worldtransform_.rotate = transform_.rotate;
	worldtransform_.translate = transform_.translate;
	worldtransform_.UpdateMatrix();

	isDead_ = false;

	enemyTex = textureManager_->Load("resources/black.png");
}

void Enemy::Update()
{

	///敵の移動処理
	worldtransform_.translate.y -= 0.1f;


	model_->SetWorldTransform(worldtransform_);
	worldtransform_.UpdateMatrix();

	//if (ImGui::TreeNode("Enemy")) {
	//	ImGui::DragFloat3("Rotate.y ", &worldtransform_.rotate.x, 0.01f);
	//	ImGui::DragFloat3("Transform", &worldtransform_.translate.x, 0.01f);
	//	ImGui::Checkbox("isDead", &isDead_);
	//	ImGui::TreePop();
	//}
}

void Enemy::Draw(Camera* camera)
{
	if (isDead_ == false) {
		model_->Draw(camera, enemyTex);
	}
}