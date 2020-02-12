#pragma once




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

		static bool GetChange() { return mChanging; }
		static void SetChange(bool change) { mChanging = change; }

		static bool GetEnable() { return mEnable; }
		static void SetEnable(bool enable) { mEnable = enable; mFrame = 0; }

	private:
		static std::unique_ptr<CPolygon> mpPolygon[2];
		static float mMove;
		static int mFrame;
		static bool mMoveDirection;					//�ړ������ϊ�
		static bool mChanging;						//�V�[���J��
		static bool mEnable;
		static int mPatternX, mPatternY;
	};
//}

#endif // !LOADING_H_
