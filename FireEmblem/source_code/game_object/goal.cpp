//============================================================================
//=																			 =
//=							ゲームオブジェクト　ゴール						 =
//=																			 =
//============================================================================
using namespace std;

CGoal::CGoal()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(55.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(0.7f, 0.7f, 0.7f);

	mFile[0] = "asset/model/goal.fbx";
	mAnimation[0] = "asset/model/goal1.fbx";

	mpModel = make_unique<CModelAnimation>();
	mpModel->Load(mFile);

	mpAnimation = make_unique<CModelAnimation>();
	mpAnimation->Load(mAnimation);

	mRotate = 0.0f;
	mFrame = 0.0f;
}

CGoal::~CGoal()
{
	mpModel->Unload();
	mpAnimation->Unload();
	OutputDebugString("delete CAlliesTroop\n");
}

void CGoal::Update()
{
	m_Rotation.y += 0.03f;
	mpAnimation->Update(0, mFrame);
	mFrame++;
}

void CGoal::Draw(XMFLOAT3 position, bool trigger)
{
	if (!trigger)
	{
		m_Position = position;

		XMMATRIX world;
		world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

		mpModel->Draw(world);

		world = XMMatrixScaling(m_Scale.x - 0.2f, m_Scale.y - 0.2f, m_Scale.z - 0.2f);
		world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		world *= XMMatrixTranslation(m_Position.x, m_Position.y + 1, m_Position.z);

		mpAnimation->Draw(world);
	}
}
