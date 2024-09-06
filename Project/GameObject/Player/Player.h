#pragma once
#include <TextureManager.h>
#include <Model.h>
#include <Input.h>

class Player {
public:
	~Player();

	void Initialize();
	void Update();
	void Draw(Camera* camera_);

	void OnCollision() {}
	
private:
	
private:
	TextureManager* textureManager_ = TextureManager::GetInstance();
	Input* input_ = Input::GetInsTance();

	WorldTransform worldtransform_;
	EulerTransform transform_;
	std::unique_ptr<Model> model_;

	uint32_t playerTex;
};