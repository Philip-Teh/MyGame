

VERTEX_3D vertex[4];

void CPolygon::Init()
{
	//for (int i = 1; i <= TEXTURE; i++) 
	{
		//DirectX Math ライブラリ
		vertex[0].Position = XMFLOAT3(0, 0, 0);
		vertex[0].Normal = XMFLOAT3(0, 1, 0);
		vertex[0].Diffuse = XMFLOAT4(1, 1, 1, 1);
		vertex[0].TexCoord = XMFLOAT2(0, 0);
		
		vertex[1].Position = XMFLOAT3(200, 0, 0);									//頂点位置
		vertex[1].Normal = XMFLOAT3(0, 1, 0);										//法線
		vertex[1].Diffuse = XMFLOAT4(1, 1, 1, 1);									//色
		vertex[1].TexCoord = XMFLOAT2(1, 0);											//テクスチャ座標
		
		vertex[2].Position = XMFLOAT3(0, 200, 0);
		vertex[2].Normal = XMFLOAT3(0, 1, 0);
		vertex[2].Diffuse = XMFLOAT4(1, 1, 1, 1);
		vertex[2].TexCoord = XMFLOAT2(0, 1);
		
		vertex[3].Position = XMFLOAT3(200, 200, 0);
		vertex[3].Normal = XMFLOAT3(0, 1, 0);
		vertex[3].Diffuse = XMFLOAT4(1, 1, 1, 1);
		vertex[3].TexCoord = XMFLOAT2(1, 1);
		
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

		//polygon.enable = false;
	}
}

void CPolygon::Uninit()
{
	
	m_VertexBuffer->Release();
	m_Texture->UnloadTexture();
	delete m_Texture;
}

void CPolygon::Update()
{

}

void CPolygon::Draw()
{
	//for (int i = 1; i <= TEXTURE; i++) 
	{
		//if (polygon.enable) 
		{
			UINT stride = sizeof(VERTEX_3D);
			UINT offset = 0;
			CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);//頂点バッファ設定
			CRenderer::SetTexture(m_Texture);//テクスチャ設定
			CRenderer::SetWorldViewProjection2D();//2Dマトリクス設定
			CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//トポロジ設定
			CRenderer::GetDeviceContext()->Draw(4, 0);//ポリゴン描画
											  //頂点数
		}
	}
}

void CPolygon::Create(std::string texture,XMFLOAT3 position,float sizeX,float sizeY)
{
	m_Texture->LoadTexture(texture);

	vertex[0].Position = XMFLOAT3(position.x, position.y, position.z);
	vertex[0].Normal = XMFLOAT3(0, 1, 0);
	vertex[0].Diffuse = XMFLOAT4(1, 1, 1, 1);
	vertex[0].TexCoord = XMFLOAT2(0, 0);
	
	vertex[1].Position = XMFLOAT3(position.x + sizeX, position.y, position.z);
	vertex[1].Normal = XMFLOAT3(0, 1, 0);
	vertex[1].Diffuse = XMFLOAT4(1, 1, 1, 1);
	vertex[1].TexCoord = XMFLOAT2(1, 0);
	
	vertex[2].Position = XMFLOAT3(position.x, position.y + sizeY, position.z);
	vertex[2].Normal = XMFLOAT3(0, 1, 0);
	vertex[2].Diffuse = XMFLOAT4(1, 1, 1, 1);
	vertex[2].TexCoord = XMFLOAT2(0, 1);
	
	vertex[3].Position = XMFLOAT3(position.x + sizeX, position.y + sizeY, position.z);
	vertex[3].Normal = XMFLOAT3(0, 1, 0);
	vertex[3].Diffuse = XMFLOAT4(1, 1, 1, 1);
	vertex[3].TexCoord = XMFLOAT2(1, 1);
	
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
}