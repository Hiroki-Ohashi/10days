#pragma once
#include "Input.h"

// シーン名
enum SCENE {
	TITLE,
	STAGE,
	CLEAR,
	GAMEOVER
};

class IScene {
protected:
	// シーン番号
	static int sceneNo;
	Input* input_ = Input::GetInsTance();

public:
	virtual ~IScene();

	virtual void Initialize() = 0;

	virtual void Update() = 0;

	virtual void Draw() = 0;

	virtual void PostDraw() = 0;

	int GetSceneNo();
};