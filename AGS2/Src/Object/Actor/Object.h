#pragma once
#include <DxLib.h>
#include "../../Scene/GameScene/GameScene.h"

class Object
{
public:
	Object(GameScene::WORLD world);
	~Object();

	void Init(void);
	void Load(void);
	void LoadEnd(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void SetWorld(GameScene::WORLD world) { world_ = world; }
private:
	// ステージモデルのハンドルID
	int modelId_;

	// ステージモデルの位置
	VECTOR pos_;

	GameScene::WORLD world_;
	GameScene::WORLD viewWorld_;
};