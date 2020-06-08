using namespace std;

void CMap::Load(int num)
{
	if (!mpLoadMap)
		mpLoadMap = make_unique<CLoadMap>();

	//マップ情報を保存
	mpLoadMap->Load(num);

	mMapX = mpLoadMap->GetMapX();
	mMapZ = mpLoadMap->GetMapZ();
	mNumEnemy = mpLoadMap->GetMaxEnemy();

	mType = mpLoadMap->GetType();
	mBox = mpLoadMap->GetBox();
}

void CMap::Init()
{
	//乱数初期化(敵)
	srand((int)time(nullptr));

	//ポインタ作成
	mpPlayer = make_unique<CPlayer>();
	mpPlayer->Init();

	mpWall = make_unique<CWall>();
	mpGoal = make_unique<CGoal>();
	mpFloor = make_unique<CFloor>();
	mpBox = make_unique<CBox>();

	mpPlayer->SetPosition(XMFLOAT3((float)mpLoadMap->GetPlayerPosition().x, 0, (float)mpLoadMap->GetPlayerPosition().y));

	for (int i = 0; i < mNumEnemy; i++)
	{
		mpEnemyTroop.push_back(make_unique<CEnemyTroop>());
		mpEnemyTroop[i]->SetPosition(XMFLOAT3((float)mpLoadMap->GetEnemyPosition()[i].x, 0, (float)mpLoadMap->GetEnemyPosition()[i].y));
	}

	//mPstep.push_back(PlayerbyStep(XMINT2(mpPlayer->GetPosition().x, mpPlayer->GetPosition().z), CDirection::Down));

	//mBstep.push_back(BoxbyStep(CBoxType::None));

	//list<XMINT2> pos = mpLoadMap->GetFirstBoxPosition();

	//for (auto itr = pos.begin(); itr != pos.end(); ++itr)
	//	mBstep.at(0).backspace[itr->x][itr->y] = CBoxType::Exists;

	mEnemy = mNumEnemy;
	//mBackspaceLock = false;

	mMoving = false;
	mComplete = true;
	mLock = false;
	mStageIsOver = false;
	mMoveCount = 0;
	mMoveDirection = XMINT2(0, 0);
	mMoveOffset = XMFLOAT2(0.0f, 0.0f);
}

void CMap::Uninit()
{
	mpPlayer->Uninit();
	for (int i = 0; i < mNumEnemy; i++)
		mpEnemyTroop[i]->Uninit();

	mpEnemyTroop.clear();
	//mPstep.clear();
	//mBstep.clear();

	mpLoadMap->ReleaseMap();

	OutputDebugString("delete CMap\n");
}

void CMap::Update()
{
	mpPlayer->Update();
	mpGoal->Update();

	PlayerMoving();
	mpPlayer->MoveAnimation(mMoving);

	//if (!mBackspaceLock && CInput::GetKeyTrigger(VK_BACK) && mpPlayer->GetStep() > 0) {
	//	mpPlayer->CaculateStep(-1);

	//	mPstep.pop_back();
	//	mpPlayer->SetPosition(XMFLOAT3(mPstep.back().backspace.x,0, mPstep.back().backspace.y));
	//	mpPlayer->SetDirection(mPstep.back().direction);

	//	mBstep.pop_back();
	//	for (int z = 0; z < mMapZ; z++)
	//		for (int x = 0; x < mMapX; x++)
	//			mBox[z][x] = mBstep.at(mpPlayer->GetStep()).backspace[z][x];
	//}

	if (mNumEnemy > 0) {
		for (int i = 0; i < mNumEnemy; i++)
		{
			mpEnemyTroop[i]->Update(mType, mBox, mpPlayer->GetPosition());

			//敵を箱の当たり判定
			if (mpEnemyTroop[i]->Hit(mBox, mpPlayer->GetDirection(),XMINT2(mMapX,mMapZ)))
			{
				mEnemy--;

				//敵がゼロの場合、箱を引けなくなります
				if (mEnemy == 0)
				{
					mpPlayer->SetPullEnable(false);
					mLock = true;
				}
			}
		}
		//敵とプレイヤーの当たりを判定し、ゲームオーバー判定
		GameOver();
	}

	//プレイヤーの移動アニメーション完了判定
	if (MoveAnimation())
		mComplete = true;
	else
		mComplete = false;
}

