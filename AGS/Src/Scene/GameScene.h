#pragma once
class Player;
class Weapon;
class FieldManager;

class GameScene : public SceneBase
{
public:

	static constexpr int BACKGROUND_COLOR_R = 0;
	static constexpr int BACKGROUND_COLOR_G = 139;
	static constexpr int BACKGROUND_COLOR_B = 139;

	// コンストラクタ
	GameScene(void);

	// デストラクタ
	~GameScene(void)override;

	// 初期化処理
	void Init(void)override;

	// 3D初期化
	void Init3D(void);	

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

Player* player_;

Weapon* weapon_;

FieldManager* fieldManager_;

int GameSceneSoundHandle;
};
