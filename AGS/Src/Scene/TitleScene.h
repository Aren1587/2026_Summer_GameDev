#pragma once
#include "SceneBase.h"
class Grid;
class Player;
class SlimeManager;

class TitleScene : public SceneBase
{

public:

	static constexpr int TITLE_SIZE_WID = 1000;
	static constexpr int TITLE_SIZE_HIG = 667;
	static constexpr int SPECE_KYE_WID = 300;
	static constexpr int SPECE_KYE_HIG = 50;

	// コンストラクタ
	TitleScene(void);

	// デストラクタ
	~TitleScene(void) override;

	bool SystemInit();
	void Init(void) override;
	void Update(void) override;
	void Load(void) override;
	void LoadEnd(void) override;
	void Draw(void) override;
	void Release(void) override;

private:

	// グリッド線
	Grid* grid_;

	Player* player_;

	SlimeManager* slime_;

	int imageId_;

	int specemara_;
};
