//============================================================================
//=																			 =
//=								“G‚Ì•ºŽm									 =
//=																			 =
//============================================================================

using namespace std;

CEnemyTroop::CEnemyTroop()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);

	mFile[0] = "asset/model/Eidle.fbx";
	mFile[1] = "asset/model/Erun.fbx";
	mFile[2] = "asset/model/Ejump.fbx";

	mTexture = "asset/texture/number/number.png";

	mMove = false;
	mEnable = true;
	mCollisionEnable = true;
	mHitting = false;

	mDirection = CDirection::Down;
	mCurrentDirection = CDirection::Down;
	mPlayerDirect1 = CDirection::Down;
	mPlayerDirect2 = CDirection::Down;

	mpShader = make_shared<CShader>();
	mpShader->Init("shader_3d_vs.cso", "shader_3d_ps.cso");

	mpModel = make_unique<CModelAnimation>();
	mpModel->Load(mFile, mpShader);

	mpEffect = make_unique<CEffect>();
	mpEffect->Init("asset/texture/hit.png", XMFLOAT2(25, 5), 5);

	mpBillboard = make_unique<CBillBoard>();
	mpBillboard->Init(mTexture, XMFLOAT2(NUMBER_SIZEX, NUMBER_HEIGHT));

	mFrame = 0;

	mpState = new CEnemyStateIdle();
	mAction = CAction::Idle;
	mActionChange = false;

	mpType = new CObjectType * [mRange];
	mpBox = new CBoxType * [mRange];

	for (int i = 0; i < mRange; i++)
	{
		mpType[i] = new CObjectType[mRange];
		mpBox[i] = new CBoxType[mRange];
	}

	mMoving = false;
	mComplete = true;
	mMoveCount = 0;
	mMoveDirection = XMINT2(0, 0);
	mMoveOffset = XMFLOAT2(0.0f, 0.0f);

	for (int i = 0; i < 4; i++)
	{
		mMovaD[i].direction = (CDirection)i;
		mMovaD[i].enable = false;
	}
}

CEnemyTroop::~CEnemyTroop()
{
	delete mpState;

	mpShader->Uninit();

	for (int i = 0; i < mRange; i++)
	{
		delete[] mpType[i];
		delete[] mpBox[i];
	}

	delete[]mpType;
	delete[]mpBox;

	mpModel->Unload();
	mpEffect->Uninit();
	mpBillboard->Uninit();

	OutputDebugString("delete CEnemyTroop\n");
}

void CEnemyTroop::Update(CObjectType** type, CBoxType** box, XMFLOAT3 playerposition)
{
	if (mEnable)
	{
		Action();

		switch (mAction)
		{
		case CAction::Idle:
			mpModel->Update(0, mFrame);
			break;
		case CAction::Move:
			if (mDirection != CDirection::None)
				mpModel->Update(1, mFrame);
			mDirection = Chase(XMINT2((int)playerposition.x, (int)playerposition.z), type, box);
			Move(type, box, XMINT2((int)playerposition.x, (int)playerposition.z));
			break;
		}
		Direction();
		mFrame++;

		if (MoveAnimation())
			mComplete = true;
		else
			mComplete = false;
	}
	mpEffect->Update();
}

void CEnemyTroop::Draw(XMFLOAT3 position)
{
	if (mEnable)
	{
		XMMATRIX world;
		world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

		if (mHitting)
			world *= XMMatrixTranslation(position.x, position.y, position.z);
		else
			world *= XMMatrixTranslation(position.x, position.y + 1.0f, position.z);

		CCamera* camera = CSceneManager::GetScene()->GetGameObject<CCamera>();

		XMFLOAT4X4 view, projection;
		XMStoreFloat4x4(&view, camera->GetViewMatrix());
		XMStoreFloat4x4(&projection, camera->GetProjectionMatrix());

		mpShader->SetCameraPosition(XMFLOAT4(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z, 0.0f));
		mpShader->SetViewMatrix(&view);
		mpShader->SetProjectionMatrix(&projection);

		mpModel->Draw(world);
		//mpBillboard->Draw(posiiton,)

	}
	mpEffect->Draw();
}

void CEnemyTroop::Action()
{
	if (mActionChange)
	{
		mpState->ActionTime();
		mActionChange = false;
	}

	mAction = mpState->Action(this);
}

