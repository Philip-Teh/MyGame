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
		std::unique_ptr<CScore> mpScore = nullptr;
		std::unique_ptr<CStep> mpStep = nullptr;
		std::unique_ptr<CNumEnemy> mpNumEnemy = nullptr;
		std::unique_ptr<CPull> mpPull = nullptr;
		std::unique_ptr<CStageNum> mpStageNum = nullptr;

		std::unique_ptr<CMenu> mpMenu = nullptr;
		std::unique_ptr<CHelp> mpHelp = nullptr;
		std::unique_ptr<CKeyInfo> mpKeyInfo = nullptr;
		std::unique_ptr<CReturnTitle> mpTitle = nullptr;
		std::unique_ptr<CReturnStageSelect> mpReturn = nullptr;

		std::unique_ptr<CReset> mpReset = nullptr;
		std::unique_ptr<CExit> mpExit = nullptr;

		std::unique_ptr<CPause> mpPause = nullptr;

	};

#endif
