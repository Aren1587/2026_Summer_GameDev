#include "../Utility/AsoUtility.h"
#include "../Manager/Input/KeyManager.h"
#include "Camera.h"
#include "../Object/Player/Player.h"
#include <EffekseerForDXLib.h>

Camera::Camera(void)
{
	// DxLibの初期設定では、
	// カメラの位置が x = 320.0f, y = 240.0f, z = (画面のサイズによって変化)、
	// 注視点の位置は x = 320.0f, y = 240.0f, z = 1.0f
	// カメラの上方向は x = 0.0f, y = 1.0f, z = 0.0f
	// 右上位置からZ軸のプラス方向を見るようなカメラ
}

Camera::~Camera(void)
{
}

void Camera::Init(void)
{
	// カメラの初期座標
	pos_ = DERFAULT_POS;

	// カメラの初期角度
	angles_ = DERFAULT_ANGLES;
}

void Camera::Update(void)
{
	if (follow_)
	{
		// プレイヤーの座標を取得
		VECTOR target = follow_->GetPos();

		// 目標カメラ座標（例：プレイヤーの真上や後方など、好みで調整）
		VECTOR targetPos = { target.x, target.y + 200.0f, target.z - 150.0f };

		// 線形補間で滑らかに追従
		float followSpeed = 0.1f; // 0.0f～1.0f（小さいほどゆっくり追従）
		pos_.x = pos_.x + (targetPos.x - pos_.x) * followSpeed;
		pos_.y = pos_.y + (targetPos.y - pos_.y) * followSpeed;
		pos_.z = pos_.z + (targetPos.z - pos_.z) * followSpeed;

		// カメラの位置・角度をDxLibに反映
		SetCameraPositionAndTarget_UpVecY(pos_, target);
	}
}

void Camera::SetBeforeDraw(void)
{
	// クリップ距離を設定する(SetDrawScreenでリセットされる)
	SetCameraNearFar(VIEW_NEAR, VIEW_FAR);

	switch (mode_)
	{
	case Camera::MODE::FIXED_POINT:
		SetBeforeDrawFixedPoint();
		break;
	case Camera::MODE::FREE:
		SetBeforeDrawFree();
		break;
	case Camera::MODE::FOLLOW:
		SetBeforeDrawFollow();
		break;

	}

	// カメラの設定(位置と角度による制御)
	SetCameraPositionAndAngle(
		pos_,
		angles_.x,
		angles_.y,
		angles_.z
	);
}

void Camera::SetBeforeDrawFixedPoint(void)
{
	// カメラの設定(位置と角度による制御)
	SetCameraPositionAndAngle(
		pos_,
		angles_.x,
		angles_.y,
		angles_.z
	);
}

void Camera::SetBeforeDrawFree(void)
{
	//auto& ins = InputManager::GetInstance();

	//// マウス座標取得
	//int mouseX, mouseY;
	//GetMousePoint(&mouseX, &mouseY);

	//if (firstMouse_) {
	//	prevMouseX_ = mouseX;
	//	prevMouseY_ = mouseY;
	//	firstMouse_ = false;
	//}

	//// マウス移動量
	//int deltaX = mouseX - prevMouseX_;
	//int deltaY = mouseY - prevMouseY_;

	//prevMouseX_ = mouseX;
	//prevMouseY_ = mouseY;

	//// マウス移動をカメラ回転に反映
	//angles_.y += deltaX * mouseSensitivity_; // 左右回転
	//angles_.x += deltaY * mouseSensitivity_; // 上下回転

	//// ピッチ角制限（上下向きすぎ防止）
	//if (angles_.x > DX_PI_F / 2.0f) angles_.x = DX_PI_F / 2.0f;
	//if (angles_.x < -DX_PI_F / 2.0f) angles_.x = -DX_PI_F / 2.0f;

	//// WASD で移動
	//float movePow = 3.0f;
	//if (ins.IsNew(KEY_INPUT_W)) { pos_.z += movePow; }
	//if (ins.IsNew(KEY_INPUT_A)) { pos_.x -= movePow; }
	//if (ins.IsNew(KEY_INPUT_S)) { pos_.z -= movePow; }
	//if (ins.IsNew(KEY_INPUT_D)) { pos_.x += movePow; }
	//if (ins.IsNew(KEY_INPUT_Q)) { pos_.y += movePow; }
	//if (ins.IsNew(KEY_INPUT_E)) { pos_.y -= movePow; }

	//// XYZ方向移動（既存処理）
	//MoveXYZDirection();
}