void CEnemyTroop::ChangeState(CEnemyState* p)
{
	delete mpState;
	mpState = p;
	mActionChange = true;
}

bool CEnemyTroop::Hit(CBoxType** box,CDirection playerdirection,XMINT2 map)
{
	if (mEnable)
	{
		XMINT2 p;
		p.x = (int)m_Position.x;
		p.y = (int)m_Position.z;

		XMFLOAT3 effect;
		effect.x = CELLSIZE * m_Position.x - map.x * CELLSIZE / 2;
		effect.z = CELLSIZE * m_Position.z - map.y * CELLSIZE / 2;

		if (box[p.y][p.x] == CBoxType::Exists || box[p.y][p.x] == CBoxType::Moving)
		{
			mHitting = true;
			mCollisionEnable = false;
			//mpEffect->Create(effect);
		}

		if (mHitting)return DownDirection(playerdirection);
		else return false;
	}
	else
		return false;
}

void CEnemyTroop::Move(CObjectType** type, CBoxType** box, XMINT2 playerposition)
{
	if (mEnable && mComplete)
	{
		mFrame++;
		if (mFrame >= mMoveSpeed) mFrame = 0;

		if (mFrame == 0 && mDirection == CDirection::Down) {
			Patrol(XMINT2(0, 1), type, box, playerposition);
		}
		else if (mFrame == 0 && mDirection == CDirection::Up) {
			Patrol(XMINT2(0, -1), type, box, playerposition);
		}
		else if (mFrame == 0 && mDirection == CDirection::Left) {
			Patrol(XMINT2(-1, 0), type, box, playerposition);
		}
		else if (mFrame == 0 && mDirection == CDirection::Right) {
			Patrol(XMINT2(1, 0), type, box, playerposition);
		}
		//else {
		//	Patrol(XMINT2(0, 1), type, box, playerposition);
		//}
	}
}


void CEnemyTroop::Patrol(XMINT2 position, CObjectType** type, CBoxType** box, XMINT2 playerposition)
{
	if (mEnable && !mHitting)
	{
		XMINT2 front;
		front.x = (int)m_Position.x + position.x;
		front.y = (int)m_Position.z + position.y;

		CDirection direction = CDirection::None;

		if (m_Position.z > playerposition.y)
			direction = CDirection::Up;
		if (m_Position.z < playerposition.y)
			direction = CDirection::Down;

		if ((direction == CDirection::Up || direction == CDirection::Down) && m_Position.x == playerposition.x)
		{
			mDirection = Chase(playerposition, type, box);
		}

		if (Collision(front,type,box))
		{
			mDirection = Chase(playerposition, type, box);
			return;
		}

		mMoving = true;
		mMoveCount = 0;
		mMoveDirection = XMINT2(position.x, position.y);

		m_Position.x = (float)front.x;
		m_Position.z = (float)front.y;
	}
}

