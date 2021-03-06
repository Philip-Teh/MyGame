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
	m_Scale = XMFLOAT3(0.5f, 0.5f, 0.5f);

	mFile = "asset/model/goal.fbx";
	mAnimation = "asset/model/goal1.fbx";

	//ポインタ作成
	mpShader = make_shared<CShader>();
	mpShader->Init("shader_goal_vs.cso", "shader_goal_ps.cso");

	mpModel = make_unique<CModelAnimation>();
	mpModel->LoadSingle(mFile, mpShader);

	mpAnimation = make_unique<CModelAnimation>();
	mpAnimation->LoadSingle(mAnimation, mpShader);

	mRotate = 0.0f;
	mFrame = 0;
}

CGoal::~CGoal()
{
	mpModel->Unload();
	mpAnimation->Unload();
	mpShader->Uninit();

	OutputDebugString("delete CGoal\n");
}

void CGoal::Update()
{
	//回転
	m_Rotation.y += mRotateSpeed;

	//アニメーション
	mpAnimation->Update(0, mFrame);
	mFrame++;
}

void CGoal::Draw(XMFLOAT3 position, bool trigger)
{
	if (!trigger)
	{
		m_Position = position;

		//マトリクス設定
		XMMATRIX world,world1;
		world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

		world1 = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
		world1 *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
		world1 *= XMMatrixTranslation(m_Position.x, m_Position.y + 1, m_Position.z);

		CCamera* camera = CSceneManager::GetScene()->GetGameObject<CCamera>();

		XMFLOAT4X4 view, projection;
		XMStoreFloat4x4(&view, camera->GetViewMatrix());
		XMStoreFloat4x4(&projection, camera->GetProjectionMatrix());

		//シェーダ設定
		mpShader->SetCameraPosition(XMFLOAT4(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z, 0.0f));
		mpShader->SetViewMatrix(&view);
		mpShader->SetProjectionMatrix(&projection);

		//描画
		mpModel->Draw(world);
		mpAnimation->Draw(world1);
	}
}
