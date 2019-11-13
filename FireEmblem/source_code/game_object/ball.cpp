#define SPEED (0.1f)

XMFLOAT3 pp;
CModelAnimation* modelani;

void CBall::Init()
{
	mQuaternion = XMQuaternionIdentity();

	m_Position = XMFLOAT3(0.0f, 1.0f, -5.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	//modelani = new ModelA();
	//modelani->Load("asset/model/ball.fbx");

	modelani = new CModelAnimation();
	modelani->Load("asset/model/ball.fbx");

	pp = m_Position;
}

XMFLOAT3 CBall::GetPosition()
{
	return pp;
}

void CBall::Uninit()
{
	//model->Unload();
	//delete model;
	modelani->Unload();
	delete modelani;
}

void CBall::Update()
{
	if (CInput::GetKeyPress('W')) 
	{
		XMFLOAT3 vz = XMFLOAT3(1.0f, 0.0f, 0.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);
		mQuaternion = XMQuaternionMultiply(mQuaternion, rotation);
		mQuaternion = XMQuaternionNormalize(mQuaternion);
	}
	if (CInput::GetKeyPress('S')) 
	{
		XMFLOAT3 vz = XMFLOAT3(-1.0f, 0.0f, 0.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);
		mQuaternion = XMQuaternionMultiply(mQuaternion, rotation);
		mQuaternion = XMQuaternionNormalize(mQuaternion);
	}
	if (CInput::GetKeyPress('A')) 
	{
		XMFLOAT3 vz = XMFLOAT3(0.0f, 0.0f, 1.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);
		mQuaternion = XMQuaternionMultiply(mQuaternion, rotation);
		mQuaternion = XMQuaternionNormalize(mQuaternion);
	}
	if (CInput::GetKeyPress('D')) 
	{
		XMFLOAT3 vz = XMFLOAT3(0.0f, 0.0f, -1.0f);
		XMVECTOR axis = XMLoadFloat3(&vz);
		XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.2f);
		mQuaternion = XMQuaternionMultiply(mQuaternion, rotation);
		mQuaternion = XMQuaternionNormalize(mQuaternion);
	}

	pp = m_Position;
}

void CBall::Draw()
{
	// マトリクス設定																
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationQuaternion(mQuaternion);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y + 2, m_Position.z);

	//CRenderer::SetWorldMatrix(&world);
	//model->Draw();
	modelani->Draw(world);
}