CDirection CEnemyTroop::Chase(XMINT2 playerposition,CObjectType** type, CBoxType** box)
{
	XMINT2 up, down, right, left;
	up.x = (int)m_Position.x;
	up.y = (int)m_Position.z - 1;
	down.x = (int)m_Position.x;
	down.y = (int)m_Position.z + 1;
	right.x = (int)m_Position.x + 1;
	right.y = (int)m_Position.z;
	left.x = (int)m_Position.x - 1;
	left.y = (int)m_Position.z;

	if (Collision(up, type, box))
		mMovaD[(int)CDirection::Up].enable = false;
	else
		mMovaD[(int)CDirection::Up].enable = true;

	if (Collision(down, type, box))
		mMovaD[(int)CDirection::Down].enable = false;
	else						
		mMovaD[(int)CDirection::Down].enable = true;

	if (Collision(left, type, box))
		mMovaD[(int)CDirection::Left].enable = false;
	else
		mMovaD[(int)CDirection::Left].enable = true;

	if (Collision(right, type, box))
		mMovaD[(int)CDirection::Right].enable = false;
	else
		mMovaD[(int)CDirection::Right].enable = true;

	int directionNum = 0;
	int enable1 = 0, enable2 = 0, enable3 = 0;

	for (int i = 0; i < 4; i++)
	{
		if (mMovaD[i].enable)
		{
			if (directionNum == 0)
			{
				enable1 = i;
			}
			if (directionNum == 1)
			{
				enable2 = i;
			}
			if (directionNum == 2)
			{
				enable3 = i;
			}
			directionNum++;
		}
	}

	XMINT2 PlayerPos = playerposition;
	CDirection directionLR = CDirection::None;
	CDirection directionUD = CDirection::None;
	CDirection randomdirection = CDirection::None;

	if (PlayerPos.x > m_Position.x)
		mPlayerDirect1 = CDirection::Right;
	else if (PlayerPos.x < m_Position.x)
		mPlayerDirect1 = CDirection::Left;
	else
		mPlayerDirect1 = CDirection::None;

	if (PlayerPos.y < m_Position.z)
		mPlayerDirect2 = CDirection::Up;
	else if (PlayerPos.y > m_Position.z)
		mPlayerDirect2 = CDirection::Down;
	else
		mPlayerDirect2 = CDirection::None;

	//if (m_Position.x != PlayerPos.x && m_Position.z != PlayerPos.y)
	//	direction = RandomDirection2(mPlayerDirect1, mPlayerDirect2);
	//else if (m_Position.z == PlayerPos.y)
	//	direction = mPlayerDirect1;
	//else if (m_Position.x == PlayerPos.x)
	//	direction = mPlayerDirect2;

	switch (directionNum)
	{
	case 0:
		return CDirection::None;
		break;
	case 1:
		return mMovaD[enable1].direction;
		break;
	case 2:
		randomdirection = RandomDirection2(mMovaD[enable1].direction, mMovaD[enable2].direction);

		if (mPlayerDirect1 == mMovaD[enable1].direction)directionLR = mPlayerDirect1;
		else if (mPlayerDirect1 == mMovaD[enable2].direction)directionLR = mPlayerDirect1;
		else directionLR = CDirection::None;

		if (mPlayerDirect2 == mMovaD[enable1].direction)directionUD = mPlayerDirect2;
		else if (mPlayerDirect2 == mMovaD[enable2].direction)directionUD = mPlayerDirect2;
		else directionUD = CDirection::None;

		if (directionLR != CDirection::None && directionUD != CDirection::None)return RandomDirection2(directionLR, directionUD);
		else if (directionLR != CDirection::None)return directionLR;
		else if (directionUD != CDirection::None)return directionUD;
		else return randomdirection;

		break;
	case 3:
		randomdirection = RandomDirection3(mMovaD[enable1].direction, mMovaD[enable2].direction, mMovaD[enable3].direction);

		if (mPlayerDirect1 == mMovaD[enable1].direction)directionLR = mPlayerDirect1;
		else if (mPlayerDirect1 == mMovaD[enable2].direction)directionLR = mPlayerDirect1;
		else if (mPlayerDirect1 == mMovaD[enable3].direction)directionLR = mPlayerDirect1;
		else directionLR = CDirection::None;

		if (mPlayerDirect2 == mMovaD[enable1].direction)directionUD = mPlayerDirect2;
		else if (mPlayerDirect2 == mMovaD[enable2].direction)directionUD = mPlayerDirect2;
		else if (mPlayerDirect2 == mMovaD[enable3].direction)directionUD = mPlayerDirect2;
		else directionUD = CDirection::None;

		if (directionLR != CDirection::None && directionUD != CDirection::None)return RandomDirection2(directionLR, directionUD);
		else if (directionLR != CDirection::None)return directionLR;
		else if (directionUD != CDirection::None)return directionUD;
		else return randomdirection;

		break;
	case 4:		
		return RandomDirection2(mPlayerDirect1, mPlayerDirect2);
		break;
	default:
		return CDirection::None;
		break;
	}
}


bool CEnemyTroop::Collision(XMINT2 position, CObjectType** type, CBoxType** box)
{
	if (type[position.y][position.x] == CObjectType::Wall
		|| box[position.y][position.x] == CBoxType::Exists
		|| box[position.y][position.x] == CBoxType::Moving)
		return true;
	else
		return false;
}

bool CEnemyTroop::MoveAnimation()
{
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

			mMoving = false;
			return true;
		}
		return false;
	}
	else return true;
}