void Camera::DrawDebug(void)
{
	//DrawFormatString(
	//	0, 110, 0xffffff,
	//	"カメラ座標　 ：(%.1f, %.1f, %.1f)",
	//	pos_.x, pos_.y, pos_.z
	//);
	//DrawFormatString(
	//	0, 130, 0xffffff,
	//	"カメラ角度　 ：(%.1f, %.1f, %.1f)",
	//	AsoUtility::Rad2DegF(angles_.x),
	//	AsoUtility::Rad2DegF(angles_.y),
	//	AsoUtility::Rad2DegF(angles_.z)
	//);

	//DrawFormatString(
	//	0, 150, 0xffffff,
	//	"対象座標　 ：(%.1f, %.1f, %.1f)",
	//	follow_->GetPos().x, follow_->GetPos().y, follow_->GetPos().z
	//);

}

void Camera::Release(void)
{
}

const VECTOR& Camera::GetPos(void) const
{
	return pos_;
}

const VECTOR& Camera::GetAngles(void) const
{
	return angles_;
}

void Camera::ChangeMode(MODE mode)
{
	// カメラモードの変更
	
	mode_ = mode;
	// 変更時の初期化処理
	switch (mode_)
	{
	case Camera::MODE::FIXED_POINT:
		break;
	case Camera::MODE::FREE:
		break;
	case Camera::MODE::FOLLOW:
		break;
	}
}

void Camera::MoveXYZDirection(void)
{
	//auto& ins = InputManager::GetInstance();

	//// 矢印キーでカメラの角度を変える
	//float rotPow = 1.0f * DX_PI_F / 180.0f;
	//if (ins.IsNew(KEY_INPUT_DOWN)) { angles_.x += rotPow; }
	//if (ins.IsNew(KEY_INPUT_UP)) { angles_.x -= rotPow; }
	//if (ins.IsNew(KEY_INPUT_RIGHT)) { angles_.y += rotPow; }
	//if (ins.IsNew(KEY_INPUT_LEFT)) { angles_.y -= rotPow; }

	//// WASDでカメラを移動させる
	//const float movePow = 3.0f;
	//VECTOR dir = AsoUtility::VECTOR_ZERO;

	//if (ins.IsNew(KEY_INPUT_W)) { dir = AsoUtility::DIR_F; }
	//if (ins.IsNew(KEY_INPUT_A)) { dir = { -1.0f, 0.0f, 0.0f }; }
	//if (ins.IsNew(KEY_INPUT_S)) { dir = { 0.0f, 0.0f, -1.0f }; }
	//if (ins.IsNew(KEY_INPUT_D)) { dir = { 1.0f, 0.0f, 0.0f }; }

	//if (!AsoUtility::EqualsVZero(dir))

	//{
	//	// XYZの回転行列
	//	// XZ平面移動にする場合は、XZの回転を考慮しないようにする
	//	MATRIX mat = MGetIdent();
	//	//mat = MMult(mat, MGetRotX(angles_.x));
	//	mat = MMult(mat, MGetRotY(angles_.y));
	//	//mat = MMult(mat, MGetRotZ(angles_.z));
	//	// 
	//	// 回転行列を使用して、ベクトルを回転させる
	//	VECTOR moveDir = VTransform(dir, mat);

	//	// 方向×スピードで移動量を作って、座標に足して移動
	//	pos_ = VAdd(pos_, VScale(moveDir, movePow));
	//}
}

const VECTOR& Camera::GetTargetPos(void) const
{
	return targetPos_;
}

