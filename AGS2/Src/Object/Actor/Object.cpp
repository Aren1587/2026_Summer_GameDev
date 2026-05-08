#include "Object.h"

#include "../../Application.h"
#include "../../Input/InputManager.h"

Object::Object(GameScene::WORLD world)
{
	modelId_ = -1;
	pos_ = { 0.0f, 0.0f, 0.0f };
	viewWorld_ = world;
}

Object::~Object()
{
}

void Object::Init(void)
{
	// モデルの位置
	pos_ = { 0.0f, 80.0f, 0.0f };

	// モデルの位置を設定
	MV1SetPosition(modelId_, pos_);

	// マテリアルの数を取得
	int num = MV1GetMaterialNum(modelId_);
	for (int i = 1; i < num; i++)
	{
		// 0は地面なので、1から設定する
		MV1SetMaterialEmiColor(modelId_, i, GetColorF(0.2f, 0.2f, 0.2f, 1.0f));
	}

	// 衝突判定情報の構築
	MV1SetupCollInfo(modelId_, -1);
}

void Object::Load(void)
{
	//
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "Cube.mv1").c_str());
}

void Object::LoadEnd(void)
{
	Init();
}

void Object::Update(void)
{
	if (InputManager::GetInstance()->IsTrgDown(KEY_INPUT_SPACE))
	{
		viewWorld_ = (viewWorld_ == GameScene::WORLD::LEFT) ? GameScene::WORLD::RIGHT : GameScene::WORLD::LEFT;
	}
}

void Object::Draw(void)
{
	if (viewWorld_ == world_)
	{
		MV1DrawModel(modelId_);

		DrawFormatString(
			0, 20, 0xffffff,
			"座標 :(%.1f, %.1f, %.1f)",
			pos_.x,
			pos_.y,
			pos_.z
		);
	}
}

void Object::Release(void)
{
	MV1DeleteModel(modelId_);
}
