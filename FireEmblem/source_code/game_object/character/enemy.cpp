

void CEnemy::Init()
{
	m_Position = XMFLOAT3(0.0f, 1.0f, 5.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	collision = new Collision();
	collision->SetPosition(m_Position);
	collision->SetRadius(0.5f);

	model = new CModel();
	model->Load("asset/miku_01.obj");
}

void CEnemy::Uninit()
{
	delete collision;

	model->Unload();
	delete model;
}

void CEnemy::Update()
{
	collision->SetPosition(m_Position);
}

void CEnemy::Draw()
{
	// マトリクス設定																
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&world);

	model->Draw();
}

void CEnemy::Create(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale)
{
	m_Position = position;
	m_Rotation = rotation;
	m_Scale = scale;
}