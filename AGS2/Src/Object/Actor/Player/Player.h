#pragma once
#include <vector>
#include <DxLib.h>

#include "../ActorBase.h"

class Camera;

class Player : public ActorBase
{

public:

	// アニメーション種類
	enum class ANIM_TYPE
	{
		IDLE,
		WALK,
		MAX,
	};

	enum class PLAYER_NO
	{
		PLAYER_ONE = 0,
		PLAYER_TWO,
	};

	// コンストラクタ（プレイヤー番号を追加）
	Player(Camera* camera, PLAYER_NO playerNo);

	// デストラクタ
	~Player(void) override;

	// 更新
	void Update(void) override;

	// 描画
	void Draw(void) override;

	// 解放
	void Release(void) override;

	void SetNo(PLAYER_NO no) { playerNo_ = no; }

private:

	// リソース読込
	void InitLoad(void) override;

	// 大きさ、回転、座標の初期化
	void InitTransform(void) override;

	// アニメーションの初期化
	void InitAnimation(void) override;

	// 読み込み後の後処理
	void InitPost(void) override;

	// 移動制御
	void Move(void) override;

private:

	constexpr static VECTOR PLAYER_ONE_START_POS = { -100.0f, 0.0f, 0.0f };
	constexpr static VECTOR PLAYER_TWO_START_POS = { 100.0f, 0.0f, 0.0f };
	// カメラ
	Camera* camera_;

	// プレイヤー番号（0 or 1）
	PLAYER_NO playerNo_;

	int movePlayerNo_;
	int downKey_, hitKey_;
};