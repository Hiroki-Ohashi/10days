#include "GameScene.h"

GameScene::~GameScene(){
	for (int i = 0; i < Max; i++) {
		delete triangle_[i];
	}
	delete sprite_;
	delete sphere_;
	delete model_;
	delete camera_;
	delete particle_;
}

void GameScene::Initialize(){
	textureManager_ = TextureManager::GetInstance();
	textureManager_->Initialize();

	camera_ = new Camera();
	camera_->Initialize();

	sprite_ = new Sprite(); 
	sprite_->Initialize(Vector2{0.0f, 0.0f}, Vector2{640.0f, 360.0f});

	sphere_ = new Sphere();
	sphere_->Initialize();

	transform = { { 0.5f,0.5f,0.5f},{0.0f,0.0f,0.0f},{0.0f,-0.5f,1.0f} };

	model_ = new Model();
	model_->Initialize("cube.obj", transform);

	particle_ = new Particles();
	particle_->Initialize("plane.obj", Vector3{0.0f, 0.0f, 0.0f});

	Vector4 pos[Max][3];

	// 左下
	pos[0][0] = { -0.5f, -0.25f, 0.0f, 1.0f };
	// 上
	pos[0][1] = { 0.0f, 0.5f, 0.0f, 1.0f };
	// 右下
	pos[0][2] = { 0.5f, -0.25f, 0.0f, 1.0f };

	// 左下2
	pos[1][0] = { -0.5f, -0.25f, 0.5f, 1.0f };
	// 上2
	pos[1][1] = { 0.0f, 0.0f, 0.0f, 1.0f };
	// 右下2
	pos[1][2] = { 0.5f, -0.25f, -0.5f, 1.0f };

	for (int i = 0; i < Max; i++) {
		triangle_[i] = new Triangle();
		triangle_[i]->Initialize(pos[i]);
	}

	uv = textureManager_->Load("resources/uvChecker.png");
	moon = textureManager_->Load("resources/moon.png");
	monsterBall = textureManager_->Load("resources/monsterball.png");
	kusa = textureManager_->Load("resources/kusa.png");
	circle = textureManager_->Load("resources/circle.png");
}

void GameScene::Update(){
	camera_->Update();
}

void GameScene::Draw(){
	sphere_->Draw(camera_, moon);

	model_->Draw(camera_, kusa);


	triangle_[0]->Draw(camera_, uv);
	triangle_[1]->Draw(camera_, uv);

	sprite_->Draw(monsterBall);

	particle_->Draw(camera_, circle);
}

void GameScene::Release() {
}
