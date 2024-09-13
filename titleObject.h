#pragma once
#include <TextureManager.h>
#include <Model.h>
#include <Input.h>

class TitleObject {
public:
	~TitleObject();

	void Initialize();
	void Update();
	void Draw(Camera* camera_);
private:
	TextureManager* textureManager_ = TextureManager::GetInstance();

	std::unique_ptr<Model> titleModel_1;
	std::unique_ptr<Model> titleModel_2;
	std::unique_ptr<Model> titleModel_3;
	std::unique_ptr<Model> titleModel_4;

	std::unique_ptr<Model> titleLog;

private:
	EulerTransform titleTransform_1 = { {3.0f,3.0f,3.0f},{0.0f,0.0f,0.0f},{-15.0f,0.0f,15.0f} };
	WorldTransform titleWorldtransform_1;

	EulerTransform titleTransform_2 = { {3.0f,3.0f,3.0f},{0.0f,0.0f,0.0f},{-5.0f,0.0f,15.0f} };
	WorldTransform titleWorldtransform_2;

	EulerTransform titleTransform_3 = { {3.0f,3.0f,3.0f},{0.0f,0.0f,0.0f},{5.0f,0.0f,15.0f} };
	WorldTransform titleWorldtransform_3;

	EulerTransform titleTransform_4 = { {3.0f,3.0f,3.0f},{0.0f,0.0f,0.0f},{15.0f,0.0f,15.0f} };
	WorldTransform titleWorldtransform_4;

	EulerTransform logTransform = { {9.0f,3.0f,3.0f},{0.0f,0.0f,0.0f},{0.2f,9.0f,15.0f} };
	WorldTransform logWorldtransform;

	uint32_t titleTex1;
	uint32_t titleTex2;
	uint32_t titleTex3;
	uint32_t titleTex4;

	uint32_t logTex;

	float speed1 = 0.05f;
	float speed2 = 0.05f;
	float speed3 = 0.05f;
	float speed4 = 0.05f;

	bool isUp1;
	bool isUp2;
	bool isUp3;
};