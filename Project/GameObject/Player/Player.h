#pragma once
#include <TextureManager.h>
#include <Model.h>
#include <Input.h>
#include "PlayerBullet.h"

class Player {
public:
	~Player();

	void Initialize();
	void Update();
	void Draw(Camera* camera_);

	void OnCollision() {}

	// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

private:
	void Attack();
private:
	TextureManager* textureManager_ = TextureManager::GetInstance();
	Input* input_ = Input::GetInsTance();

	std::list<PlayerBullet*> bullets_;

	WorldTransform worldtransform_;
	EulerTransform transform_;
	std::unique_ptr<Model> model_;

	WorldTransform worldtransform_2;
	EulerTransform transform_2;
	std::unique_ptr<Model> model_2;

	uint32_t playerTex;
	uint32_t playerTex2;

	uint32_t playerbulletTex;

	XINPUT_STATE joyState{};

	//種類
	int type_;
};