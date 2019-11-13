

#define BILLBOARD_ALPHA (128)

static VERTEX_3D vertex[4];
unsigned short* Index;

CCamera cc;

void BillBoard::Init() 
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	float sizex = 10, sizey = 10;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			vertex[j + 2 * i].Position = XMFLOAT3(-(sizex * 0.5f) + sizex * j, sizey * 0.5f - sizey * i, 0.0f);
			vertex[j + 2 * i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[j + 2 * i].TexCoord = XMFLOAT2((float)j, (float)i);
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

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &VertexBuffer);


	Index[0] = 0;
	Index[1] = 1;
	Index[2] = 2;
	Index[3] = 1;
	Index[4] = 3;
	Index[5] = 2;

	//インデックスバッファ生成
	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(unsigned short) * 4;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = Index;

		CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &IndexBuffer);
	}

	g_texture = new CTexture();
	g_texture->LoadTexture("assest/dog.jpg");
}

void BillBoard::Uninit(void) 
{
	IndexBuffer->Release();
	VertexBuffer->Release();
	g_texture->UnloadTexture();
	delete g_texture;
}

void BillBoard::Draw(void) 
{
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, BILLBOARD_ALPHA);
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CRenderer::SetVertexBuffers(VertexBuffer);
	CRenderer::SetIndexBuffer(IndexBuffer);

	XMMATRIX mtxInvView;
	XMMATRIX world;

	mtxInvView = XMMatrixTranspose(cc.GetViewMatrix());

	XMFLOAT4X4 mIV;
	mIV._14 = 0.0f;
	mIV._24 = 0.0f;
	mIV._34 = 0.0f;

	mtxInvView = XMLoadFloat4x4(&mIV);

	world *= mtxInvView;

	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);
	CRenderer::SetWorldMatrix(&world);

	CRenderer::SetTexture(g_texture);

	CRenderer::DrawIndexed(4, 0, 0);

	//g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

void BillBoard::Create(XMFLOAT3 position) 
{
	m_Position = XMFLOAT3(position.x, position.y, position.z);
}
