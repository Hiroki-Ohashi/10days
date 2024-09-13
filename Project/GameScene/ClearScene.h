#pragma once
#include "IScene.h"
#include <TextureManager.h>
#include <Camera.h>
#include <Sprite.h>
#include <PostProcess.h>
#include <Skydome.h>
#include <Json.h>
#include <Stage/Stage.h>

class ClearScene : public IScene {
public:
	~ClearScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void PostDraw() override;

private:
	Camera camera_;
	TextureManager* textureManager_ = TextureManager::GetInstance();

	std::unique_ptr<PostProcess> postProcess_ = nullptr;

	std::unique_ptr<Stage> stage_;
	std::unique_ptr<Skydome> skydome_;
	std::unique_ptr<Model> titleModel_;
private:
	EulerTransform titleTransform = { {20.0f,10.0f,10.0f},{0.0f,0.0f,0.0f},{0.0f,3.0f,35.0f} };
	WorldTransform titleWorldtransform;

	uint32_t titleTexture;

	float speed = 0.05f;
};