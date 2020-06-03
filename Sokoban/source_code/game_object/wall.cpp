using namespace std;


CWall::CWall()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	mFile = "asset/model/wall3d.fbx";

	mpShader = make_shared<CShader>();
	mpShader->Init("shader_3d_vs.cso", "shader_3d_ps.cso");

	mpModel = make_unique<CModelAnimation>();
	mpModel->LoadSingle(mFile, mpShader);
}

CWall::~CWall()
{
	mpModel->Unload();
	mpShader->Uninit();

	OutputDebugString("delete CWall\n");
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

	CCamera* camera = CSceneManager::GetScene()->GetGameObject<CCamera>();

	XMFLOAT4X4 view, projection;
	XMStoreFloat4x4(&view, camera->GetViewMatrix());
	XMStoreFloat4x4(&projection, camera->GetProjectionMatrix());

	mpShader->SetCameraPosition(XMFLOAT4(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z, 0.0f));
	mpShader->SetViewMatrix(&view);
	mpShader->SetProjectionMatrix(&projection);

	mpModel->Draw(world);
}