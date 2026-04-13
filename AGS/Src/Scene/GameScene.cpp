#include <cmath>
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include "../Manager/Camera.h"
#include "../Object/Stage/Stage.h"
#include "TitleScene.h"
#include "../Object/Player/Player.h"
#include "GameScene.h"
#include "../Object/Weapon/Weapon.h"
#include "../Scene/SceneManager.h"
#include "../Object/Stage/Field/FieldManager.h"
#include "../Effect/EffekseerEffect.h"


GameScene::GameScene(void) : SceneBase()
{
	SetMouseDispFlag(false);
}

GameScene::~GameScene(void)
{

}

void GameScene::Init(void)
{
	GameSceneSoundHandle = LoadSoundMem("Data/Sound/BGM.mp3");
}

void GameScene::Init3D(void)
{

	// 背景色設定
	SetBackgroundColor(
		BACKGROUND_COLOR_R,
		BACKGROUND_COLOR_G,
		BACKGROUND_COLOR_B);

	// Zバッファを有効にする
	SetUseZBuffer3D(true);

	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(true);

	// バックカリングを有効にする
	SetUseBackCulling(true);

	// ライトの設定
	SetUseLighting(true);

	// 正面から斜め下に向かったライト
	ChangeLightTypeDir({ 0.00f, -1.00f, 1.00f });

}


void GameScene::Update(void)
{
	// ステージ更新
	Stage::GetInstance()->Update();

	PlaySoundMem(GameSceneSoundHandle, DX_PLAYTYPE_LOOP);

	// プレイヤー更新
	player_->Update();

	// エフェクト更新
	EffekseerEffect::GetInstance()->Update();

	// フィールドの更新
	fieldManager_->Update();


}

void GameScene::Load(void)
{
	// プレイヤー初期化
	player_ = new Player();
	player_->Init();

	// カメラモード変更
	Camera* camera = SceneManager::GetInstance()->GetCamera();
	camera->SetFollow(player_);
	camera->ChangeMode(Camera::MODE::FOLLOW);

	// ステージ初期化
	Stage::CreateInstance();
	Stage::GetInstance()->Init();
	Stage::GetInstance()->SetPlayer(player_);

	// エフェクトの初期化
	EffekseerEffect::CreateInstance();

	EffekseerEffect::GetInstance()->SetWeapon(player_->GetWeapon());

	// フィールドの初期化
	fieldManager_ = new FieldManager();
	fieldManager_->Init(player_);
}

void GameScene::LoadEnd(void)
{

}

void GameScene::Draw(void)
{

	Camera* camera = SceneManager::GetInstance()->GetCamera();
	camera->SetBeforeDraw();

	// Effekseerにより再生中のエフェクトを更新する
	UpdateEffekseer3D();


	// ステージ描画
	Stage::GetInstance()->Draw();

	// フィールド描画
	fieldManager_->Draw();

	// プレイヤー描画
	player_->Draw();

	// エフェクトの描画
	EffekseerEffect::GetInstance()->Draw();

	// カメラの描画
	camera->DrawDebug();

	// Effekseerにより再生中のエフェクトを描画する
	//DrawEffekseer3D();
}

void GameScene::Release(void)
{
	// ステージ解放
	Stage::GetInstance()->Release();
	Stage::DeleteInstance();

	// エフェクトの解放
	EffekseerEffect::GetInstance()->Delete();
	EffekseerEffect::DeleteInstance();

	// フィールド解放
	fieldManager_->Release();
	delete fieldManager_;

	// プレイヤー解放
	player_->Release();
}