bool CEnemyTroop::DownDirection(CDirection playerdirection)
{
	if (mDirection == CDirection::Down && playerdirection == CDirection::Down
		|| mDirection == CDirection::Up && playerdirection == CDirection::Up
		|| mDirection == CDirection::Left && playerdirection == CDirection::Left
		|| mDirection == CDirection::Right && playerdirection == CDirection::Right)
	{
		return Falling(true, true);
	}
	else if (mDirection == CDirection::Up && playerdirection == CDirection::Down
		|| mDirection == CDirection::Down && playerdirection == CDirection::Up
		|| mDirection == CDirection::Left && playerdirection == CDirection::Right
		|| mDirection == CDirection::Right && playerdirection == CDirection::Left)
	{
		return Falling(true, false);
	}
	else if (mDirection == CDirection::Down && playerdirection == CDirection::Right
		|| mDirection == CDirection::Up && playerdirection == CDirection::Left
		|| mDirection == CDirection::Left && playerdirection == CDirection::Down
		|| mDirection == CDirection::Right && playerdirection == CDirection::Up)
	{
		return Falling(false, true);
	}
	else if (mDirection == CDirection::Down && playerdirection == CDirection::Up
		|| mDirection == CDirection::Up && playerdirection == CDirection::Right
		|| mDirection == CDirection::Right && playerdirection == CDirection::Down
		|| mDirection == CDirection::Left && playerdirection == CDirection::Up)
	{
		return Falling(false, false);
	}
	else return true;
}

bool CEnemyTroop::Falling(bool rotation,bool minus)
{
	if (minus && rotation)
		m_Rotation.x -= mDownSpeed;

	else if (minus && !rotation)
		m_Rotation.z -= mDownSpeed;

	else if (!minus && rotation)
		m_Rotation.x += mDownSpeed;

	else if (!minus && !rotation)
		m_Rotation.z += mDownSpeed;

	if (m_Rotation.x >= mDown || m_Rotation.x <= -mDown || m_Rotation.z >= mDown || m_Rotation.z <= -mDown)
	{
		mEnable = false;
		return true;
	}
	else
		return false;
}

void CEnemyTroop::Direction()
{
	switch (mDirection)
	{
	case CDirection::Down:
		if (mCurrentDirection == CDirection::Left)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.down)
				mCurrentDirection = CDirection::Down;
		}
		else if (mCurrentDirection == CDirection::Right)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.down1)
			{
				mCurrentDirection = CDirection::Down;
				m_Rotation.y = mCurrentRotation.down;
			}
		}
		else if (mCurrentDirection == CDirection::Up)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.down)
				mCurrentDirection = CDirection::Down;
		}
		else
			m_Rotation.y = mCurrentRotation.down;
		break;

	case CDirection::Up:
		if (mCurrentDirection == CDirection::Left)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.up)
				mCurrentDirection = CDirection::Up;
		}
		else if (mCurrentDirection == CDirection::Right)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.up)
				mCurrentDirection = CDirection::Up;
		}
		else if (mCurrentDirection == CDirection::Down)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.up)
				mCurrentDirection = CDirection::Up;
		}
		else
			m_Rotation.y = mCurrentRotation.up;
		break;

	case CDirection::Left:
		if (mCurrentDirection == CDirection::Down)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.left)
				mCurrentDirection = CDirection::Left;
		}
		else if (mCurrentDirection == CDirection::Right)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.left)
				mCurrentDirection = CDirection::Left;
		}
		else if (mCurrentDirection == CDirection::Up)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.left)
				mCurrentDirection = CDirection::Left;
		}
		else
			m_Rotation.y = mCurrentRotation.left;
		break;

	case CDirection::Right:
		if (mCurrentDirection == CDirection::Down)
		{
			m_Rotation.y -= mTurnSpeed;
			if (m_Rotation.y <= mCurrentRotation.right1)
			{
				mCurrentDirection = CDirection::Right;
				m_Rotation.y = mCurrentRotation.right;
			}
		}
		else if (mCurrentDirection == CDirection::Left)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.right)
				mCurrentDirection = CDirection::Right;
		}
		else if (mCurrentDirection == CDirection::Up)
		{
			m_Rotation.y += mTurnSpeed;
			if (m_Rotation.y >= mCurrentRotation.right)
				mCurrentDirection = CDirection::Right;
		}
		else
			m_Rotation.y = mCurrentRotation.right;
		break;
	}
}