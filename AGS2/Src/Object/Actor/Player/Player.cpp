#include "Player.h"
#include "../../../Application.h"
#include "../../../Input/InputManager.h"
#include "../../../Utility/AsoUtility.h"
#include "../../../Utility/MatrixUtility.h"
#include "../../Common/AnimationController.h"
#include "../../../Camera/Camera.h"

Player::Player(Camera* camera, int playerNo)
{
	camera_ = camera;
	playerNo_ = playerNo;
}

Player::~Player(void)
{
}

void Player::InitLoad(void)
{
	// モデルの読み込み
	modelId_ = MV1LoadModel((Application::PATH_MODEL + "Player/Player.mv1").c_str());
}

void Player::InitTransform(void)
{
	// モデルの角度
	angle_ = { 0.0f, 0.0f, 0.0f };
	localAngle_ = { 0.0f, AsoUtility::Deg2RadF(180.0f), 0.0f };

	// 角度を方向に変換する
	moveDir_ = { sinf(angle_.y), 0.0f, cosf(angle_.y) };
	preInputDir_ = moveDir_;

	// 行列の作成(子、親と指定すると親子の順に適用される)
	MATRIX mat = MatrixUtility::Multiplication(localAngle_, angle_);

	// 回転行列をモデルに反映
	MV1SetRotationMatrix(modelId_, mat);

	// モデルの位置設定（プレイヤー番号で初期位置を分ける）
	if (playerNo_ == 1)
	{
		pos_ = { -100.0f, 0.0f, 0.0f };  // プレイヤー1は左側
	}
	else
	{
		pos_ = { 100.0f, 0.0f, 0.0f };   // プレイヤー2は右側
	}
	MV1SetPosition(modelId_, pos_);

	// 当たり判定作成
	startCapsulePos_ = { 0.0f,110,0.0f };
	endCapsulePos_ = { 0.0f,30.0f,0.0f };
	capsuleRadius_ = 20.0f;

	// 当たり判定取るか
	isCollision_ = true;
}

void Player::InitAnimation(void)
{
	// モデルアニメーション制御の初期化
	animationController_ = new AnimationController(modelId_);

	// アニメーションの追加
	animationController_->Add(
		static_cast<int>(ANIM_TYPE::IDLE), 0.5f, Application::PATH_MODEL + "Player/Idle.mv1");
	animationController_->Add(
		static_cast<int>(ANIM_TYPE::WALK), 0.5f, Application::PATH_MODEL + "Player/Walk.mv1");

	// 待機アニメーションの再生
	animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));
}

void Player::InitPost(void)
{
	downKey_ = hitKey_ = 0;
}

void Player::Update(void)
{
	ActorBase::Update();

	// アニメーションの更新
	animationController_->Update();
}

void Player::Draw(void)
{
	ActorBase::Draw();

	// デバッグ表示の位置をプレイヤー番号で分ける
	int yPos = playerNo_ == 1 ? 50 : 70;
	DrawFormatString(
		0, yPos, 0xffffff,
		"P%d角度 :(%.1f, %.1f, %.1f)",
		playerNo_,
		AsoUtility::Rad2DegF(angle_.x),
		AsoUtility::Rad2DegF(angle_.y),
		AsoUtility::Rad2DegF(angle_.z)
	);
}

void Player::Release(void)
{
	ActorBase::Release();
}

void Player::Move(void)
{
	// カメラ角度を取得
	VECTOR cameraAngles = camera_->GetAngle();

	// 移動量
	const float MOVE_POW = 5.0f;
	VECTOR dir = AsoUtility::VECTOR_ZERO;

	// プレイヤー番号で入力デバイスを分ける
	if (playerNo_ == 1)
	{
		// プレイヤー1：WASD キー
		if (InputManager::GetInstance()->IsNew(KEY_INPUT_W)) { dir = { 0.0f, 0.0f, 1.0f }; }
		if (InputManager::GetInstance()->IsNew(KEY_INPUT_A)) { dir = { -1.0f, 0.0f, 0.0f }; }
		if (InputManager::GetInstance()->IsNew(KEY_INPUT_S)) { dir = { 0.0f, 0.0f, -1.0f }; }
		if (InputManager::GetInstance()->IsNew(KEY_INPUT_D)) { dir = { 1.0f, 0.0f, 0.0f }; }
	}

	downKey_ = hitKey_;
	hitKey_ = GetMouseInput();

	if ((downKey_ != hitKey_) != 0)
	{
		if (playerNo_ == 1)
		{
			playerNo_ = 2;
		}
		else
		{
			playerNo_ = 1;
		}
	}

	if (!AsoUtility::EqualsVZero(dir))
	{
		// 入力値の補完
		const float SMOOTH = 0.25f; // 小さいほど滑らかになる
		dir.x = preInputDir_.x + (dir.x - preInputDir_.x) * SMOOTH;
		dir.z = preInputDir_.z + (dir.z - preInputDir_.z) * SMOOTH;
		preInputDir_ = dir;

		// 正規化
		dir = VNorm(dir);

		// XYZの回転行列
		// XZ平面移動にする場合は、XZの回転値が入らないようにする
		MATRIX mat = MGetIdent();
		mat = MMult(mat, MGetRotY(cameraAngles.y));

		// 回転行列を使用して、ベクトルを回転させる
		moveDir_ = VTransform(dir, mat);

		// 一定スピードで移動量を決めて、座標に足して移動
		pos_ = VAdd(pos_, VScale(moveDir_, MOVE_POW));

		// 移動アニメーションの再生
		animationController_->Play(static_cast<int>(ANIM_TYPE::WALK));
	}
	else
	{
		// 待機アニメーションの再生
		animationController_->Play(static_cast<int>(ANIM_TYPE::IDLE));
	}
}