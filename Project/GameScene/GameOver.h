#pragma once
#include "IScene.h"
#include <TextureManager.h>
#include <Camera.h>
#include <Sprite.h>
#include <PostProcess.h>
#include <Skydome.h>
#include <Json.h>
#include <Stage/Stage.h>

class GameOverScene : public IScene {
public:
	~GameOverScene();

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
	std::unique_ptr<Model> titleModel_2;
private:
	EulerTransform titleTransform = { {30.0f,10.0f,10.0f},{0.0f,0.0f,0.0f},{0.0f,3.0f,55.0f} };
	WorldTransform titleWorldtransform;

	EulerTransform titleTransform2 = { {15.0f,3.0f,10.0f},{0.0f,0.0f,0.0f},{0.0f,titleTransform.translate.y - 8.0f,55.0f} };
	WorldTransform titleWorldtransform2;

	uint32_t titleTexture;
	uint32_t titleTexture1;

	float speed = 0.05f;
};