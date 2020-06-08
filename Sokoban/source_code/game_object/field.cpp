using namespace std;

void CField::Init(std::string texture)
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(2.0f, 2.0f, 2.0f);

	//頂点計算
	mNumVertices = (mNum.x + 1) * (mNum.y + 1);

	VERTEX_3D vertex[4];

	for (int i = 0; i < mNum.x + 1; i++)
	{
		for (int j = 0; j < mNum.y + 1; j++)
		{
			//DirectX Math ライブラリ
			vertex[j + (mNum.x + 1) * i].Position = XMFLOAT3(-(mSize.x * mNum.x * 0.5f) + mSize.x * j, 0.0f, (mSize.y * mNum.y * 0.5f) - mSize.y * i);		//位置
			vertex[j + (mNum.x + 1) * i].Normal = XMFLOAT3(0, 1, 0);																						//法線
			vertex[j + (mNum.x + 1) * i].Diffuse = XMFLOAT4(1, 1, 1, 1);																					//色
			vertex[j + (mNum.x + 1) * i].TexCoord = XMFLOAT2((float)j, (float)i);																			//テクスチャ座標
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
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &mpVertexBuffer);

	//ポインタ作成
	mpShader = make_unique<CShader>();
	mpShader->Init("shader_3d_vs.cso", "shader_3d_ps.cso");

	//テクスチャ読み込み
	mpTexture = new CTexture();
	mpTexture->LoadTexture(texture);
}

void CField::Uninit()
{
	if (mpVertexBuffer)
		mpVertexBuffer->Release();

	mpShader->Uninit();

	mpTexture->UnloadTexture();
	delete mpTexture;

	OutputDebugString("delete CField\n");
}

void CField::Update()
{

}

void CField::Draw(XMFLOAT3 position,float rotate)
{
	m_Position = position;

	//マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y + rotate, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

	//シェーダ設定
	XMFLOAT4X4 worldf;
	XMStoreFloat4x4(&worldf, world);
	mpShader->SetWorldMatrix(&worldf);

	CCamera* camera = CSceneManager::GetScene()->GetGameObject<CCamera>();

	XMFLOAT4X4 view, projection;
	XMStoreFloat4x4(&view, camera->GetViewMatrix());
	XMStoreFloat4x4(&projection, camera->GetProjectionMatrix());

	mpShader->SetCameraPosition(XMFLOAT4(camera->GetPosition().x, camera->GetPosition().y, camera->GetPosition().z, 0.0f));
	mpShader->SetViewMatrix(&view);
	mpShader->SetProjectionMatrix(&projection);
	mpShader->Set();

	//テクスチャ設定
	CRenderer::SetTexture(mpTexture, 0);

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);	

	// プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(mNumVertices, 0);
}