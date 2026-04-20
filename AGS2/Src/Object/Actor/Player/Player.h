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

	// コンストラクタ（プレイヤー番号を追加）
	Player(Camera* camera, int playerNo);

	// デストラクタ
	~Player(void) override;

	// 更新
	void Update(void) override;

	// 描画
	void Draw(void) override;

	// 解放
	void Release(void) override;

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
	// カメラ
	Camera* camera_;

	// プレイヤー番号（1 or 2）
	int playerNo_;
};