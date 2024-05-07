#include <Novice.h>
#include "func/Math.h"
#include "func/ScreenPrintf.h"

const char kWindowTitle[] = "GC2B_01_イイヅカ_ソラ_title";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		Matrix4x4 orthographicMatrix = Math::MakeOrthographicMatrix(-160.0f, 160.0f, 200.0f, 300.0f, 0.0f, 1000.0f);//正射影行列
		Matrix4x4 perspectiveFovMatrix = Math::MakePerspectiveFovMatrix(0.63f, 1.33f, 0.1f, 1000.0f);//透視投影行列
		Matrix4x4 viewportMatrix = Math::MakeViewportMatrix(100.0f, 200.0f, 600.0f, 300.0f, 0.0f, 1.0f);//ビューポートマトリックス
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		ScreenPrintf::MatrixScreenPrintf(0, 0, orthographicMatrix, "orthographicMatrix");//正射影行列
		ScreenPrintf::MatrixScreenPrintf(0, kRowHeight * 5, perspectiveFovMatrix, "perspectiveFovMatrix");//透視投影行列
		ScreenPrintf::MatrixScreenPrintf(0, kRowHeight * 10, viewportMatrix, "viewportMatrix");//ビューポートマトリックス

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
