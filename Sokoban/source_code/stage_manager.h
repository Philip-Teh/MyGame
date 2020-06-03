#pragma once

//============================================================================
//=																			 =
//=							�X�e�[�W�}�l�[�W���[							 =
//=																			 =
//============================================================================

#ifndef STAGEMANAGER_H_
#define STAGEMANAGER_H_

class CStageManager : public CGameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	//�X�e�[�W�Z���N�g�֖߂��Q�b�^�[�ƃZ�b�^�[
	const bool& GetReturn() { return mpUIManager->GetReturn(); }
	void ReturnNay() { mpUIManager->ReturnNay(); }

	//�^�C�g���g�֖߂��Q�b�^�[�ƃZ�b�^�[
	const bool& GetReturnTitle() { return mpUIManager->GetReturnTitle(); }
	void ReturnTitleNay() { mpUIManager->ReturnTitleNay(); }

	//�X�e�[�W�ă��[�h
	void ResetStage();

private:
	//�}�b�v���Ǘ�����|�C���^
	std::unique_ptr<CMap> mpMap;

	//���[�U�[�C���^�[�t�F�[�X���Ǘ�����|�C���^
	std::unique_ptr<CUIManager> mpUIManager;

	//�X�e�[�W�N���A�V�[�����Ǘ�����|�C���^
	std::unique_ptr<CStageClear> mpStageClear;

	//�X�e�[�W�I�[�o�[�V�[�����Ǘ�����|�C���^
	std::unique_ptr<CStageOver> mpStageOver;

	//�G������锻��
	bool mEnemyAppear = false;

	//�X�e�[�W���N���A��������
	bool mStageClear = false;

	//�X�R�A�����Z����锻��
	bool mPlusScore = false;

	//���݂̃X�e�[�W
	int mStage = 0;

	//���̃X�e�[�W�̃v���O����
	void NextStage();

	//�X�R�A�����Z
	void ScoreCaculate();
};

#endif // !STAGEMANAGER_H_
