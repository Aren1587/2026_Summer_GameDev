#pragma once
#include <string>
#include <map>
#include <vector>

class AnimationController
{

public:

	// アニメーションデータ
	struct Animation
	{
		int model = -1;
		int attachNo = -1;
		int animIndex = 0;
		float speed = 0.0f;
		float totalTime = 0.0f;
		float step = 0.0f;
	};

	struct BlendAnim {
		int attachIndex = -1;
		float blendRate = 0.0f;
		float playTime = 0.0f;
		bool isLoop = true;
	};

	// コンストラクタ
	AnimationController(int modelId);

	// デストラクタ
	~AnimationController(void);

	// 外部FBXからアニメーション追加
	void Add(int type, float speed, const std::string path);

	// 同じFBX内のアニメーションを準備
	void AddInFbx(int type, float speed, int animIndex);

	// アニメーション再生
	void Play(int type, bool isLoop = true);

	// アニメーションブレンド再生
	void PlayBlend(int fromAnim, int toAnim, float t); 

	void Update(void);
	void Release(void);

	// 再生中のアニメーション
	int GetPlayType(void) const;

	// 再生終了
	bool IsEnd(void) const;

	bool IsPlaying(void) const;

	void SetSpeed(float speed);

private:

	// アニメーションするモデルのハンドルID
	int modelId_;

	// 種類別のアニメーションデータ
	std::map<int, Animation> animations_;

	// 再生中のアニメーション
	int playType_;
	Animation playAnim_;

	// アニメーションをループするかしないか
	bool isLoop_;

	// アニメーション追加の共通処理
	void Add(int type, float speed, Animation& animation);

	float GetNowFrame() const;

	float GetTotalFrame() const;


	// 各アニメーションIDのモデルインデックス
	std::map<int, int> animHandles_; 

	// 現在ブレンド中のアニメーション
	std::vector<BlendAnim> blends_;   

	// 現在再生中のアニメーションID
	int currentAnim_ = -1;

	// アニメーション終了フラグ
	bool isEnd_ = false;

};
