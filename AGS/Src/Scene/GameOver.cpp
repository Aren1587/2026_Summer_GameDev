#include <DxLib.h>
#include "GameOver.h"
#include "../Manager/Input/KeyManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/TitleScene.h"

GameOver::GameOver(void)
{
}

GameOver::~GameOver(void)
{
}

void GameOver::Init(void)
{

}

void GameOver::Update(void)
{
    if (CheckHitKey(KEY_INPUT_SPACE) || (KEY::GetIns().GetInfo(KEY_TYPE::GAME_NEXT).down))
    {
        // スペースキーが押下されたら、ゲームシーンへ遷移する
        SceneManager::GetInstance()->ChangeScene(std::make_shared<TitleScene>());
    }
}

void GameOver::Load(void)
{
}

void GameOver::LoadEnd(void)
{
}

void GameOver::Draw(void)
{
    DrawString(100, 100, "げぇむおーばー wwww!", GetColor(255, 255, 255));
    DrawString(100, 150, "Press A Button to return to Title", GetColor(255, 255, 255));
}

void GameOver::Release(void)
{
}