void CMap::Draw()
{
	for (int z = 0; z < mMapZ; z++)
	{
		for (int x = 0; x < mMapX; x++)
		{
			//描画位置を中心にする
			XMFLOAT3 p;
			p.x = CELLSIZE * x - mMapX * CELLSIZE / 2;
			p.z = CELLSIZE * z - mMapZ * CELLSIZE / 2;

			//床描画
			if (mType[z][x] == CObjectType::Floor) {
				mpFloor->Draw(XMFLOAT3(p.x, -1.1f, -p.z));
			}
			//ゴール描画
			else if (mType[z][x] == CObjectType::Goal)
			{
				mpFloor->Draw(XMFLOAT3(p.x, -1.1f, -p.z));

				//箱と重なっている状態
				if (mBox[z][x] == CBoxType::Exists)
					mpGoal->Draw(XMFLOAT3(p.x, -1.0f, -p.z), true);
				else
					mpGoal->Draw(XMFLOAT3(p.x, -1.0f, -p.z), false);
			}
			//壁描画
			else if (mType[z][x] == CObjectType::Wall)
			{
				mpWall->Draw(XMFLOAT3(p.x, 0.0f, -p.z));
			}

			//箱描画
			if (mBox[z][x] == CBoxType::Exists)
			{
				//ゴールと重なっている状態
				if (mType[z][x] == CObjectType::Goal)
					mpBox->Draw(XMFLOAT3(p.x, 0.0f, -p.z), 1);

				//箱が動かない状態
				else if (BoxClogged(XMINT2(z, x)) && mLock) {
					mStageIsOver = true;
					mpBox->Draw(XMFLOAT3(p.x, 0.0f, -p.z), 2);
				}

				else
					mpBox->Draw(XMFLOAT3(p.x, 0.0f, -p.z), 0);
			}
			//箱の移動描画
			else if (mBox[z][x] == CBoxType::Moving)
			{
				mpBox->Draw(XMFLOAT3(p.x + mMoveOffset.x, 0.0f, -p.z - mMoveOffset.y), 0);
			}
		}
	}

	//プレイヤー描画
	XMFLOAT3 pp;
	pp.x = CELLSIZE * mpPlayer->GetPosition().x + mMoveOffset.x- mMapX * CELLSIZE / 2;
	pp.z = CELLSIZE * mpPlayer->GetPosition().z + mMoveOffset.y- mMapZ * CELLSIZE / 2;
	mpPlayer->Draw(XMFLOAT3(pp.x, 0.0f, -pp.z));

	//敵描画
	if (mNumEnemy > 0)
		for (int i = 0; i < mNumEnemy; i++)
		{
			pp.x = CELLSIZE * mpEnemyTroop[i]->GetPosition().x + mpEnemyTroop[i]->GetMoveOffset().x - mMapX * CELLSIZE / 2;
			pp.z = CELLSIZE * mpEnemyTroop[i]->GetPosition().z + mpEnemyTroop[i]->GetMoveOffset().y - mMapZ * CELLSIZE / 2;
			mpEnemyTroop[i]->Draw(XMFLOAT3(pp.x, 0.0f, -pp.z));
		}
}

void CMap::PlayerMoving()
{
	if (mComplete)
	{
		if (mpPlayer->GetDirection() == CDirection::Up && mpPlayer->GetMove())
			PlayerMove(0, -1);

		if (mpPlayer->GetDirection() == CDirection::Down && mpPlayer->GetMove())
			PlayerMove(0, 1);

		if (mpPlayer->GetDirection() == CDirection::Left && mpPlayer->GetMove())
			PlayerMove(-1, 0);

		if (mpPlayer->GetDirection() == CDirection::Right && mpPlayer->GetMove())
			PlayerMove(1, 0);

	}
}

