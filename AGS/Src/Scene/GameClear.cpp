#include <DxLib.h>
#include "GameClear.h"
#include "../Manager/Input/KeyManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/TitleScene.h"


GameClear::GameClear(void)
{
}

GameClear::~GameClear(void)
{
}

void GameClear::Init(void)
{
}

void GameClear::Update(void)
{
    if (CheckHitKey(KEY_INPUT_SPACE) || (KEY::GetIns().GetInfo(KEY_TYPE::GAME_NEXT).down))
    {
        // スペースキーが押下されたら、ゲームシーンへ遷移する
        SceneManager::GetInstance()->ChangeScene(std::make_shared<TitleScene>());
    }
}

void GameClear::Load(void)
{
}

void GameClear::LoadEnd(void)
{
}

void GameClear::Draw(void)
{
    DrawString(100, 100, "Game Clear!", GetColor(255, 255, 255));
	DrawString(100, 150, "Press A Button to return to Title", GetColor(255, 255, 255));
}

void GameClear::Release(void)
{
}
