
void CMap::Load(int num)
{
	if (!mpLoadMap)
		mpLoadMap = std::make_unique<CLoadMap>();

	mpLoadMap->Load(num);

	mMapX = mpLoadMap->GetMapX();
	mMapZ = mpLoadMap->GetMapZ();
	mNumEnemy = mpLoadMap->GetMaxEnemy();

	mType = mpLoadMap->GetType();
	mBox = mpLoadMap->GetBox();
}

void CMap::Init()
{
	std::srand((int)std::time(nullptr));

	mpPlayer = std::make_unique<CPlayer>();
	mpPlayer->Init();

	mpWall = std::make_unique<CWall>();
	mpGoal = std::make_unique<CGoal>();
	mpFloor = std::make_unique<CFloor>();
	mpBox = std::make_unique<CBox>();

	mpPlayer->SetPosition(XMFLOAT3(mpLoadMap->GetPlayerPosition().x, 0, mpLoadMap->GetPlayerPosition().y));

	for (int i = 0; i < mNumEnemy; i++)
	{
		mpEnemyTroop.push_back(std::make_unique<CEnemyTroop>());
		mpEnemyTroop[i]->SetPosition(XMFLOAT3(mpLoadMap->GetEnemyPosition()[i].x, 0, mpLoadMap->GetEnemyPosition()[i].y));
	}

	mPstep.push_back(PlayerbyStep(XMINT2(mpPlayer->GetPosition().x, mpPlayer->GetPosition().z), CDirection::Down));

	mBstep.push_back(BoxbyStep(CBoxType::None));

	std::list<XMINT2> pos = mpLoadMap->GetFirstBoxPosition();

	for (auto itr = pos.begin(); itr != pos.end(); ++itr)
		mBstep.at(0).backspace[itr->x][itr->y] = CBoxType::Exists;

	mKeyFrame = 0;
	mEnemy = mNumEnemy;
	mBackspaceLock = false;

	mMoving = false;
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
	mPstep.clear();
	mBstep.clear();

	mpLoadMap->ReleaseMap();

	OutputDebugString("delete CMap\n");
}

void CMap::Update()
{
	mpPlayer->Update();
	mpGoal->Update();

	PlayerMoving();

	if (!mBackspaceLock && CInput::GetKeyTrigger(VK_BACK) && mpPlayer->GetStep() > 0) {
		mpPlayer->CaculateStep(-1);

		mPstep.pop_back();
		mpPlayer->SetPosition(XMFLOAT3(mPstep.back().backspace.x,0, mPstep.back().backspace.y));
		mpPlayer->SetDirection(mPstep.back().direction);

		mBstep.pop_back();
		for (int z = 0; z < mMapZ; z++)
			for (int x = 0; x < mMapX; x++)
				mBox[z][x] = mBstep.at(mpPlayer->GetStep()).backspace[z][x];
	}

	if (mNumEnemy > 0) {
		for (int i = 0; i < mNumEnemy; i++)
		{
			mpEnemyTroop[i]->Update();
			mpEnemyTroop[i]->Move(mType, mBox, mpPlayer->GetPosition());

			if (mpEnemyTroop[i]->Hit(mBox))
			{
				mEnemy--;

				if (mEnemy == 0)
					mBackspaceLock = true;
			}
		}
		GameOver();
	}

	if (mMoving)
	{
		mMoveCount++;

		if (mMoveCount < mMoveDuration)
		{
			float rate = (float)mMoveCount / mMoveDuration;

			mMoveOffset.x = -mMoveDirection.x * CELLSIZE * (1.0f - rate);
			mMoveOffset.y = -mMoveDirection.y * CELLSIZE * (1.0f - rate);
		}
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
		}
	}

}

