#pragma once
#include <DxLib.h>

class Player;

class Camera
{

public:

	// カメラの初期座標
	static constexpr VECTOR DERFAULT_POS = { 0.0f,200.0f,-400.0f };

	// カメラの初期角度
	static constexpr VECTOR DERFAULT_ANGLES = {
		30.0f * DX_PI_F / 180.0f, 0.0f, 0.0f 
	};

	// 追従対象からカメラへの相対座標
	static constexpr VECTOR FOLLOW_CAMERA_LOCAL_POS = { 0.0f, 200.0f, -350.0f };

	// 追従対象から注視点への相対座標
	static constexpr VECTOR FOLLOW_TARGET_LOCAL_POS = { 0.0f, 0.0f, 150.0f };

	// カメラのクリップ範囲
	static constexpr float VIEW_NEAR = 10.0f;
	static constexpr float VIEW_FAR = 10000.0f;

	static constexpr VECTOR FOLLOW_LOCAL_POS = { 0.0f,200.0f,-400.0f };

	static constexpr VECTOR LOOKAT_DIFF = { 0.0f, 200.0f, -400.0f };

	// カメラモード
	enum class MODE
	{
		NONE,
		FIXED_POINT,	// 定点カメラ
		FREE,			// フリーモード
		FOLLOW,
	};

	// コンストラクタ
	Camera(void);

	// デストラクタ
	~Camera(void);

	// 初期化
	void Init(void);

	// 更新
	void Update(void);

	// 描画前のカメラ設定
	void SetBeforeDraw(void);
	void SetBeforeDrawFixedPoint(void);
	void SetBeforeDrawFree(void);
	void SetBeforeDrawFollow(void);

	// デバッグ用描画
	void DrawDebug(void);

	// 解放
	void Release(void);

	// 座標の取得
	const VECTOR& GetPos(void) const;

	// 角度の取得
	const VECTOR& GetAngles(void) const;

	// カメラモードの変更
	void ChangeMode(MODE mode);

	// XYZ方向に移動
	void MoveXYZDirection(void);

	// 注視点の取得
	const VECTOR& GetTargetPos(void) const;

	// 追従対象の設定
	void SetFollow(Player* follow);

	//void SetFollow(Player* player);

private:

	// カメラの追従対象
	Player* follow_;

	// 注視点
	VECTOR targetPos_;

	// カメラモード
	MODE mode_;

	// カメラの位置
	VECTOR pos_;

	// カメラの角度
	VECTOR angles_;

	VECTOR* lookAt_;

	VECTOR lookAtMultPos_;

	// カメラのマウス操作関係
	int prevMouseX_ = 0;
	int prevMouseY_ = 0;
	bool firstMouse_ = true;
	float mouseSensitivity_ = 0.005f; 
};
