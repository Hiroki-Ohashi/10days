#pragma once
#include <Camera.h>
#include <TextureManager.h>
#include <WorldTransform.h>
#include <Model.h>

class Enemy {
public:
	void Initialize(Vector3 pos);
	void Update();
	void Draw(Camera* camera);

	void OnCollision() { isDead_ = true; }
	void SetIsDead(bool isDead) { isDead_ = isDead; }

	bool IsDead() { return isDead_; }
	Vector3 GetPos() { return worldtransform_.translate; }
private:
	TextureManager* textureManager_ = TextureManager::GetInstance();
	WorldTransform worldtransform_;
	EulerTransform transform_;
	std::unique_ptr<Model> model_;
private:
	uint32_t enemyTex;
	
	bool isDead_;
};