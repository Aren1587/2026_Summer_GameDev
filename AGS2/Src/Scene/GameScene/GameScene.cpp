#include "GameScene.h"
#include <DxLib.h>
#include "../../Application.h"
#include "../../Camera/Camera.h"
#include "../../Object/Actor/ActorBase.h"
#include "../../Object/Actor/Player/Player.h"
#include "../../Object/Actor/Enemy/Enemy.h"
#include "../../Object/Actor/Stage/Stage.h"

GameScene::GameScene(void)
{
	stage_ = new Stage();
	stage_->Load();
}

GameScene::~GameScene(void)
{
	if (stage_) {
		stage_->Release();
		delete stage_;
		stage_ = nullptr;
	}
}

void GameScene::Init(void)
{
	// カメラの初期化
	camera1_->Init();
	camera2_->Init();
	camera3_->Init();

	// 各ステージ初期化
	for (int i = 0; i < WORLD_NUM; ++i) {
		stages_[i]->Init();
	}

	// 全アクター初期化
	for (auto actor : allActor_) {
		actor->Init();
	}
}

void GameScene::Load(void)
{
	// カメラ生成
	camera1_ = new Camera();
	camera2_ = new Camera();
	camera3_ = new Camera();


	// ステージを3つ生成・ロード
	for (int i = 0; i < WORLD_NUM; ++i) {
		stages_[i] = new Stage();
		stages_[i]->Load();
	}

	// プレイヤー生成
	players_[0] = new Player(camera1_, 1); // 間違い1の世界
	players_[1] = new Player(camera2_, 2); // 間違い2の世界

	// アクター配列に追加
	for (int i = 0; i < PLAYER_NUM; ++i) {
		allActor_.push_back(players_[i]);
	}

	// カメラモード変更
	camera1_->SetFollow(players_[0]);
	camera2_->SetFollow(players_[1]);
	camera1_->ChangeMode(Camera::MODE::FOLLOW);
	camera2_->ChangeMode(Camera::MODE::FOLLOW);
	camera3_->ChangeMode(Camera::MODE::FIXED_POINT);
	SetCameraScreenCenter(0.0f, 240.0f);

	// 全てのアクターを読み込み
	for (auto actor : allActor_) {
		actor->Load();
	}
}

void GameScene::LoadEnd(void)
{
	// 両方のカメラの初期化
	camera1_->Init();
	camera2_->Init();

	// ステージ初期化
	stage_->LoadEnd();

	// 全てのアクターを読み込み後
	for (auto actor : allActor_)
	{
	 	// 読み込み
		actor->LoadEnd();
	}
}

void GameScene::Update(void)
{
	camera1_->Update();
	camera2_->Update();

	// 各ステージ更新
	for (int i = 0; i < WORLD_NUM; ++i) {
		stages_[i]->Update();
	}

	// 全アクター更新
	for (auto actor : allActor_) {
		actor->Update();
		if (actor) {
			WallCollision(actor);
		}
	}
	
}

void GameScene::Draw(void)
{
	int screen1 = MakeScreen(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y, false);
	int screen2 = MakeScreen(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y, false);
	int screen3 = MakeScreen(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y, false);//Application::SCREEN_SIZE_X / 4, Application::SCREEN_SIZE_Y, false);

	// 左画面（間違い1の世界）
	SetDrawScreen(screen1);
	ClearDrawScreen();
	camera1_->SetBeforeDraw();
	stages_[1]->Draw();
	players_[0]->Draw();

	// 右画面（間違い2の世界）
	SetDrawScreen(screen2);
	ClearDrawScreen();
	camera2_->SetBeforeDraw();
	stages_[2]->Draw();
	players_[1]->Draw();

	// 上画面（正解の世界）
	SetDrawScreen(screen3);
	ClearDrawScreen();
	camera3_->SetBeforeDraw();
	stages_[0]->Draw();

	SetDrawScreen(DX_SCREEN_BACK);
	DrawExtendGraph(0, 0, Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y, screen1, true);
	DrawExtendGraph(Application::SCREEN_SIZE_X / 2, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y, screen2, true);
	//DrawExtendGraph(((Application::SCREEN_SIZE_X / 2) - (Application::SCREEN_SIZE_X / 4)), 0,
		//((Application::SCREEN_SIZE_X / 2) + (Application::SCREEN_SIZE_X / 4)), Application::SCREEN_SIZE_Y / 3, screen3, true);


	DeleteGraph(screen1);
	DeleteGraph(screen2);
	DeleteGraph(screen3);

}

