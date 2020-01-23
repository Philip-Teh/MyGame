using namespace std;


void CSelector::Init()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);

	mModel[0] = "asset/model/selectorsky.fbx";
	mModel[1] = "asset/model/selectorfloor.fbx";

	for (int i = 0; i < 2; i++)
	{
		mpModelA[i] = make_unique<CModelAnimation>();
		mpModelA[i]->Load(&mModel[i]);
	}
}

void CSelector::Uninti()
{
	for (int i = 0; i < 2; i++)
		mpModelA[i]->Unload();
}

void CSelector::Update()
{
	if (CInput::GetKeyPress(VK_LEFT))
		m_Position.x--;
	if (CInput::GetKeyPress(VK_RIGHT))
		m_Position.x++;
	if (CInput::GetKeyPress(VK_UP))
		m_Position.z++;
	if (CInput::GetKeyPress(VK_DOWN))
		m_Position.z--;

	for (int i = 0; i < 2; i++)
		mpModelA[i]->Update(0, mFrame);

	mFrame++;
}

void CSelector::Draw()
{
	// マトリクス設定																
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	for (int i = 0; i < 2; i++)
		mpModelA[i]->Draw(world);
}