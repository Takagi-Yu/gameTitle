#include "ClearScene.h"

ClearScene::~ClearScene() {
	delete fade_;
	delete modelSkydome_;
	delete modelClear_;
}

void ClearScene::Initialize() {

	camera_.Initialize();

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);

	phase_ = Phase::kFadeIn;

	// skydome生成
	skydome_ = new Skydome();
	// 初期化
	modelSkydome_ = Model::CreateFromOBJ("SkyDome", true);
	skydome_->Initialize(modelSkydome_, &camera_);

	modelClear_ = Model::CreateFromOBJ("clearFont", true);
	worldTransformClear_.Initialize();
	worldTransformClear_.scale_ = {3.0f, 3.0f, 1.0f};
}

void ClearScene::Update() {
	switch (phase_) {
	case Phase::kFadeIn:

		fade_->Update();

		if (fade_->IsFinished()) {
			phase_ = Phase::kMain;
		}

		break;
	case Phase::kMain:

		skydome_->Update();

		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
		}

		break;

	case Phase::kFadeOut:

		fade_->Update();

		if (fade_->IsFinished()) {
			finished_ = true;
		}

		break;
	}

	camera_.TransferMatrix();
	WorldTransformUpdate(worldTransformClear_);
}

void ClearScene::Draw() {
	switch (phase_) {
	case Phase::kFadeIn:

		Model::PreDraw();

		skydome_->Draw();

		Model::PostDraw();

		fade_->Draw();

		break;
	case Phase::kMain:

		Model::PreDraw();

		skydome_->Draw();

		modelClear_->Draw(worldTransformClear_, camera_);

		Model::PostDraw();

		break;
	case Phase::kFadeOut:

		Model::PreDraw();

		skydome_->Draw();

		Model::PostDraw();

		fade_->Draw();

		break;
	}
}
