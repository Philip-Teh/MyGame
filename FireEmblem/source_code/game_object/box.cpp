using namespace std;

CBox::CBox()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	mFile[0] = "asset/model/box3d.fbx";
	mFile1[0] = "asset/model/box3dclear.fbx";

	for (int i = 0; i < 2; i++)
		mpModel[i] = make_unique<CModelAnimation>();

	mpModel[0]->Load(mFile);
	mpModel[1]->Load(mFile1);
}

CBox::~CBox()
{
	for (int i = 0; i < 2; i++)
		mpModel[i]->Unload();

	OutputDebugString("delete CBox\n");
}

void CBox::Update()
{

}

void CBox::Draw(XMFLOAT3 position,int num)
{
	m_Position = position;

	// マトリクス設定																
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);

	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	mpModel[num]->Draw(world);
}