void CMap::Draw()
{
	for (int z = 0; z < mMapZ; z++)
	{
		for (int x = 0; x < mMapX; x++)
		{
			XMFLOAT3 p;
			p.x = CELLSIZE * x;
			p.z = CELLSIZE * z;

			if (mType[z][x] == CObjectType::Floor) {
				mpFloor->Draw(XMFLOAT3(p.x, -1.1f, -p.z));
			}
			else if (mType[z][x] == CObjectType::Goal)
			{
				mpFloor->Draw(XMFLOAT3(p.x, -1.1f, -p.z));

				if (mBox[z][x] == CBoxType::Exists)
					mpGoal->Draw(XMFLOAT3(p.x, -1.0f, -p.z), true);
				else
					mpGoal->Draw(XMFLOAT3(p.x, -1.0f, -p.z), false);
			}
			else if (mType[z][x] == CObjectType::Wall)
			{
				mpWall->Draw(XMFLOAT3(p.x, 0.0f, -p.z));
			}

			if (mBox[z][x] == CBoxType::Exists)
			{
				if(mType[z][x] == CObjectType::Goal)
					mpBox->Draw(XMFLOAT3(p.x, 0.0f, -p.z), 1);
				else
					mpBox->Draw(XMFLOAT3(p.x, 0.0f, -p.z), 0);
			}
			else if (mBox[z][x] == CBoxType::Moving)
			{
				mpBox->Draw(XMFLOAT3(p.x + mMoveOffset.x, 0.0f, -p.z - mMoveOffset.y), 0);
			}
		}
	}

	XMFLOAT3 pp;
	pp.x = CELLSIZE * mpPlayer->GetPosition().x + mMoveOffset.x;
	pp.z = CELLSIZE * mpPlayer->GetPosition().z + mMoveOffset.y;
	mpPlayer->Draw(XMFLOAT3(pp.x, 1.0f, -pp.z));


	if(mNumEnemy>0)
		for (int i = 0; i < mNumEnemy; i++)
		{
			pp.x = CELLSIZE * mpEnemyTroop[i]->GetPosition().x;
			pp.z = CELLSIZE * mpEnemyTroop[i]->GetPosition().z;
			mpEnemyTroop[i]->Draw(XMFLOAT3(pp.x, 2.0f, -pp.z));
		}
}

void CMap::PlayerMoving()
{
	mKeyFrame--;
	if (mKeyFrame <= 0)
		mKeyFrame = 0;

	if (mKeyFrame <= 0)
	{
		if (mpPlayer->GetDirection() == CDirection::Up && mpPlayer->GetMove())
		{
			PlayerMove(0, -1);
			mKeyFrame = KEYFRAME;
		}
		if (mpPlayer->GetDirection() == CDirection::Down && mpPlayer->GetMove())
		{
			PlayerMove(0, 1);
			mKeyFrame = KEYFRAME;
		}
		if (mpPlayer->GetDirection() == CDirection::Left && mpPlayer->GetMove())
		{
			PlayerMove(-1, 0);
			mKeyFrame = KEYFRAME;
		}
		if (mpPlayer->GetDirection() == CDirection::Right && mpPlayer->GetMove())
		{
			PlayerMove(1, 0);
			mKeyFrame = KEYFRAME;
		}
	}
}

void CMap::PlayerMove(int x, int y)
{
	//プレイヤーの一歩前
	int frontX = mpPlayer->GetPosition().x + x;
	int frontZ = mpPlayer->GetPosition().z + y;

	if (mType[frontZ][frontX] == CObjectType::Wall)						//一歩先が壁の場合　何もしない
		return;

	if (mBox[frontZ][frontX] == CBoxType::Exists) {							//箱との当たり判定

		int front2X = frontX + x;
		int front2Z = frontZ + y;

		//二歩先が空きスペースではない場合　何もしない
		if (mType[front2Z][front2X] == CObjectType::Wall || mBox[front2Z][front2X] == CBoxType::Exists)
			return;

		mBox[front2Z][front2X] = CBoxType::Moving;							//箱を移動
		mBox[frontZ][frontX] = CBoxType::None;								//箱の元場所を消す
	}
	mMoving = true;
	mMoveCount = 0;
	mMoveDirection = XMINT2(x, y);

	mpPlayer->SetPosition(XMFLOAT3(frontX, 0, frontZ));
	mpPlayer->CaculateStep(1);

	mPstep.push_back(PlayerbyStep(XMINT2(frontX, frontZ), mpPlayer->GetDirection()));

	mBstep.push_back(BoxbyStep(CBoxType::None));
	for (int z = 0; z < mMapZ; z++)
		for (int x = 0; x < mMapX; x++)
			mBstep.at(mpPlayer->GetStep()).backspace[z][x] = mBox[z][x];
}

bool CMap::StageIsClear()
{
	for (int z = 0; z < mMapZ; z++)
	{
		for (int x = 0; x < mMapX; x++)
		{
			if (mType[z][x] == CObjectType::Goal && mBox[z][x] == CBoxType::None || mType[z][x] != CObjectType::Goal && mBox[z][x] == CBoxType::Exists)
				return false;
		}
	}
	return true;
}

void CMap::GameClear()
{

}

void CMap::GameOver()
{
	for (int i = 0; i < mNumEnemy; i++)
	{
		if (mpEnemyTroop[i]->GetEnable() && CMath::Float3Equal(mpEnemyTroop[i]->GetPosition(), mpPlayer->GetPosition()))
		{
			CGameStatus::SetGameOver(true);
			CGameStatus::PlusScore(-100);
		}
	}
}