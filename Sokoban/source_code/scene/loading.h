#pragma once

//============================================================================
//=																			 =
//=							�V�[���@���[�f�B���O							 =
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
		static float mMove;							//�ړ�
		static int mFrame;							//�ҋ@�t���[��
		static bool mMoveDirection;					//�ړ������ϊ�
		static bool mChanging;						//�V�[���J��
		static bool mEnable;						//�L��
		static int mPatternX, mPatternY;			//�L�����N�^�[�摜�p�^�[��
	};
//}

#endif // !LOADING_H_
