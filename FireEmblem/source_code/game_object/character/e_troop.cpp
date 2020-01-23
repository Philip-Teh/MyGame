//============================================================================
//=																			 =
//=								ìGÇÃï∫ém									 =
//=																			 =
//============================================================================

#define L_2PI       (6.2830f)
#define ADJUST_RAD(e) (((e)<(0.0000f))?(e)+(L_2PI):((e)>(L_2PI))?(e)-(L_2PI):(e))

using namespace std;

CEnemyTroop::CEnemyTroop()
{
	mFile[0] = "asset/model/Eidle.fbx";
	mFile[1] = "asset/model/Erun.fbx";
	mFile[2] = "asset/model/Ejump.fbx";

	mMove = false;
	mEnable = true;
	mDirection = CDirection::Down;

	mpModel = make_unique<CModelAnimation>();
	mpModel->Load(mFile);

	mFrame = 0;
}

CEnemyTroop::~CEnemyTroop()
{
	mpModel->Unload();
	OutputDebugString("delete CEnemyTroop\n");
}

void CEnemyTroop::Update()
{
	if (mEnable)
	{
		mpModel->Update(1, mFrame);
		//Animation();
		mFrame++;
	}
}

void CEnemyTroop::Draw(XMFLOAT3 position)
{
	if (mEnable)
	{
		XMMATRIX world;
		world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		world *= XMMatrixTranslation(position.x, position.y, position.z);


		//m_Position = position;
		mpModel->Draw(world);
	}
}

void CEnemyTroop::Move(CObjectType** type, CBoxType** box, XMFLOAT3 Pposition)
{
	if (mEnable)
	{
		mFrame++;
		if (mFrame >= 30) mFrame = 0;

		if (mFrame == 0 && mDirection == CDirection::Down) {
			Patrol(XMINT2(0, 1), type, box, Pposition);
			mMove = true;
		}
		else if (mFrame == 0 && mDirection == CDirection::Up) {
			Patrol(XMINT2(0, -1), type, box, Pposition);
			mMove = true;
		}
		else if (mFrame == 0 && mDirection == CDirection::Left) {
			Patrol(XMINT2(-1, 0), type, box, Pposition);
			mMove = true;
		}
		else if (mFrame == 0 && mDirection == CDirection::Right) {
			Patrol(XMINT2(1, 0), type, box, Pposition);
			mMove = true;
		}
		else {
			mMove = false;
		}
	}
}

bool CEnemyTroop::Hit(CBoxType** box)
{
	if (mEnable)
	{
		XMINT2 p;
		p.x = m_Position.x;
		p.y = m_Position.z;

		if (box[p.y][p.x] == CBoxType::Exists)
		{
			mEnable = false;
			return true;
		}
		else return false;
	}
	else
		return false;
}

void CEnemyTroop::Patrol(XMINT2 position, CObjectType** type, CBoxType** box,XMFLOAT3 Pposition)
{
	if (mEnable)
	{
		XMINT2 front;
		front.x = m_Position.x + position.x;
		front.y = m_Position.z + position.y;

		int right = m_Position.x + 1;
		int down = m_Position.y + 1;
		int left = m_Position.x - 1;
		int up = m_Position.y - 1;

		//ìGÇÃélñ Ç™ï«Ç©î†ÇÃéûÅ@âΩÇ‡ÇµÇ»Ç¢
		/*if ((type[up][m_Position.x] == CObjectType::Wall || box[up][m_Position.x] == CBox::Exists) &&
			(type[down][m_Position.x] == CObjectType::Wall || box[down][m_Position.x] == CBox::Exists) &&
			(type[m_Position.y][left] == CObjectType::Wall || box[m_Position.y][left] == CBox::Exists) &&
			(type[m_Position.y][right] == CObjectType::Wall || box[m_Position.y][right] == CBox::Exists))
		{
			mMove = false;
			return;
		}*/

		if (type[front.y][front.x] == CObjectType::Wall || box[front.y][front.x] == CBoxType::Exists)
		{
			mDirection = Tracking(Pposition);
			m_Rotation.y = (float)mDirection;
			return;
		}

		m_Position.x = front.x;
		m_Position.z = front.y;
	}
}

CDirection CEnemyTroop::Tracking(XMFLOAT3 position)
{
	if (mDirection == CDirection::Down)
	{
		for (int i = 1; i < 6; i++)
		{
			XMFLOAT2 front;
			front.x = m_Position.x;
			front.y = m_Position.z + i;

			if (position.x == front.x && position.z == front.y)
				return CDirection::Down;

			else if (i == 5)
				return random();
		}
	}
	else if (mDirection == CDirection::Up)
	{
		for (int i = 1; i < 6; i++)
		{
			XMFLOAT2 front;
			front.x = m_Position.x;
			front.y = m_Position.z - i;

			if (position.x == front.x && position.z == front.y)
				return CDirection::Up;

			else if (i == 5)
				return random();
		}
	}
	else if (mDirection == CDirection::Left)
	{
		for (int i = 1; i < 6; i++)
		{
			XMFLOAT2 front;
			front.x = m_Position.x - i;
			front.y = m_Position.z;

			if (position.x == front.x && position.z == front.y)
				return CDirection::Left;

			else if (i == 5)
				return random();
		}
	}
	else if (mDirection == CDirection::Right)
	{
		for (int i = 1; i < 6; i++)
		{
			XMFLOAT2 front;
			front.x = m_Position.x + i;
			front.y = m_Position.z;

			if (position.x == front.x && position.z == front.y)
				return CDirection::Right;

			else if (i == 5)
				return random();

		}
	}
	else return random();
}

CDirection CEnemyTroop::DirectionConform(XMFLOAT3 position, int i, XMFLOAT2 front)
{
	if (position.x == front.x && position.z == front.y)
	{
		if(mDirection == CDirection::Down)
			return CDirection::Down;

		if (mDirection == CDirection::Up)
			return CDirection::Up;

		if (mDirection == CDirection::Left)
			return CDirection::Left;

		if (mDirection == CDirection::Right)
			return CDirection::Right;
	}	
	else if (i == 5)
		return random();
}

void CEnemyTroop::Animation()
{
	if (mMove)
		mpModel->Update(1, mFrame);

}