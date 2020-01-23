

void CPlayer::Init()
{
	mAnimation[0] = "asset/model/Hidle.fbx";
	mAnimation[1] = "asset/model/Hjump.fbx";
	mAnimation[2] = "asset/model/Hrun.fbx";

	m_Position = XMFLOAT3(0.0f, 0.0f, 1.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);

	mpModelA = new CModelAnimation();
	mpModelA->Load(mAnimation);
	mMove = false;

	mDirection = CDirection::Down;
}

void CPlayer::Uninit()
{
	mpModelA->Unload();
	delete mpModelA;
}

void CPlayer::Update()
{
	mFrame++;
	mpModelA->Update(0, mFrame);

	if (CInput::GetKeyTrigger('E'))
		mFrame = 0;

	if (CInput::GetKeyPress('E'))
		mpModelA->Update(1, mFrame);

	if (CInput::GetKeyPress('Z'))
		m_Rotation.y -= 0.1f;
	if (CInput::GetKeyPress('C'))
		m_Rotation.y += 0.1f;

	Move();
	Direction();

	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		CScene* scene = CSceneManager::GetScene();
		CBullet* bullet = scene->AddGameObject<CBullet>(CHARACTER);
		bullet->Create(m_Position);
	}

	//CMeshfield* field = CSceneManager::GetScene()->GetGameObject<CMeshfield>(WORLD);
	//m_Position.y = field->GetHeight(m_Position);
}

void CPlayer::Draw(XMFLOAT3 position)
{
	//m_Position = position;
	// マトリクス設定																
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(position.x, position.y, position.z);

	mpModelA->Draw(world);
}

void CPlayer::Move()
{
	mMove = false;
	if (CInput::GetKeyPress('W')) {
		mDirection = CDirection::Up;
		mpModelA->Update(2, mFrame);
		mMove = true;
	}
	if (CInput::GetKeyPress('S')) {
		mDirection = CDirection::Down;
		mpModelA->Update(2, mFrame);
		mMove = true;
	}
	if (CInput::GetKeyPress('A')) {
		mDirection = CDirection::Left;
		mpModelA->Update(2, mFrame);
		mMove = true;
	}
	if (CInput::GetKeyPress('D')){
		mDirection = CDirection::Right;
		mpModelA->Update(2, mFrame);
		mMove = true;
	}
}

void CPlayer::Direction()
{
	if(mDirection==CDirection::Down)
		m_Rotation.y = (float)CDirection::Down;
	if (mDirection == CDirection::Up)
		m_Rotation.y = (float)CDirection::Up;	
	if (mDirection == CDirection::Left)
		m_Rotation.y = (float)CDirection::Left;	
	if (mDirection == CDirection::Right)
		m_Rotation.y = (float)CDirection::Right;
}