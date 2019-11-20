
#define SPEED (0.1f)

void CPlayer::Init()
{
	mAnimation[0] = "asset/model/Hidle.fbx";
	mAnimation[1] = "asset/model/Hjump.fbx";
	mAnimation[2] = "asset/model/Hrun.fbx";

	m_Position = XMFLOAT3(0.0f, 1.0f, -5.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	mpModelA = new CModelAnimation();
	mpModelA->Load(mAnimation);
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

	if (CInput::GetKeyPress('W')) {
		m_Rotation.y = 110.0f;
		m_Position.z += 0.1f;
		mpModelA->Update(2, mFrame);
	}
	if (CInput::GetKeyPress('S')) {
		m_Rotation.y = 0.0f;
		m_Position.z -= 0.1f;
		mpModelA->Update(2, mFrame);
	}
	if (CInput::GetKeyPress('A')) {
		m_Rotation.y = -55.0f;
		m_Position.x -= 0.1f;
		mpModelA->Update(2, mFrame);
	}
	if (CInput::GetKeyPress('D')){
		m_Rotation.y = 55.0f;
		m_Position.x += 0.1f;
		mpModelA->Update(2, mFrame);
	}

	if (CInput::GetKeyPress('Z'))
		m_Rotation.y -= 0.1f;
	if (CInput::GetKeyPress('C'))
		m_Rotation.y += 0.1f;

	if (CInput::GetKeyTrigger(VK_SPACE))
	{
		CScene* scene = CSceneManager::GetScene();
		CBullet* bullet = scene->AddGameObject<CBullet>(CHARACTER);
		bullet->Create(m_Position);
	}

	CMeshfield* field = CSceneManager::GetScene()->GetGameObject<CMeshfield>(WORLD);
	m_Position.y = field->GetHeight(m_Position);
}

void CPlayer::Draw()
{
	// マトリクス設定																
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y+2, m_Position.z);

	mpModelA->Draw(world);
}