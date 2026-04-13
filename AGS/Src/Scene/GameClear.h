#pragma once
#include "SceneBase.h"

class GameClear : public SceneBase
{
public:

	// コンストラクタ
	GameClear(void);

	// デストラクタ
	~GameClear(void)override;

	// 初期化処理
	void Init(void)override;

	// 更新ステップ
	void Update(void)override;

	// 読み込み
	void Load(void) override;

	// 読み込み後の初期化
	void LoadEnd(void) override;

	// 描画処理
	void Draw(void)override;

	// 解放処理
	void Release(void)override;

private:
};

