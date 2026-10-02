#pragma once
#include "Fade.h"
#include "KamataEngine.h"
#include "Math.h"
#include "Skydome.h"

using namespace KamataEngine;

class TitleScene {
public:
	// ゲームのフェーズ(型)
	enum class Phase {
		kFadeIn,  // フェードイン
		kMain,    // メイン部
		kFadeOut, // フェードアウト
	};

	~TitleScene();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
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
	Model* modelTitle_ = nullptr;

	WorldTransform worldTransformTitle_;
};
