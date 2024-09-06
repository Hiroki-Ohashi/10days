#include "Player.h"

Player::~Player() {
	// bullet_の解放
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Player::Initialize()
{
	transform_ = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,-10.0f,10.0f} };

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
	if (input_->PushKey(DIK_A)) {
		worldtransform_.rotate.z += 0.05f;
	}
	else if(input_->PushKey(DIK_D))
	{
		worldtransform_.rotate.z -= 0.05f;
	}

	model_->SetWorldTransform(worldtransform_);
	worldtransform_.UpdateMatrix();

	// デスフラグの立った弾を排除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});

	// 攻撃処理
	Attack();

	// 弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}

	if (ImGui::TreeNode("Player")) {
		ImGui::DragFloat3("Transform", &worldtransform_.translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &worldtransform_.rotate.x, 0.01f);
		ImGui::TreePop();
	}
}

void Player::Draw(Camera* camera_)
{
	model_->Draw(camera_, playerTex);

	// 弾描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(camera_, playerTex);
	}
}

void Player::Attack()
{
	if (input_->TriggerKey(DIK_SPACE)) {

		// 弾の速度
		const float kBulletSpeed = 2.0f;
		Vector3 velocity(0.0f, kBulletSpeed, 0.0f);

		// 速度ベクトルを自機の向きに併せて回転させる
		velocity = TransformNormal(velocity, worldtransform_.matWorld);

		velocity.x = Normalize(velocity).x * kBulletSpeed;
		velocity.y = Normalize(velocity).y * kBulletSpeed;
		velocity.z = Normalize(velocity).z * kBulletSpeed;

		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(worldtransform_.translate, velocity);

		// 弾を登録
		bullets_.push_back(newBullet);
	}
}
