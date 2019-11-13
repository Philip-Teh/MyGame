

static int NumVertices = 0;
static float sizex = 10, sizez = 10;
static int numx = 1, numz = 1;

void CField::Init()
{
	m_Position = XMFLOAT3(0.0f, 7.0f, 0.0f);
	m_Rotation= XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale= XMFLOAT3(1.0f, 1.0f, 1.0f);

	NumVertices = (numx + 1) * (numz + 1);

	VERTEX_3D vertex[4];

	for (int i = 0; i < numx+1; i++)
	{
		for (int j = 0; j < numz+1; j++)
		{
			//DirectX Math ライブラリ
			vertex[j + (numx + 1) * i].Position = XMFLOAT3(-(sizex * numx * 0.5f) + sizex * j, 0.0f, (sizez * numz * 0.5f) - sizez * i);		//位置
			vertex[j + (numx + 1) * i].Normal = XMFLOAT3(0, 1, 0);																				//法線
			vertex[j + (numx + 1) * i].Diffuse = XMFLOAT4(1, 1, 1, 1);																			//色
			vertex[j + (numx + 1) * i].TexCoord = XMFLOAT2((float)j, (float)i);																				//テクスチャ座標
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

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	//テクスチャ読み込み
	m_Texture = new CTexture();
	m_Texture->Load("asset/field004.tga");
}

void CField::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;
}

void CField::Update()
{

}

void CField::Draw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);		//頂点バッファ設定
	CRenderer::SetTexture(m_Texture);																//テクスチャ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);	//トポロジ設定

	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&world);

	CRenderer::GetDeviceContext()->Draw(NumVertices, 0);//ポリゴン描画
									//頂点数
}