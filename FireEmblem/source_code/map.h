#pragma once

//============================================================================
//=																			 =
//=									 Map									 =
//=																			 =
//============================================================================

#ifndef MAP_H_
#define MAP_H_

#define CELLSIZE (2.0f)
#define KEYFRAME (15)

class CMap : public CGameObject
{
public:
	void Load(int num);
	void Init();
	void Uninit();

	void Update();
	void Draw();
	bool StageIsClear();

	int GetStep() { return mpPlayer->GetStep(); }
	int GetNumEnemy() { return mEnemy; }

private:
	std::unique_ptr<CLoadMap> mpLoadMap;

	std::unique_ptr<CPlayer> mpPlayer;
	std::unique_ptr<CGoal> mpGoal;
	std::vector<std::unique_ptr<CEnemyTroop>> mpEnemyTroop;
	std::unique_ptr<CFloor> mpFloor;
	std::unique_ptr<CWall> mpWall;
	std::unique_ptr<CBox> mpBox;

	CObjectType** mType;
	CBoxType** mBox;

	const int mMoveDuration = 30;

	int mMapX = 0;
	int mMapZ = 0;
	int mNumEnemy = 0;
	int mEnemy = 0;
	bool mBackspaceLock = false;

	int mKeyFrame = 0;

	bool mMoving = false;
	int mMoveCount = 0;
	XMINT2 mMoveDirection = XMINT2(0, 0);
	XMFLOAT2 mMoveOffset = XMFLOAT2(0.0f, 0.0f);

	//プレイヤー移動を保存するリスト
	struct PlayerbyStep {
		XMINT2 backspace;
		CDirection direction;

		PlayerbyStep(XMINT2 back, CDirection dir) {
			backspace = back;
			direction = dir;
		}
	};
	std::list<PlayerbyStep> mPstep;

	//箱の移動を保存するベクター
	struct BoxbyStep {
		CBoxType backspace[MapSizeZ][MapSizeX] = {};

		BoxbyStep(CBoxType back) {
			for (int z = 0; z < MapSizeZ; z++)
				for (int x = 0; x < MapSizeX; x++)
					backspace[z][x] = back;
		}
	};
	std::vector<BoxbyStep> mBstep;

	void PlayerMoving();
	void PlayerMove(int x, int y);
	void GameClear();
	void GameOver();
};

#endif // !MAP_H_
