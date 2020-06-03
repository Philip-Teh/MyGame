#pragma once

//============================================================================
//=																			 =
//=							�}�b�v���Ǘ�����N���X							 =
//=																			 =
//============================================================================

#ifndef MAP_H_
#define MAP_H_

#define CELLSIZE (2.0f)	//�}�X�̃T�C�Y

class CMap : public CGameObject
{
public:
	//�X�e�[�W�i���o�[�����[�h
	void Load(int num);

	void Init();
	void Uninit();
	void Update();
	void Draw();

	//�X�e�[�W���N���A���锻��
	bool StageIsClear();

	//�X�e�b�v�̃Q�b�^�[
	const int& GetStep() { return mpPlayer->GetStep(); }

	//�G�̐��̃Q�b�^�[
	const int& GetNumEnemy() { return mEnemy; }

	//�G�̍ő吔�̃Q�b�^�[
	const int& GetMaxEnemy() { return mNumEnemy; }

	//�X�e�[�W�I�[�o�[�̃Q�b�^�[
	const bool& GetStageIsOver() { return mStageIsOver; }

private:
	std::unique_ptr<CLoadMap> mpLoadMap = nullptr;
	std::unique_ptr<CPlayer> mpPlayer = nullptr;
	std::unique_ptr<CGoal> mpGoal = nullptr;
	std::vector<std::unique_ptr<CEnemyTroop>> mpEnemyTroop = {};
	std::unique_ptr<CFloor> mpFloor = nullptr;
	std::unique_ptr<CWall> mpWall = nullptr;
	std::unique_ptr<CBox> mpBox = nullptr;

	//���ȊO�̃I�u�W�F�N�g�̈ʒu�����ϐ�
	CObjectType** mType = {};

	//���̈ʒu�����ϐ�
	CBoxType** mBox = {};

	//�v���C���[�}�X����}�X�ֈړ��̃t���[��
	const int mMoveDuration = 15;

	//�}�b�v�̉���
	int mMapX = 0;

	//�}�b�v�̏c��
	int mMapZ = 0;

	//�X�e�[�W���ƓG�̍ő吔
	int mNumEnemy = 0;

	//�G�̐�
	int mEnemy = 0;

	//�v���C���[���ړ����̔���
	bool mMoving = false;

	//�}�X����}�X�ֈړ������̔���
	bool mComplete = true;

	//�������Ƃ̌�
	bool mLock = false;

	//�X�e�[�W�I�[�o�[�̔���
	bool mStageIsOver = false;

	//�v���C���[�ړ��̃J�E���g
	int mMoveCount = 0;

	//�v���C���[�ړ��̕���
	XMINT2 mMoveDirection = XMINT2(0, 0);

	//�v���C���[�ړ��̍���
	XMFLOAT2 mMoveOffset = XMFLOAT2(0.0f, 0.0f);

	//�v���C���[�̈ړ�����
	void PlayerMoving();
	void PlayerMove(int x, int y);

	//�v���C���[�̈ړ��A�j���[�V����
	bool MoveAnimation();

	//�Q�[���I�[�o�[����
	void GameOver();

	//�����l�񂾔���
	bool BoxClogged(XMINT2 position);

	//bool mBackspaceLock = false;

	////�v���C���[�ړ���ۑ����郊�X�g
	//struct PlayerbyStep {
	//	XMINT2 backspace;
	//	CDirection direction;

	//	PlayerbyStep(XMINT2 back, CDirection dir) {
	//		backspace = back;
	//		direction = dir;
	//	}
	//};
	//std::list<PlayerbyStep> mPstep;

	////���̈ړ���ۑ�����x�N�^�[
	//struct BoxbyStep {
	//	CBoxType backspace[MapSizeZ][MapSizeX] = {};

	//	BoxbyStep(CBoxType back) {
	//		for (int z = 0; z < MapSizeZ; z++)
	//			for (int x = 0; x < MapSizeX; x++)
	//				backspace[z][x] = back;
	//	}
	//};
	//std::vector<BoxbyStep> mBstep;
};

#endif // !MAP_H_
