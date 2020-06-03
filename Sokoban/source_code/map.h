#pragma once

//============================================================================
//=																			 =
//=							マップを管理するクラス							 =
//=																			 =
//============================================================================

#ifndef MAP_H_
#define MAP_H_

#define CELLSIZE (2.0f)	//マスのサイズ

class CMap : public CGameObject
{
public:
	//ステージナンバーをロード
	void Load(int num);

	void Init();
	void Uninit();
	void Update();
	void Draw();

	//ステージをクリアする判定
	bool StageIsClear();

	//ステップのゲッター
	const int& GetStep() { return mpPlayer->GetStep(); }

	//敵の数のゲッター
	const int& GetNumEnemy() { return mEnemy; }

	//敵の最大数のゲッター
	const int& GetMaxEnemy() { return mNumEnemy; }

	//ステージオーバーのゲッター
	const bool& GetStageIsOver() { return mStageIsOver; }

private:
	std::unique_ptr<CLoadMap> mpLoadMap = nullptr;
	std::unique_ptr<CPlayer> mpPlayer = nullptr;
	std::unique_ptr<CGoal> mpGoal = nullptr;
	std::vector<std::unique_ptr<CEnemyTroop>> mpEnemyTroop = {};
	std::unique_ptr<CFloor> mpFloor = nullptr;
	std::unique_ptr<CWall> mpWall = nullptr;
	std::unique_ptr<CBox> mpBox = nullptr;

	//箱以外のオブジェクトの位置を持つ変数
	CObjectType** mType = {};

	//箱の位置を持つ変数
	CBoxType** mBox = {};

	//プレイヤーマスからマスへ移動のフレーム
	const int mMoveDuration = 15;

	//マップの横幅
	int mMapX = 0;

	//マップの縦幅
	int mMapZ = 0;

	//ステージごと敵の最大数
	int mNumEnemy = 0;

	//敵の数
	int mEnemy = 0;

	//プレイヤーが移動中の判定
	bool mMoving = false;

	//マスからマスへ移動完了の判定
	bool mComplete = true;

	//引くことの鍵
	bool mLock = false;

	//ステージオーバーの判定
	bool mStageIsOver = false;

	//プレイヤー移動のカウント
	int mMoveCount = 0;

	//プレイヤー移動の方向
	XMINT2 mMoveDirection = XMINT2(0, 0);

	//プレイヤー移動の差引
	XMFLOAT2 mMoveOffset = XMFLOAT2(0.0f, 0.0f);

	//プレイヤーの移動処理
	void PlayerMoving();
	void PlayerMove(int x, int y);

	//プレイヤーの移動アニメーション
	bool MoveAnimation();

	//ゲームオーバー処理
	void GameOver();

	//箱が詰んだ判定
	bool BoxClogged(XMINT2 position);

	//bool mBackspaceLock = false;

	////プレイヤー移動を保存するリスト
	//struct PlayerbyStep {
	//	XMINT2 backspace;
	//	CDirection direction;

	//	PlayerbyStep(XMINT2 back, CDirection dir) {
	//		backspace = back;
	//		direction = dir;
	//	}
	//};
	//std::list<PlayerbyStep> mPstep;

	////箱の移動を保存するベクター
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
