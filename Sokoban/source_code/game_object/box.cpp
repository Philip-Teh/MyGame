using namespace std;

CBox::CBox()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	mFile[0] = "asset/model/box3d.fbx";
	mFile[1] = "asset/model/box3dclear.fbx";
	mFile[2] = "asset/model/box3dover.fbx";

	//ポインタ作成
	mpShader = make_shared<CShader>();
	mpShader->Init("shader_3d_vs.cso", "shader_3d_ps.cso");

	for (int i = 0; i < 3; i++)
	{
		mpModel[i] = make_unique<CModelAnimation>();
		mpModel[i]->LoadSingle(mFile[i],mpShader);
	}
}

CBox::~CBox()
{
	for (int i = 0; i < 3; i++)
		mpModel[i]->Unload();

	mpShader->Uninit();

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

	CCamera* camera = CSceneManager::GetScene()->GetGameObject<CCamera>();

	XMFLOAT4X4 view, projection;
	XMStoreFloat4x4(&view, camera->GetViewMatrix());
	XMStoreFloat4x4(&projection, camera->GetProjectionMatrix());

	//シェーダ設定
	mpShader->SetCameraPosition(XMFLOAT4(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z, 0.0f));
	mpShader->SetViewMatrix(&view);
	mpShader->SetProjectionMatrix(&projection);

	//描画
	mpModel[num]->Draw(world);
}
