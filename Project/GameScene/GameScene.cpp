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

	for (Enemy* enemy : enemys_) {
		enemy->SetIsDead(false);
	}

}

void GameScene::Update() {

	UpdateEnemyPopCommands();

	camera_.Update();

	player_->Update();

	stage_->Update();

	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}

	CheckAllCollisions();

	if (input_->TriggerKey(DIK_RETURN)) {
		sceneNo = CLEAR;
	}
}

void GameScene::Draw()
{
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

			if (e2pBX + e2pBY + e2pBZ <= L && enemy->GetTYPE() == bullet->GetTYPE()) {
				// 敵キャラの衝突時コールバックを呼び出す
				enemy->OnCollision();
			}

			if (e2pBX + e2pBY + e2pBZ <= L) {
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
	//enemy_->SetType(RED);

	// 敵キャラの初期化
	enemy_->Initialize(pos);


	AddEnemy(enemy_);
}

void GameScene::AddEnemy(Enemy* enemy)
{
	// リストに登録する
	enemys_.push_back(enemy);
}