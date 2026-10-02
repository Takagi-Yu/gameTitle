#include "ClearScene.h"
#include "GameScene.h"
#include "KamataEngine.h"
#include "TitleScene.h"
#include <Windows.h>

using namespace KamataEngine;

TitleScene* titleScene = nullptr;
GameScene* gameScene = nullptr;
ClearScene* clearScene = nullptr;

// シーン（型）
enum class Scene {
	kUnknown = 0,

	kTitle,
	kGame,
	kClear,
};

// 現在シーン（型）
Scene scene = Scene::kUnknown;

void ChangeScene();
void UpdateScene();
void DrawScene();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// エンジンの初期化
	KamataEngine::Initialize(L"LE3D_13_タカギ_ユウ");

	scene = Scene::kTitle;

	// DirectXCommonインスタンスの取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// ImGuiManagerインスタンスの取得
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();

	// タイトルシーンのインスタンス生成
	titleScene = new TitleScene();
	// タイトルシーンの初期化
	titleScene->Initialize();

	//// ゲームシーンのインスタンス生成
	// GameScene* gameScene = new GameScene();
	//// ゲームシーンの初期化
	// gameScene->Initialize();

	// メインループ
	while (true) {
		// エンジンの更新
		if (KamataEngine::Update()) {
			break;
		}

		ChangeScene();

		// ImGui受付開始
		imguiManager->Begin();
		UpdateScene();
		imguiManager->End();

		// ゲームシーンの更新
		// gameScene->Update();

		// 描画開始
		dxCommon->PreDraw();

		// ゲームシーンの描画
		// gameScene->Draw();

		DrawScene();

		imguiManager->Draw();

		// 描画終了
		dxCommon->PostDraw();

		//// ImGui受付開始
		// imguiManager->Begin();

		//// ゲームシーンの更新
		// gameScene->Update();

		//// ImGui受付終了
		// imguiManager->End();

		//// 描画開始
		// dxCommon->PreDraw();

		//// ゲームシーンの描画
		// gameScene->Draw();

		//// 軸表示の描画
		// AxisIndicator::GetInstance()->Draw();

		//// プリミティブ描画のリセット
		// PrimitiveDrawer::GetInstance()->Reset();

		//// ImGui描画
		// imguiManager->Draw();
		// imguiManager->Draw();

		//// 描画終了
		// dxCommon->PostDraw();
	}

	// ゲームシーンの解放
	delete gameScene;

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}

void ChangeScene() {
	switch (scene) {
	case Scene::kTitle:

		if (titleScene->IsFinished()) {
			// シーン変更
			scene = Scene::kGame;
			// 旧シーンの解放
			delete titleScene;
			titleScene = nullptr;
			// 新シーンの生成と初期化
			gameScene = new GameScene;
			gameScene->Initialize();
		}

		break;

	case Scene::kGame:

		if (gameScene->IsFinished()) {
			if (gameScene->nextScene_ == 1) {
				// シーン変更
				scene = Scene::kClear;
				// 旧シーンの解放
				delete gameScene;
				gameScene = nullptr;
				// 新シーンの生成と初期化
				clearScene = new ClearScene;
				clearScene->Initialize();
			}
		}

		break;
	case Scene::kClear:

		if (clearScene->IsFinished()) {
			// シーン変更
			scene = Scene::kTitle;
			// 旧シーンの解放
			delete clearScene;
			clearScene = nullptr;
			// 新シーンの生成と初期化
			titleScene = new TitleScene;
			titleScene->Initialize();
		}

		break;
	}
}


void UpdateScene() {
	switch (scene) {
	case Scene::kTitle:

		titleScene->Update();

		break;

	case Scene::kGame:

		gameScene->Update();

		break;
	case Scene::kClear:

		clearScene->Update();

		break;
	}
}

void DrawScene() {
	switch (scene) {
	case Scene::kTitle:

		titleScene->Draw();

		break;

	case Scene::kGame:

		gameScene->Draw();

		break;
	case Scene::kClear:

		clearScene->Draw();

		break;
	}
}

