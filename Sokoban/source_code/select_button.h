#pragma once

#ifndef STAGE_BUTTON_H_
#define STAGE_BUTTON_H_


#define BUTTON (3)	//�I���ł���X�e�[�W�̐�


//namespace UI
//{
	class CSelectButton
	{
	public:
		CSelectButton();
		~CSelectButton();

		void Update();
		void Draw();

	private:
		//�e�N�X�`��
		std::string mTexture[2] = {};

		//�e�N�X�`���|�C���^
		std::unique_ptr<CPolygon> mpPolygon[BUTTON + 2] = {};

		const float mSize = 100.0f;			//�e�N�X�`���̃T�C�Y
		const float mPositionX = 125.0f;	//�e�N�X�`����X�ʒu
		const float mPositionY = 300.0f;	//�e�N�X�`����Y�ʒu
		const float mSpace = 200.0f;		//�{�^���̊Ԃ̃X�y�[�X
		const int mButtonX = 5;				//��s�̃{�^���̐�

		//�t�@�C���p�X��ۑ����A�ǂݍ��݂̕ϐ�
		char mFilename[50] = "";

		//�I�񂾃{�^���̃i���o�[
		int mChoose = 0;

		//�N���A�����X�e�[�W�̔���
		bool mClear[BUTTON + 1] = {};

		//�L�[�{�[�h���͑���
		void KeyInput();
	};
//}

#endif // !STAGE_BUTTON_H_
