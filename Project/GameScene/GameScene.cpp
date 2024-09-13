#include "GameScene.h"

GameScene::~GameScene() {
	for (Enemy* enemy : enemys_) {
		delete enemy;
	}
}

void GameScene::Initialize() {
	camera_.Initialize();
	textureManager_->Initialize();

	postProcess_ = std::make_unique<PostProcess>();
	postProcess_->Initialize(NONE);

	// player
	player_ = std::make_unique<Player>();
	player_->Initialize();

	stage_ = std::make_unique<Stage>();
	stage_->Initialize();

	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize();

	sceneBGM = audio_->SoundLoadWave("resources/chasing.wav");
	audio_->SoundPlayLoop(sceneBGM);

	for (Enemy* enemy : enemys_) {
		enemy->SetIsDead(true);
	}
	ClearCount = 0;
	Interval = 0;

	//時間のUI
	timeTexture = textureManager_->Load("resources/4b3u5.png");
	timeModel_ = std::make_unique<Model>();
	timeModel_->Initialize("board.obj", timeTransform);
	timeModel_->SetLight(false);

	timeWorldtransform.translate = timeTransform.translate;
	timeWorldtransform.rotate = timeTransform.rotate;
	timeWorldtransform.scale = timeTransform.scale;
	timeWorldtransform.UpdateMatrix();


	timeblockTransform = { {-6.8f,0.95f,1.5f},{0.0f,0.0f,0.0f},{24.35f,10.45f,10.0f} };
	timeblockTexture = textureManager_->Load("resources/Green.png");
	timeblockModel_ = std::make_unique<Model>();
	timeblockModel_->Initialize("board.obj", timeblockTransform);
	timeblockModel_->SetLight(false);

	timeblockWorldtransform.translate = timeblockTransform.translate;
	timeblockWorldtransform.rotate = timeblockTransform.rotate;
	timeblockWorldtransform.scale = timeblockTransform.scale;
	timeblockWorldtransform.UpdateMatrix();
}

void GameScene::Update() {

	UpdateEnemyPopCommands();

	camera_.Update();

	player_->Update();

	stage_->Update();



	for (Enemy* enemy : enemys_) {
		enemy->Update();
		if (ImGui::TreeNode("Enemy")) {
			ImGui::Text("Type : %d", enemy->GetTYPE(), 1);
			ImGui::TreePop();
		}


		if (enemy->GetPos().y <= -10.0f) {
			audio_->SoundPlayStop(sceneBGM);
			sceneNo = GAMEOVER;
			enemy->SetIsDead(true);
		}
	}

	if (ImGui::TreeNode("timeWorldtransform")) {
		ImGui::DragFloat3("Translate", &timeWorldtransform.translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &timeWorldtransform.rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &timeWorldtransform.scale.x, 0.01f);
		ImGui::TreePop();
	}

	if (ImGui::TreeNode("timeblockWorldtransform")) {
		ImGui::DragFloat3("Translate", &timeblockWorldtransform.translate.x, 0.01f);
		ImGui::DragFloat3("Rotate", &timeblockWorldtransform.rotate.x, 0.01f);
		ImGui::DragFloat3("Scale", &timeblockWorldtransform.scale.x, 0.01f);
		ImGui::DragInt("time", &ClearCount, 0.01f);
		ImGui::TreePop();
	}

	//デスフラグの立った弾を削除
	enemys_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
		});


	CheckAllCollisions();

	ClearCount++;
	if (ClearCount >= 1800) {
		for (Enemy* enemy : enemys_) {
			enemy->SetIsDead(true);
		}
		audio_->SoundPlayStop(sceneBGM);
		sceneNo = CLEAR;
	}

	timeblockWorldtransform.scale.x += 0.0037777777777778f;
	/*if (input_->TriggerKey(DIK_RETURN)) {
		for (Enemy* enemy : enemys_) {
			enemy->SetIsDead(true);
		}
		audio_->SoundPlayStop(sceneBGM);
		sceneNo = CLEAR;
	}*/


	timeWorldtransform.UpdateMatrix();
	timeModel_->SetWorldTransform(timeWorldtransform);

	timeblockWorldtransform.UpdateMatrix();
	timeblockModel_->SetWorldTransform(timeblockWorldtransform);
}

void GameScene::Draw()
{
	//UI
	timeModel_->Draw(&camera_, timeTexture);
	timeblockModel_->Draw(&camera_, timeblockTexture);
	
	skydome_->Draw(&camera_);

	stage_->Draw(&camera_);

	// 敵キャラの描画
	for (Enemy* enemy : enemys_) {
		enemy->Draw(&camera_);
	}

	player_->Draw(&camera_);


}


void GameScene::PostDraw()
{
	postProcess_->Draw();
}

void GameScene::Release() {
}

void GameScene::CheckAllCollisions()
{
	// 判定衝突AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullets();

#pragma region 自弾と敵キャラの当たり判定
	// 敵キャラと自弾すべての当たり判定
	for (PlayerBullet* bullet : playerBullets) {
		for (Enemy* enemy : enemys_) {

			// 敵キャラの座標
			posA = enemy->GetPos();

			// 自弾の座標
			posB = bullet->GetPos();

			float e2pBX = (posB.x - posA.x) * (posB.x - posA.x);
			float e2pBY = (posB.y - posA.y) * (posB.y - posA.y);
			float e2pBZ = (posB.z - posA.z) * (posB.z - posA.z);

			float eRadius = 1.0f;
			float pBRadius = 1.0f;

			float L = (eRadius + pBRadius);

			if (e2pBX + e2pBY + e2pBZ <= L) {

				if (enemy->GetTYPE() == bullet->GetTYPE()) {
					// 敵キャラの衝突時コールバックを呼び出す
					enemy->OnCollision();
				}

				// 自弾の衝突時コールバックを呼び出す
				bullet->OnCollision();
			}
		}
	}
#pragma endregion
}


void GameScene::UpdateEnemyPopCommands()
{


	///	真下に落ちるタイプ
	//if (input_->TriggerKey(DIK_A)) {
		//// 乱数生成器を初期化
		//EnemySpown({ float(rand() % 86 - 45),float(rand() % 11 + 27),0 });


	Interval++;
	if (Interval >= 120) {
		// 乱数生成器を初期化
		EnemySpown({ float(rand() % 45 - 22),float(rand() % 6 + 15) ,10 });
		srand((unsigned)time(NULL) * 54321);  // 乱数系列を初期化


		Interval = 0;
	}

	if (input_->TriggerKey(DIK_P)) {
		// 乱数生成器を初期化
		EnemySpown({ float(rand() % 45 - 22),float(rand() % 6 + 15) ,10 });
		srand((unsigned)time(NULL) * 54321);  // 乱数系列を初期化

	}
}

void GameScene::EnemySpown(Vector3 pos)
{
	// 敵キャラの生成
	Enemy* enemy_ = new Enemy();

	//敵キャラの色の確定
	enemy_->SetType(TYPE(rand() % 3));
	srand((unsigned)time(NULL) * 54321);  // 乱数系列を初期化

	// 敵キャラの初期化
	enemy_->Initialize(pos);

	AddEnemy(enemy_);
}

void GameScene::AddEnemy(Enemy* enemy)
{
	// リストに登録する
	//enemys_.push_back(enemy);
}