void CMap::PlayerMove(int x, int y)
{
	//プレイヤーの一歩前
	XMINT2 front, front2, back, on;
	front.x = (int)mpPlayer->GetPosition().x + x;
	front.y = (int)mpPlayer->GetPosition().z + y;
	back.x = (int)mpPlayer->GetPosition().x - x;
	back.y = (int)mpPlayer->GetPosition().z - y;

	//一歩先が壁の場合　何もしない
	if (mType[front.y][front.x] == CObjectType::Wall)
		return;

	//箱との当たり判定
	if (mBox[front.y][front.x] == CBoxType::Exists || mBox[front.y][front.x] == CBoxType::Moving) {		

		front2.x = front.x + x;
		front2.y = front.y + y;

		//二歩先が空きスペースではない場合　何もしない
		if (mType[front2.y][front2.x] == CObjectType::Wall || mBox[front2.y][front2.x] == CBoxType::Exists)
			return;

		//箱を移動
		mBox[front2.y][front2.x] = CBoxType::Moving;

		//箱の元場所を消す
		mBox[front.y][front.x] = CBoxType::None;								
	}

	//箱を引く
	if (mpPlayer->GetPull() && mBox[back.y][back.x] == CBoxType::Exists) {

		if (mType[front.y][front.x] == CObjectType::Wall || mBox[front.y][front.x] == CBoxType::Exists)
			return;

		on.x = (int)mpPlayer->GetPosition().x;
		on.y = (int)mpPlayer->GetPosition().z;

		mBox[on.y][on.x] = CBoxType::Moving;
		mBox[back.y][back.x] = CBoxType::None;
	}


	mMoving = true;
	mMoveCount = 0;
	mMoveDirection = XMINT2(x, y);

	mpPlayer->SetPosition(XMFLOAT3((float)front.x, 0, (float)front.y));
	mpPlayer->CaculateStep(1);

	//mPstep.push_back(PlayerbyStep(XMINT2(front.x, front.y), mpPlayer->GetDirection()));

	//mBstep.push_back(BoxbyStep(CBoxType::None));
	//for (int z = 0; z < mMapZ; z++)
	//{
	//	for (int x = 0; x < mMapX; x++)
	//	{
	//		mBstep.at(mpPlayer->GetStep()).backspace[z][x] = mBox[z][x];

	//		if (mBstep.at(mpPlayer->GetStep()).backspace[z][x] == CBoxType::Moving)
	//			mBstep.at(mpPlayer->GetStep()).backspace[z][x] = CBoxType::Exists;
	//	}
	//}
}

bool CMap::MoveAnimation()
{
	//マスからマスへの移動をスムーズにする
	if (mMoving)
	{
		mMoveCount++;

		//移動中
		if (mMoveCount < mMoveDuration)
		{
			float rate = (float)mMoveCount / mMoveDuration;

			mMoveOffset.x = -mMoveDirection.x * CELLSIZE * (1.0f - rate);
			mMoveOffset.y = -mMoveDirection.y * CELLSIZE * (1.0f - rate);
		}
		//移動完了
		else
		{
			mMoveOffset = XMFLOAT2(0.0f, 0.0f);

			for (int z = 0; z < mMapZ; z++)
			{
				for (int x = 0; x < mMapX; x++)
				{
					if (mBox[z][x] == CBoxType::Moving)
					{
						mBox[z][x] = CBoxType::Exists;
					}
				}
			}

			mMoving = false;
			return true;
		}
		return false;
	}
	return true;
}

bool CMap::StageIsClear()
{
	for (int z = 0; z < mMapZ; z++)
	{
		for (int x = 0; x < mMapX; x++)
		{
			//全てゴールと全ての箱を重なっている状態とステージクリア
			if (mType[z][x] == CObjectType::Goal && mBox[z][x] == CBoxType::None || mType[z][x] != CObjectType::Goal && mBox[z][x] == CBoxType::Exists || mBox[z][x]==CBoxType::Moving)
				return false;
		}
	}
	return true;
}

void CMap::GameOver()
{
	for (int i = 0; i < mNumEnemy; i++)
	{
		//敵に当たられたらゲームオーバー
		if (mpEnemyTroop[i]->GetCollisionEnable() && CMath::Float3Equal(mpEnemyTroop[i]->GetPosition(), mpPlayer->GetPosition()))
		{
			CGameStatus::SetGameOver(true);
			CGameStatus::PlusScore(-50);
		}
	}
}

bool CMap::BoxClogged(XMINT2 position)
{
	if (mBox[position.x][position.y] == CBoxType::Exists)
	{
		CObjectType up, down, right, left;
		up = mType[position.x - 1][position.y];
		down = mType[position.x + 1][position.y];
		right = mType[position.x][position.y + 1];
		left = mType[position.x][position.y - 1];

		//箱は詰まっているとtrueリターン
		if ((up == CObjectType::Wall && left == CObjectType::Wall) ||
			(up == CObjectType::Wall && right == CObjectType::Wall) ||
			(down == CObjectType::Wall && left == CObjectType::Wall) ||
			(down == CObjectType::Wall && right == CObjectType::Wall))
		{
			return true;
		}
		else
			return false;
	}
}