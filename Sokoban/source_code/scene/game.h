#pragma once

//============================================================================
//=																			 =
//=								�V�[���@�Q�[��								 =
//=																			 =
//============================================================================

#ifndef GAME_H_
#define GAME_H_

class CGame : public CScene
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	std::string mTexture = "";

	std::unique_ptr<CCamera> mpCamera = nullptr;				//�J����
	std::unique_ptr<CStageManager> mpStageManager = nullptr;	//�X�e�[�W�}�l�[�W���[
	std::unique_ptr<CSkydome> mpSkydome = nullptr;				//�X�J�C�h�[��
	std::unique_ptr<CMeshfield> mpMeshField = nullptr;			//���b�V���t�B�[��

	std::unique_ptr<CGameOver> mpGameOver = nullptr;			//�Q�[���I�[�o�[
	std::unique_ptr<CReplay> mpReplay = nullptr;				//���v���C

	bool mGameOver = false;

	//�X�e�[�W�Z���N�g�֖߂�����
	bool ReturnStageSelect();

	//�^�C�g���֖߂�����
	bool ReturnTitle();
};

#endif // !GAME_H_

