//
//
//void CBEnemy::Init()
//{
//	m_Position = XMFLOAT3(0.0f, 1.0f, 5.0f);
//	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
//	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
//
//	mpCollision = new Collision();
//	mpCollision->SetPosition(m_Position);
//	mpCollision->SetRadius(0.5f);
//
//	mpModel = new CModel();
//	mpModel->Load("asset/miku_01.obj");
//}
//
//void CBEnemy::Uninit()
//{
//	delete mpCollision;
//
//	mpModel->Unload();
//	delete mpModel;
//}
//
//void CBEnemy::Update()
//{
//	mpCollision->SetPosition(m_Position);
//}
//
//void CBEnemy::Draw(XMFLOAT3 position)
//{
//	// マトリクス設定																
//	XMMATRIX world;
//	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
//	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
//	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
//	CRenderer::SetWorldMatrix(&world);
//
//	mpModel->Draw();
//}
//
//void CBEnemy::Create(XMFLOAT3 position, XMFLOAT3 rotation, XMFLOAT3 scale)
//{
//	m_Position = position;
//	m_Rotation = rotation;
//	m_Scale = scale;
//}