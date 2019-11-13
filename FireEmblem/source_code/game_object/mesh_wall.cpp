

void CMeshwall::Init()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	sizex = 5.0f, sizez = 5.0f;
	numx = 5, numz = 5;

	//テクスチャ読み込み
	m_Texture = new CTexture();
	m_Texture->Load("asset/field004.tga");

	NumVertex = (numx + 1) * (numz + 1);
	NumIndex = (2 + numx * 2) * numz + (numz - 1) * 2;

	Vertex = new VERTEX_3D[NumVertex];
	Index = new unsigned short[NumIndex];

	for (int i = 0; i < numz + 1; i++)
	{
		for (int j = 0; j < numx + 1; j++)
		{
			//DirectX Math ライブラリ
			Vertex[j + (numx + 1) * i].Position = XMFLOAT3(-(sizex * numx * 0.5f) + sizex * j, 0.0f, (sizez * numz * 0.5f) - sizez * i);		//位置
			Vertex[j + (numx + 1) * i].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);																			//法線
			Vertex[j + (numx + 1) * i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);																		//色
			Vertex[j + (numx + 1) * i].TexCoord = XMFLOAT2((float)j, (float)i);														//テクスチャ座標
		}
	}

	XMFLOAT3 va, vb, n;

	for (int z = 1; z < numz; z++)
	{
		for (int x = 1; x < numx; x++)
		{
			//手前から奥
			va.x = Vertex[(z - 1) * (numx + 1) + x].Position.x - Vertex[(z + 1) * (numx + 1) + x].Position.x;
			va.y = Vertex[(z - 1) * (numx + 1) + x].Position.y - Vertex[(z + 1) * (numx + 1) + x].Position.y;
			va.z = Vertex[(z - 1) * (numx + 1) + x].Position.z - Vertex[(z + 1) * (numx + 1) + x].Position.z;

			//左から右
			vb.x = Vertex[z * (numx + 1) + (x + 1)].Position.x - Vertex[z * (numx + 1) + (x - 1)].Position.x;
			vb.y = Vertex[z * (numx + 1) + (x + 1)].Position.y - Vertex[z * (numx + 1) + (x - 1)].Position.y;
			vb.z = Vertex[z * (numx + 1) + (x + 1)].Position.z - Vertex[z * (numx + 1) + (x - 1)].Position.z;

			//外積計算
			n.x = va.y * vb.z - va.z * vb.y;
			n.y = va.z * vb.x - va.x * vb.z;
			n.z = va.x * vb.y - va.y - vb.x;

			//nの長さ
			float length = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);

			//正規化(Normalize)
			n.x = n.x / length;
			n.y = n.y / length;
			n.z = n.z / length;

			Vertex[z * numx + x].Normal = n;
		}
	}

	//頂点バッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VERTEX_3D) * NumVertex;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = Vertex;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
	}

	int p = 0;

	// 上下２こずつ入れる
	for (int j = 0; j < numz; j++)
	{
		for (int i = 0; i <= numx; i++)
		{
			Index[p] = (numx + 1) * (j + 1) + i;
			Index[p + 1] = numx * j + i + j;
			p += 2;
		}

		// 繰り返し
		if (j != numz - 1)
		{
			Index[p] = numx * j + numx + j;
			Index[p + 1] = (numx + 1) * (j + 2);
			p += 2;
		}
	}

	//インデックスバッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned short) * NumIndex;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = Index;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_IndexBuffer);
	}
}

void CMeshwall::Uninit()
{
	delete[] Vertex;
	delete[] Index;
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->Unload();
	delete m_Texture;
}

void CMeshwall::Update()
{

}

void CMeshwall::Draw()
{
	//頂点バッファ設定
	CRenderer::SetVertexBuffers(m_VertexBuffer);

	//インデクスバッファ設定
	CRenderer::SetIndexBuffer(m_IndexBuffer);

	//テクスチャ設定
	CRenderer::SetTexture(m_Texture);

	//マトリクス設定
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&world);

	//トポロジ設定&Draw
	CRenderer::DrawIndexedSTRIP(NumIndex, 0, 0);
}

void CMeshwall::Set(XMFLOAT3 position, XMFLOAT3 rotation)
{
	m_Position = position;
	m_Rotation = rotation;
}