#pragma once
#include "Fade.h"
#include "KamataEngine.h"
#include "Math.h"
#include "Skydome.h"

using namespace KamataEngine;

class ClearScene {
public:
	// ゲームのフェーズ
	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン
		kFadeOut, // フェードアウト
	};

	~ClearScene();

	void Initialize();

	void Update();

	void Draw();

	bool IsFinished() const { return finished_; }

private:
	Camera camera_;

	// 終了フラグ
	bool finished_ = false;

	Fade* fade_ = nullptr;

	Phase phase_;

	// 天球
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	Model* modelClear_ = nullptr;
	WorldTransform worldTransformClear_;
};