//void Camera::SetBeforeDrawFollow(void)
//{
//	if (GetJoypadNum() == 0)
//	{
//		MoveXYZDirection();
//	}
//		// 画面サイズ取得
//	int screenW, screenH;
//	GetScreenState(&screenW, &screenH, nullptr);
//
//	int mouseX, mouseY;
//	GetMousePoint(&mouseX, &mouseY);
//
//	// 画面中央
//	int centerX = screenW / 2;
//	int centerY = screenH / 2;
//
//	// マウス移動量（差分）
//	int deltaX = mouseX - centerX;
//	int deltaY = mouseY - centerY;
//
//	if (deltaX == 0 && deltaY == 0)
//	{
//		deltaX = KEY::GetIns().GetRightStickVec().x;
//		deltaY = KEY::GetIns().GetRightStickVec().y;
//		deltaX *= 8; deltaY *= 8;
//	}
//
//	// 視点回転
//	angles_.y += deltaX * mouseSensitivity_; // 左右
//	angles_.x += deltaY * mouseSensitivity_; // 上下
//
//	// ピッチ制限
//	if (angles_.x > DX_PI_F / 2.0f) angles_.x = DX_PI_F / 2.0f;
//	if (angles_.x < -DX_PI_F / 2.0f) angles_.x = -DX_PI_F / 2.0f;
//
//	// マウスを中央に戻す（カーソルは固定される）
//	SetMousePoint(centerX, centerY);
//
//	// 注視点の移動
//	VECTOR followPos = follow_->GetPos();
//	targetPos_ = followPos;
//
//	// カメラの移動
//	// カメラの回転行列を作成
//	MATRIX mat = MGetIdent();
//	mat = MMult(mat, MGetRotX(angles_.x));
//	mat = MMult(mat, MGetRotY(angles_.y));
//	//mat = MMult(mat, MGetRotZ(angles_.z));
//
//	VECTOR targetLocalRotPos = VTransform(FOLLOW_TARGET_LOCAL_POS, mat);
//	targetPos_ = VAdd(followPos, targetLocalRotPos);
//
//	// カメラの移動
//	// 相対座標を回転させて、回転後の相対座標を取得する
//	VECTOR cameraLocalRotPos = VTransform(FOLLOW_CAMERA_LOCAL_POS, mat);
//
//	// 相対座標からワールド座標に直して、カメラ座標とする
//	pos_ = VAdd(followPos, cameraLocalRotPos);
//
//	// 相対座標を回転させて、回転後の相対座標を取得する
//	VECTOR localRotPos = VTransform(FOLLOW_LOCAL_POS, mat);
//
//	// 相対座標からワールド座標に直して、カメラ座標とする
//	pos_ = VAdd(followPos, localRotPos);
//
//	// カメラの設定(位置と注視点による制御)
//	SetCameraPositionAndTargetAndUpVec(
//		pos_,
//		targetPos_,
//		{ 0.0f, 1.0f, 0.0f }
//	);
//}

void Camera::SetBeforeDrawFollow(void)

{
	if (lookAt_ == nullptr || follow_ == nullptr) { return; }

	auto& key = KEY::GetIns();

	// 入力ベクトル（右スティック→マウス→キーボード）
	VECTOR vec = { key.GetRightStickVec().y, key.GetRightStickVec().x, 0.0f };

	if (AsoUtility::VZERO(vec)) {
		vec = { key.GetMouceMove().y, key.GetMouceMove().x, 0.0f };
	}
	if (AsoUtility::VZERO(vec)) {
		if (key.GetInfo(KEY_TYPE::CAMERA_UP).now) { vec.x++; }
		if (key.GetInfo(KEY_TYPE::CAMERA_DOWN).now) { vec.x--; }
		if (key.GetInfo(KEY_TYPE::CAMERA_RIGHT).now) { vec.y++; }
		if (key.GetInfo(KEY_TYPE::CAMERA_LEFT).now) { vec.y--; }
	}

	float rotPow = 3.5f * DX_PI_F / 180.0f;

	if (!AsoUtility::VZERO(vec)) {
		vec = AsoUtility::VNormalize(vec); 
		vec = VScale(vec, rotPow);
		angles_ = VAdd(angles_, vec);

		// ヨー角度の範囲制限
		if (angles_.y >= AsoUtility::Deg2RadF(360.0f)) { angles_.y -= AsoUtility::Deg2RadF(360.0f); }
		if (angles_.y <= AsoUtility::Deg2RadF(0.0f)) { angles_.y += AsoUtility::Deg2RadF(360.0f); }
		// ピッチ角度の範囲制限
		if (angles_.x < AsoUtility::Deg2RadF(-30.0f)) { angles_.x = AsoUtility::Deg2RadF(-30.0f); }
		if (angles_.x > AsoUtility::Deg2RadF(60.0f)) { angles_.x = AsoUtility::Deg2RadF(60.0f); }
	}

	// カメラ座標・注視点計算
	MATRIX mat = MGetIdent();
	mat = MMult(mat, MGetRotX(angles_.x));
	mat = MMult(mat, MGetRotY(angles_.y));

	// カメラ座標（プレイヤーからのオフセット）
	pos_ = VAdd(*lookAt_, VTransform(LOOKAT_DIFF, mat));
	// 注視点（プレイヤー座標）
	targetPos_ = *lookAt_;

	// カメラの設定
	SetCameraPositionAndTargetAndUpVec(
		pos_,
		targetPos_,
		{ 0.0f, 1.0f, 0.0f }
	);

	// DXライブラリのカメラとEffekseerのカメラを同期する
	Effekseer_Sync3DSetting();
}


void Camera::SetFollow(Player* follow)
{
	if (this == nullptr) return;
	follow_ = follow;

	lookAt_ = follow_->GetPosPtr();
}