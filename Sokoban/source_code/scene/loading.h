#pragma once

//============================================================================
//=																			 =
//=							シーン　ローディング							 =
//=																			 =
//============================================================================

#ifndef LOADING_H_
#define LOADING_H_

//namespace Scene
//{
	class CLoading
	{
	public:
		static void Init();
		static void Uninit();
		static bool Update();
		static void Draw();

		static const bool& GetChange() { return mChanging; }
		static void SetChange(bool change) { mChanging = change; }

		static const bool& GetEnable() { return mEnable; }
		static void SetEnable(bool enable) { mEnable = enable; mFrame = 0; }

	private:
		static std::unique_ptr<CPolygon> mpPolygon[2];
		static float mMove;							//移動
		static int mFrame;							//待機フレーム
		static bool mMoveDirection;					//移動方向変換
		static bool mChanging;						//シーン遷移
		static bool mEnable;						//有効
		static int mPatternX, mPatternY;			//キャラクター画像パターン
	};
//}

#endif // !LOADING_H_
