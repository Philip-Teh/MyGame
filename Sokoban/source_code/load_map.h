#pragma once

//============================================================================
//=																			 =
//=							�N���X�@���[�h�}�b�v							 =
//=																			 =
//============================================================================

#ifndef LOADMAP_H_
#define LOADMAP_H_

class CLoadMap
{
public:
	void Load(int mapID);

	void ReleaseMap(void);
	
	//�I�u�W�F�N�g�̃Q�b�^�[
	CObjectType** GetType() { return mpType; }

	//���̃Q�b�^�[
	CBoxType** GetBox() { return mpBox; }

	//�}�b�v�̉����Q�b�^�[
	const int& GetMapX() { return mMapX; }

	//�}�b�v�̏c���̃Q�b�^�[
	const int& GetMapZ() { return mMapZ; }

	//�G�̍ő吔�̃Q�b�^�[
	const int& GetMaxEnemy() { return mMaxEnemyTroop; }

	XMINT2 GetPlayerPosition() { return mPlayerPosition; }
	std::vector<XMINT2> GetEnemyPosition() { return mEnemyPosition; }

private:
	std::string mFilename = "";
	char mMap[MapSizeX * MapSizeZ] = {};	//�}�b�v�̍ő�T�C�Y
	int mMapX = 0;							//�}�b�v�̉��T�C�Y
	int mMapZ = 0;							//�}�b�v�̏c�T�C�Y
	int mMaxEnemyTroop = 0;					//�G�̍ő吔

	XMINT2 mPlayerPosition = XMINT2(0, 0);
	std::vector<XMINT2> mEnemyPosition;

	CObjectType** mpType = nullptr;			//���ȊO�̕ۑ��|�C���^
	CBoxType** mpBox = nullptr;				//���̕ۑ��|�C���^

	void Init();
	void SetPlayerPosition(XMINT2 p) { mPlayerPosition = p; }
	void SetEnemyPosition(XMINT2 p) { mEnemyPosition.push_back(p); }
};

#endif // !LOADMAP_H_