void GameScene::Release(void)
{
	delete camera1_;
	delete camera2_;

	// ステージ解放
	for (int i = 0; i < WORLD_NUM; ++i) {
		if (stages_[i]) {
			stages_[i]->Release();
			delete stages_[i];
			stages_[i] = nullptr;
		}
	}

	// 全アクター解放
	for (auto actor : allActor_) {
		actor->Release();
		delete actor;
	}
	allActor_.clear();
}

// ステージの床とプレイヤーの衝突
void GameScene::FieldCollision(ActorBase* actor)
{
	// 座標を所得
	VECTOR actorPos = actor->GetPos();

	// 線分の上座標
	VECTOR startPos = actorPos;
	startPos.y = actorPos.y + 10.0f;

	// 線分の下座標
	VECTOR endPos = actorPos;
	endPos.y = actorPos.y - 10.0f;

	// ステージのモデルを取得
	int modelId = stage_->GetModelId();

	// 線分とモデルの衝突判定
	MV1_COLL_RESULT_POLY res =
		MV1CollCheck_Line(modelId, -1, startPos, endPos);

	// ステージに当たっているか？
	if (res.HitFlag)
	{
		// 当たった場所に戻す
		actor->CollisionStage(res.HitPosition);
	}
}

void GameScene::WallCollision(ActorBase* actor)
{
	// 座標を取得
	VECTOR pos = actor->GetPos();

	// カプセルの座標
	VECTOR capStartPos = VAdd(pos, actor->GetStartCapsulePos());
	VECTOR capEndPos = VAdd(pos, actor->GetEndCapsulePos());

	// カプセルとの当たり判定
	auto hits = MV1CollCheck_Capsule
	(
		stage_->GetModelId(),			// ステージのモデルID
		-1,								// ステージ全てのポリゴンを指定
		capStartPos,					// カプセルの上
		capEndPos,						// カプセルの下
		actor->GetCapsuleRadius()		// カプセルの半径
	);

	// 衝突したポリゴン全ての検索
	for (int i = 0; i < hits.HitNum; i++)
	{
		// ポリゴンを1枚に分割
		auto hit = hits.Dim[i];

		// ポリゴン検索を制限(全てを検索すると重いので)
		for (int tryCnt = 0; tryCnt < 10; tryCnt++)
		{
			// 最初の衝突判定で検出した衝突ポリゴン1枚と衝突判定を取る
			int pHit = HitCheck_Capsule_Triangle
			(
				capStartPos,					// カプセルの上
				capEndPos,						// カプセルの下
				actor->GetCapsuleRadius(),		// カプセルの半径
				hit.Position[0],				// ポリゴン1
				hit.Position[1],				// ポリゴン2
				hit.Position[2]					// ポリゴン3
			);

			// カプセルとポリゴンが当たっていた
			if (pHit)
			{
				// 当たっていたので座標をポリゴンの法線方向に移動させる
				pos = VAdd(pos, VScale(hit.Normal, 1.0f));

				// 球体の座標も移動させる
				capStartPos = VAdd(capStartPos, VScale(hit.Normal, 1.0f));
				capEndPos = VAdd(capEndPos, VScale(hit.Normal, 1.0f));

				// 複数当たっている可能性があるので再検索
				continue;
			}
		}
	}
	// 検出したポリゴン情報の後始末
	MV1CollResultPolyDimTerminate(hits);

	// 計算した場所にアクターを戻す
	actor->CollisionStage(pos);
}
