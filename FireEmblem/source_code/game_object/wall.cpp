using namespace std;


CWall::CWall()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	mFile[0] = "asset/model/wall3d.fbx";

	mpModel = make_unique<CModelAnimation>();
	mpModel->Load(mFile);
}

CWall::~CWall()
{
	mpModel->Unload();

	OutputDebugString("delete CMountain\n");
}

void CWall::Update()
{
	
}

void CWall::Draw(XMFLOAT3 position)
{
	m_Position = position;

	// マトリクス設定																
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	mpModel->Draw(world);
}