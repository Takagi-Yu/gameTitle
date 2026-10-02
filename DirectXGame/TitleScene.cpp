#include "TitleScene.h"

TitleScene::~TitleScene() {
	delete fade_;
	delete modelSkydome_;
	delete modelTitle_;
}

void TitleScene::Initialize() {
	camera_.Initialize();

	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);

	phase_ = Phase::kMain;

	// skydome生成
	skydome_ = new Skydome();
	// 初期化
	modelSkydome_ = Model::CreateFromOBJ("SkyDome", true);
	skydome_->Initialize(modelSkydome_, &camera_);

	modelTitle_ = Model::CreateFromOBJ("titleFont", true);
	worldTransformTitle_.Initialize();
	worldTransformTitle_.scale_ = {3.0f, 3.0f, 1.0f};
}

void TitleScene::Update() {
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

		if (fade_->IsFinished() == true) {
			finished_ = true;
		}

		break;
	}

	camera_.TransferMatrix();
	WorldTransformUpdate(worldTransformTitle_);
}

void TitleScene::Draw() {
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

		modelTitle_->Draw(worldTransformTitle_, camera_);

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
