#pragma once
#include <Camera.h>
#include <TextureManager.h>
#include <WorldTransform.h>
#include <Model.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


class Enemy {
public:
	void Initialize(Vector3 pos);
	void Update();
	void Draw(Camera* camera);

	void OnCollision() { isDead_ = true; }
	void SetIsDead(bool isDead) { isDead_ = isDead; }

	bool IsDead() { return isDead_; }

	Vector3 GetPos() { return worldtransform_.translate; }

	//敵弾の種類
	void SetType(TYPE type) { type_ = type; }
	TYPE GetTYPE() { return type_; }

private:
	TextureManager* textureManager_ = TextureManager::GetInstance();
	WorldTransform worldtransform_;
	EulerTransform transform_;
	std::unique_ptr<Model> model_;
private:
	//種類
	TYPE type_;

	uint32_t enemyTex;

	bool isDead_;
};	