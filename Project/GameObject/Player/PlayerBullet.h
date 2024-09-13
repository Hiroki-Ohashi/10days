#pragma once
#include <Camera.h>
#include <Model.h>

class PlayerBullet {
public:
	void Initialize(Vector3 pos, Vector3 velocity);
	void Update();
	void Draw(Camera* camera, uint32_t index);

	void OnCollision() { isDead_ = true; }

	bool IsDead() const { return isDead_; }
	Vector3 GetPos() { return worldtransform_.translate; }

	//プレイヤー弾の種類
	void SetType(TYPE type) { type_ = type; }
	TYPE GetTYPE() { return type_; }


private:
	std::unique_ptr<Model> model_;
	EulerTransform transform;
	WorldTransform worldtransform_;
	TextureManager* textureManager_ = TextureManager::GetInstance();
private:
	// デスタイマー
	static const int32_t kLifeTime = 60 * 5;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_ = false;

	//種類
	TYPE type_;

	// 速度
	Vector3 velo;

	uint32_t playerbulletTex;

};