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

	mpShader = new CShader();
	mpShader->Init("shader_goal_vs.cso", "shader_goal_ps.cso");

	mpModel = make_unique<CModelAnimation>();
	mpModel->Load(mFile, mpShader);

	mpAnimation = make_unique<CModelAnimation>();
	mpAnimation->Load(mAnimation, mpShader);

	mRotate = 0.0f;
	mFrame = 0;
}

CGoal::~CGoal()
{
	mpModel->Unload();
	mpAnimation->Unload();
	mpShader->Uninit();
	delete mpShader;

	OutputDebugString("delete CGoal\n");
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

		XMMATRIX world,world1;
		world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

		world1 = XMMatrixScaling(m_Scale.x - 0.2f, m_Scale.y - 0.2f, m_Scale.z - 0.2f);
		world1 *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		world1 *= XMMatrixTranslation(m_Position.x, m_Position.y + 1, m_Position.z);

		CCamera* camera = CSceneManager::GetScene()->GetGameObject<CCamera>();

		XMFLOAT4X4 view, projection;
		XMStoreFloat4x4(&view, camera->GetViewMatrix());
		XMStoreFloat4x4(&projection, camera->GetProjectionMatrix());

		mpShader->SetCameraPosition(XMFLOAT4(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z, 0.0f));
		mpShader->SetViewMatrix(&view);
		mpShader->SetProjectionMatrix(&projection);

		mpModel->Draw(world);
		mpAnimation->Draw(world1);
	}
}
