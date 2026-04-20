#include "EffekseerEffect.h"
#include "../Application.h"
#include "../Manager/Input/KeyManager.h"
#include "../Object/Weapon/Weapon.h"

EffekseerEffect* EffekseerEffect::instance_ = nullptr;

EffekseerEffect::EffekseerEffect(void)
{

}

EffekseerEffect::~EffekseerEffect(void)
{

}

void EffekseerEffect::Init(void)
{
	SetUseDirect3DVersion(DX_DIRECT3D_11);

	if (Effekseer_Init(8000) == -1) {
		DxLib_End();
		return;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(false);

	Effekseer_SetGraphicsDeviceLostCallbackFunctions();

	shalshutEffectId_ = LoadEffekseerEffect(
			(Application::PATH_EFFECT + "slashu.efkefc").c_str());

	if (shalshutEffectId_ == -1) {
		MessageBoxA(NULL, "エフェクトの読み込みに失敗しました。パスやファイルを確認してください。", "エラー", MB_OK);
	}

    finisyuId = LoadEffekseerEffect(
		(Application::PATH_EFFECT + "Fiyaer.efkefc").c_str());

    if (finisyuId == -1) {
        MessageBoxA(NULL, "エフェクトの読み込みに失敗しました。パスやファイルを確認してください。", "エラー", MB_OK);
	}

	finisyu2Id = LoadEffekseerEffect(
		(Application::PATH_EFFECT + "mizu.efkefc").c_str());

    if (finisyu2Id == -1) {
        MessageBoxA(NULL, "エフェクトの読み込みに失敗しました。パスやファイルを確認してください。", "エラー", MB_OK);
    }

	finisyu3Id = LoadEffekseerEffect(
        (Application::PATH_EFFECT + "kori.efkefc").c_str());

    if (finisyu3Id == -1) {
        MessageBoxA(NULL, "エフェクトの読み込みに失敗しました。パスやファイルを確認してください。", "エラー", MB_OK);
	}

    finisyu4Id = LoadEffekseerEffect(
        (Application::PATH_EFFECT + "bakuhatu.efkefc").c_str());

    if (finisyu4Id == -1) {
        MessageBoxA(NULL, "エフェクトの読み込みに失敗しました。パスやファイルを確認してください。", "エラー", MB_OK);
	}

    finisyu5Id = LoadEffekseerEffect(
        (Application::PATH_EFFECT + "comboLast.efkefc").c_str());

    if (finisyu5Id == -1) {
        MessageBoxA(NULL, "エフェクトの読み込みに失敗しました。パスやファイルを確認してください。", "エラー", MB_OK);
    }

    finisyu6Id = LoadEffekseerEffect(
        (Application::PATH_EFFECT + "meteo.efkefc").c_str());

    if (finisyu6Id == -1) {
        MessageBoxA(NULL, "エフェクトの読み込みに失敗しました。パスやファイルを確認してください。", "エラー", MB_OK);
	}
}

void EffekseerEffect::Update(void)
{
    //if (!weapon_) return;
    //
    //// 攻撃終了で停止
    //if (isSlashing_ && !weapon_->IsAttacking())
    //{
    //    StopEffekseer3DEffect(PlayshalshuEffectHandle);
    //    isSlashing_ = false;
    //    PlayshalshuEffectHandle = -1;
    //}

    //// 攻撃開始
    //if (KEY::GetIns().GetInfo(KEY_TYPE::ATTACK).down)
    //{
    //    // すでに再生中なら多重再生しない
    //    if (!isSlashing_)
    //    {
    //        PlayshalshuEffectHandle = PlayEffekseer3DEffect(shalshutEffectId_);
    //        SetSpeedPlayingEffekseer3DEffect(PlayshalshuEffectHandle, 0.5f);
    //        isSlashing_ = true;
    //    }
    //}

    //// 再生中：剣先に追従
    //if (isSlashing_)
    //{
    //    if (IsEffekseer3DEffectPlaying(PlayshalshuEffectHandle) != 0) return;

    //    VECTOR basePos = weapon_->GetSwordBasePos();
    //    VECTOR tipPos = weapon_->GetPos();

    //    // 位置追従（剣先）
    //    SetPosPlayingEffekseer3DEffect(
    //        PlayshalshuEffectHandle,
    //        tipPos.x,
    //        tipPos.y,
    //        tipPos.z
    //    );

    //    VECTOR dir = VNorm(VSub(tipPos, basePos));

    //    // 回転計算
    //    float yaw = atan2f(dir.x, dir.z);

    //    float clampled_dir_y = dir.y;
    //    if (clampled_dir_y > 1.0f) clampled_dir_y = 1.0f;
    //    if (clampled_dir_y < -1.0f) clampled_dir_y = -1.0f;

    //    float pitch = -asinf(clampled_dir_y);

    //    SetRotationPlayingEffekseer3DEffect(
    //        PlayshalshuEffectHandle,
    //        pitch,
    //        yaw,
    //        0.0f
    //    );

    //    // スケール
    //    float scale = 10.0f;
    //    SetScalePlayingEffekseer3DEffect(
    //        PlayshalshuEffectHandle,
    //        scale, scale, scale
    //    );
    //}

	//playFinisyuHandle = PlayEffekseer3DEffect(finisyuId);

	//SetPosPlayingEffekseer3DEffect(playFinisyuHandle, 0.0f, 50.0f, 0.0f);

	//SetRotationPlayingEffekseer3DEffect(playFinisyuHandle, 0.0f, DX_PI_F / 2.0f, 0.0f);

	//SetScalePlayingEffekseer3DEffect(playFinisyuHandle, 10.0f, 10.0f, 10.0f);
}

void EffekseerEffect::Draw(void)
{
	DrawEffekseer3D();
}

void EffekseerEffect::Release(void)
{
	Effkseer_End();
}

void EffekseerEffect::Delete(void)
{
	DeleteEffekseerEffect(playFinisyuHandle);
}

void EffekseerEffect::PlayComboEffect(const VECTOR& pos, float rotY)
{
	playFinisyuHandle = PlayEffekseer3DEffect(finisyuId);

    SetPosPlayingEffekseer3DEffect(
        playFinisyuHandle,
        pos.x,
        pos.y,
        pos.z
	);

    SetRotationPlayingEffekseer3DEffect(
        playFinisyuHandle,
        0.0f,
        rotY,
        0.0f
    );

    SetScalePlayingEffekseer3DEffect(
        playFinisyuHandle,
        50.0f, 50.0f, 50.0f
	);

    SetSpeedPlayingEffekseer3DEffect(
        playFinisyuHandle,
        0.2f
	);
}

void EffekseerEffect::PlayComboEffect2(const VECTOR& pos, float rotY)
{
    playFinisyu2Handle = PlayEffekseer3DEffect(finisyu2Id);

    SetPosPlayingEffekseer3DEffect(
        playFinisyu2Handle,
        pos.x,
        pos.y,
        pos.z
    );

    SetRotationPlayingEffekseer3DEffect(
        playFinisyu2Handle,
        0.0f,
        rotY,
        0.0f
    );

    SetScalePlayingEffekseer3DEffect(
        playFinisyu2Handle,
        50.0f, 50.0f, 50.0f
    );

    SetSpeedPlayingEffekseer3DEffect(
        playFinisyu2Handle,
        0.2f
	);
}

void EffekseerEffect::PlayComboEffect3(const VECTOR& pos, float rotY)
{
    playFinisyu3Handle = PlayEffekseer3DEffect(finisyu3Id);

    SetPosPlayingEffekseer3DEffect(
        playFinisyu3Handle,
        pos.x,
        pos.y,
        pos.z
    );

    SetRotationPlayingEffekseer3DEffect(
        playFinisyu3Handle,
        0.0f,
        rotY,
        0.0f
    );

    SetScalePlayingEffekseer3DEffect(
        playFinisyu3Handle,
        50.0f, 50.0f, 50.0f
    );

    SetSpeedPlayingEffekseer3DEffect(
        playFinisyu3Handle,
        0.2f
	);
}

void EffekseerEffect::PlayComboEffect4(const VECTOR& pos, float rotY)
{
    playFinisyu4Handle = PlayEffekseer3DEffect(finisyu4Id);

    SetPosPlayingEffekseer3DEffect(
        playFinisyu4Handle,
        pos.x,
        pos.y,
        pos.z
    );

    SetRotationPlayingEffekseer3DEffect(
        playFinisyu4Handle,
        0.0f,
        rotY,
        0.0f
    );

    SetScalePlayingEffekseer3DEffect(
        playFinisyu4Handle,
        50.0f, 50.0f, 50.0f
    );

    SetSpeedPlayingEffekseer3DEffect(
        playFinisyu4Handle,
        0.2f
	);
}

void EffekseerEffect::PlayComboEffect5(const VECTOR& pos, float rotY)
{
    playFinisyu5Handle = PlayEffekseer3DEffect(finisyu5Id);

    SetPosPlayingEffekseer3DEffect(
        playFinisyu5Handle,
        pos.x,
        pos.y,
        pos.z
    );

    SetRotationPlayingEffekseer3DEffect(
        playFinisyu5Handle,
        0.0f,
        rotY,
        0.0f
    );

    SetScalePlayingEffekseer3DEffect(
        playFinisyu5Handle,
        50.0f, 50.0f, 50.0f
    );

    SetSpeedPlayingEffekseer3DEffect(
        playFinisyu5Handle,
        0.2f
	);
}

void EffekseerEffect::PlayComboEffect6(const VECTOR& pos, float rotY)
{
    playFinisyu6Handle = PlayEffekseer3DEffect(finisyu6Id);

    SetPosPlayingEffekseer3DEffect(
        playFinisyu6Handle,
        pos.x,
        pos.y,
        pos.z
    );

    SetRotationPlayingEffekseer3DEffect(
        playFinisyu6Handle,
        0.0f,
        rotY,
        0.0f
    );

    SetScalePlayingEffekseer3DEffect(
        playFinisyu6Handle,
        50.0f, 50.0f, 50.0f
    );

    SetSpeedPlayingEffekseer3DEffect(
        playFinisyu6Handle,
        0.2f
	);
}
