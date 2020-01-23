

void CPolygon::Init(std::string file,XMFLOAT3 position, float sizeX, float sizeY)
{
	mPosition = position;
	size = XMFLOAT2(sizeX, sizeY);

	mVertex[0].Position = XMFLOAT3(mPosition.x, mPosition.y, mPosition.z);
	mVertex[0].Normal = XMFLOAT3(0, 1, 0);
	mVertex[0].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[0].TexCoord = XMFLOAT2(0, 0);

	mVertex[1].Position = XMFLOAT3(mPosition.x + size.x, mPosition.y, mPosition.z);
	mVertex[1].Normal = XMFLOAT3(0, 1, 0);
	mVertex[1].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[1].TexCoord = XMFLOAT2(1, 0);

	mVertex[2].Position = XMFLOAT3(mPosition.x, mPosition.y + size.y, mPosition.z);
	mVertex[2].Normal = XMFLOAT3(0, 1, 0);
	mVertex[2].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[2].TexCoord = XMFLOAT2(0, 1);

	mVertex[3].Position = XMFLOAT3(mPosition.x + size.x, mPosition.y + size.y, mPosition.z);
	mVertex[3].Normal = XMFLOAT3(0, 1, 0);
	mVertex[3].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[3].TexCoord = XMFLOAT2(1, 1);

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

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	mTexture = new CTexture();
	mTexture->LoadTexture(file);
}

void CPolygon::Init(std::string file,float sizeX, float sizeY)
{
	size = XMFLOAT2(sizeX, sizeY);

	mTexture = new CTexture();
	mTexture->LoadTexture(file);
}

void CPolygon::Uninit()
{
	if (m_VertexBuffer)
		m_VertexBuffer->Release();

	mTexture->UnloadTexture();
	delete mTexture;
}

void CPolygon::Update(XMFLOAT3 position)
{
	//mPosition = position;
}

void CPolygon::Draw()
{
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);//頂点バッファ設定
	CRenderer::SetTexture(mTexture);//テクスチャ設定
	CRenderer::SetWorldViewProjection2D();//2Dマトリクス設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//トポロジ設定
	CRenderer::GetDeviceContext()->Draw(4, 0);//ポリゴン描画
									//頂点数
}

void CPolygon::Draw(XMFLOAT3 position)
{
	mVertex[0].Position = XMFLOAT3(position.x, position.y, position.z);
	mVertex[0].Normal = XMFLOAT3(0, 1, 0);
	mVertex[0].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[0].TexCoord = XMFLOAT2(0, 0);

	mVertex[1].Position = XMFLOAT3(position.x + size.x, position.y, position.z);
	mVertex[1].Normal = XMFLOAT3(0, 1, 0);
	mVertex[1].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[1].TexCoord = XMFLOAT2(1, 0);

	mVertex[2].Position = XMFLOAT3(position.x, position.y + size.y, position.z);
	mVertex[2].Normal = XMFLOAT3(0, 1, 0);
	mVertex[2].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[2].TexCoord = XMFLOAT2(0, 1);

	mVertex[3].Position = XMFLOAT3(position.x + size.x, position.y + size.y, position.z);
	mVertex[3].Normal = XMFLOAT3(0, 1, 0);
	mVertex[3].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[3].TexCoord = XMFLOAT2(1, 1);

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

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	CRenderer::SetTexture(mTexture);
	CRenderer::SetWorldViewProjection2D();
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 0);

	m_VertexBuffer->Release();
}

void CPolygon::Draw(XMFLOAT3 position, int tx, int ty, int tw, int th)
{
	//mPosition = position;

	float u0 = (float)tx / size.x;
	float v0 = (float)ty / size.y;
	float u1 = (float)(tx + tw) / size.x;
	float v1 = (float)(ty + th) / size.y;

	mVertex[0].Position = XMFLOAT3(position.x, position.y, position.z);
	mVertex[0].Normal = XMFLOAT3(0, 1, 0);
	mVertex[0].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[0].TexCoord = XMFLOAT2(u0, v0);

	mVertex[1].Position = XMFLOAT3(position.x + tw, position.y, position.z);
	mVertex[1].Normal = XMFLOAT3(0, 1, 0);
	mVertex[1].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[1].TexCoord = XMFLOAT2(u1, v0);

	mVertex[2].Position = XMFLOAT3(position.x, position.y + th, position.z);
	mVertex[2].Normal = XMFLOAT3(0, 1, 0);
	mVertex[2].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[2].TexCoord = XMFLOAT2(u0, v1);

	mVertex[3].Position = XMFLOAT3(position.x + tw, position.y + th, position.z);
	mVertex[3].Normal = XMFLOAT3(0, 1, 0);
	mVertex[3].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[3].TexCoord = XMFLOAT2(u1, v1);

	//頂点バッファ生成
	D3D11_BUFFER_DESC mbd;
	ZeroMemory(&mbd, sizeof(mbd));
	mbd.Usage = D3D11_USAGE_DEFAULT;
	mbd.ByteWidth = sizeof(VERTEX_3D) * 4;
	mbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	mbd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA msd;
	ZeroMemory(&msd, sizeof(msd));
	msd.pSysMem = mVertex;

	CRenderer::GetDevice()->CreateBuffer(&mbd, &msd, &m_VertexBuffer);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);//頂点バッファ設定
	CRenderer::SetTexture(mTexture);//テクスチャ設定
	CRenderer::SetWorldViewProjection2D();//2Dマトリクス設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//トポロジ設定
	CRenderer::GetDeviceContext()->Draw(4, 0);//ポリゴン描画

	m_VertexBuffer->Release();
}