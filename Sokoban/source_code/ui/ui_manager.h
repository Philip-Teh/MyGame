#pragma once

#ifndef UIMANAGER_H
#define UIMANAGER_H

	class CUIManager
	{
	public:
		CUIManager();
		~CUIManager();

		void Update();
		void Update(bool enable);

		//�X�R�A�ƃX�e�b�v�̕`��
		void DrawStatus(int score, int step);

		//�G�̐��̕`��
		void DrawEnemyStatus(int num);

		//�X�e�[�W�i���o�[�̕`��
		void DrawStageNum(int num);		

		//���j���[�̕`��
		void DrawMenu();

		//�G�̐���\��UI�̕\��
		void Appear();

		//�`���[�g���A����UI�\��
		void FirstDrawCancel() { mpHelp->FirstDrawCancel(); }
		void FirstDrawHelp() { mpHelp->FirstDraw(); }
		void SetKeyEnter(bool key) { mpHelp->SetKeyEnter(key); }

		//���j���[���J������
		const bool& GetPress(){	return mpMenu->GetKeyUp(); }

		//�������Ƃ̌���������Z�b�^�[
		void SetLock(bool lock) { mpPull->SetLock(lock); }

		//�X�e�[�W�Z���N�g�ɖ߂��Z�b�^�[�ƃQ�b�^�[
		const bool& GetReturn() { return mpReturn->GetKeyUp(); }
		void ReturnNay() { mpReturn->TabCancel(); }

		//�^�C�g���ɖ߂��Z�b�^�[�ƃQ�b�^�[
		const bool& GetReturnTitle() { return mpTitle->GetKeyUp(); }
		void ReturnTitleNay() { mpTitle->TabCancel(); }

		//�X�e�[�W�����[�h�̃Z�b�^�[�ƃQ�b�^�[
		const bool& GetReset() { return mpReset->GetKeyUp(); }
		void ResetNay() { mpReset->TabCancel(); }

		//�Q�[�����I������Q�b�^�[
		const bool& GetExit() { return mpExit->GetKeyUp(); }

	private:
		//�C���^�[�t�F�[�X
		std::unique_ptr<CScore> mpScore = nullptr;					//�X�R�A
		std::unique_ptr<CStep> mpStep = nullptr;					//�X�e�b�v
		std::unique_ptr<CNumEnemy> mpNumEnemy = nullptr;			//�G�̐�
		std::unique_ptr<CPull> mpPull = nullptr;					//�����\��
		std::unique_ptr<CStageNum> mpStageNum = nullptr;			//�X�e�[�W�i���o�[

		std::unique_ptr<CMenu> mpMenu = nullptr;					//���j���[
		std::unique_ptr<CHelp> mpHelp = nullptr;					//�Q�[������
		std::unique_ptr<CKeyInfo> mpKeyInfo = nullptr;				//�L�[����
		std::unique_ptr<CReturnStageSelect> mpReturn = nullptr;		//�X�e�[�W�Z���N�g�փ��^�[��
		std::unique_ptr<CReturnTitle> mpTitle = nullptr;			//�^�C�g���փ��^�[��

		std::unique_ptr<CReset> mpReset = nullptr;					//�X�e�[�W�����Z�b�g
		std::unique_ptr<CExit> mpExit = nullptr;					//�Q�[�����I��

		std::unique_ptr<CPause> mpPause = nullptr;					//�Q�[�����ꎞ��~

	};

#endif
