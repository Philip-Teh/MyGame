
std::string gTexture = "asset/texture/plain.png";

void CPlain::Init()
{
	mpPolygon = std::make_unique<CPolygon>();


	//mpPolygon->Create(gTexture,XMFLOAT3(),)
}

void CPlain::Uninit()
{

}

void CPlain::Update()
{

}

void CPlain::Draw(XMFLOAT3 position)
{
	CCamera* camera;
	camera = CSceneManager::GetScene()->GetGameObject<CCamera>(FIRST);

	XMFLOAT3 Position(m_Position.x, m_Position.y, m_Position.z);

	//======= �����䔻��@======================//
	//======= ����������`�悵�Ȃ� =============//
	if (camera->Getvisivility(Position) == false)
	{
		return;
	}

	// �}�g���N�X�ݒ�																
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	CRenderer::SetWorldMatrix(&world);
}