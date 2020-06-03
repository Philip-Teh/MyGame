using namespace std;

#define BILLBOARD_ALPHA (128)


void CBillBoard::Init(std::string texture, float sizex, float sizey)
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	VERTEX_3D mVertex[4];

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mVertex[j + 2 * i].Position = XMFLOAT3(-(sizex * 0.5f) + sizex * j, sizey * 0.5f - sizey * i, 0.0f);
			mVertex[j + 2 * i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			mVertex[j + 2 * i].TexCoord = XMFLOAT2((float)j, (float)i);
		}
	}

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = mVertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &mpVertexBuffer);

	unsigned short mpIndex[6];

	mpIndex[0] = 0;
	mpIndex[1] = 1;
	mpIndex[2] = 2;
	mpIndex[3] = 1;
	mpIndex[4] = 3;
	mpIndex[5] = 2;

	//インデックスバッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned short) * 6;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = mpIndex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &mpIndexBuffer);
	}

	mpTexture = new CTexture();
	mpTexture->LoadTexture(texture);

	mpShader = make_unique<CShader>();
	mpShader->Init("shader_3d_vs.cso", "shader_effect_ps.cso");

	mpPolygon = nullptr;
}

void CBillBoard::Init(std::string texture, XMFLOAT2 size)
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	mpPolygon = make_unique<CPolygon>();
	mpPolygon->InitBillBoard(texture, size.x, size.y);

	mpShader = make_unique<CShader>();
	mpShader->Init("shader_3d_vs.cso", "shader_effect_ps.cso");

	mpTexture = nullptr;
}

void CBillBoard::Uninit()
{
	if (mpIndexBuffer)
		mpIndexBuffer->Release();

	if (mpVertexBuffer)
		mpVertexBuffer->Release();

	if (mpTexture)
	{
		mpTexture->UnloadTexture();
		delete mpTexture;
	}

	if (mpPolygon)
		mpPolygon->Uninit();

	mpShader->Uninit();
}

void CBillBoard::Draw(XMFLOAT3 position)
{
	m_Position = position;

	CRenderer::SetVertexBuffers(mpVertexBuffer);
	CRenderer::SetIndexBuffer(mpIndexBuffer);

	XMMATRIX mtxInvView;
	XMMATRIX world;

	CRenderer::SetTexture(mpTexture, 0);

	mpCamera = CSceneManager::GetScene()->GetGameObject<CCamera>();

	mtxInvView = XMMatrixTranspose(mpCamera->GetViewMatrix());

	XMFLOAT4X4 mIV;
	XMStoreFloat4x4(&mIV, mtxInvView);

	mIV._14 = 0.0f;
	mIV._24 = 0.0f;
	mIV._34 = 0.0f;
	mIV._44 = 1.0f;


	mtxInvView = XMLoadFloat4x4(&mIV);

	world = mtxInvView;

	world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	
	XMFLOAT4X4 w;
	XMStoreFloat4x4(&w, world);

	CCamera* camera = CSceneManager::GetScene()->GetGameObject<CCamera>();

	XMFLOAT4X4 view, projection;
	XMStoreFloat4x4(&view, camera->GetViewMatrix());
	XMStoreFloat4x4(&projection, camera->GetProjectionMatrix());

	mpShader->SetCameraPosition(XMFLOAT4(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z, 0.0f));
	mpShader->SetViewMatrix(&view);
	mpShader->SetProjectionMatrix(&projection);

	mpShader->SetWorldMatrix(&w);
	mpShader->Set();

	CRenderer::DrawIndexed(6, 0, 0);
}

void CBillBoard::Draw(XMFLOAT3 position, int tx, int ty, int tw, int th)
{
	m_Position = position;

	mpPolygon->DrawBillBoard(position, tx, ty, tw, th);

	//CRenderer::SetVertexBuffers(mpVertexBuffer);
	//CRenderer::SetIndexBuffer(mpIndexBuffer);

	XMMATRIX mtxInvView;
	XMMATRIX world;

	//CRenderer::SetTexture(mpTexture, 0);

	mpCamera = CSceneManager::GetScene()->GetGameObject<CCamera>();

	mtxInvView = XMMatrixTranspose(mpCamera->GetViewMatrix());

	XMFLOAT4X4 mIV;
	XMStoreFloat4x4(&mIV, mtxInvView);

	mIV._14 = 0.0f;
	mIV._24 = 0.0f;
	mIV._34 = 0.0f;
	mIV._44 = 1.0f;

	mtxInvView = XMLoadFloat4x4(&mIV);

	world = mtxInvView;

	world *= XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	XMFLOAT4X4 w;
	XMStoreFloat4x4(&w, world);

	//CCamera* camera = CSceneManager::GetScene()->GetGameObject<CCamera>();

	XMFLOAT4X4 view, projection;
	XMStoreFloat4x4(&view, mpCamera->GetViewMatrix());
	XMStoreFloat4x4(&projection, mpCamera->GetProjectionMatrix());

	mpShader->SetCameraPosition(XMFLOAT4(mpCamera->GetPosition().x, mpCamera->GetPosition().y, mpCamera->GetPosition().z, 0.0f));
	mpShader->SetViewMatrix(&view);
	mpShader->SetProjectionMatrix(&projection);

	mpShader->SetWorldMatrix(&w);
	mpShader->Set();

	CRenderer::DrawIndexed(6, 0, 0);
}