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
	int GetBulletType(){return type_;
	}
private:
	void Attack();
private:
	TextureManager* textureManager_ = TextureManager::GetInstance();
	Input* input_ = Input::GetInsTance();

	std::list<PlayerBullet*> bullets_;

	WorldTransform worldtransform_;
	EulerTransform transform_;
	std::unique_ptr<Model> model_;

	uint32_t playerTex;

	uint32_t playerbulletTex;


	//種類
	int type_;
};