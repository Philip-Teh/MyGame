using namespace std;

void CPolygon::Init(std::string file,XMFLOAT3 position, float sizeX, float sizeY)
{
	mPosition = position;
	mSize = XMFLOAT2(sizeX, sizeY);

	mVertex[0].Position = XMFLOAT3(mPosition.x, mPosition.y, mPosition.z);
	mVertex[0].Normal = XMFLOAT3(0, 1, 0);
	mVertex[0].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[0].TexCoord = XMFLOAT2(0, 0);

	mVertex[1].Position = XMFLOAT3(mPosition.x + mSize.x, mPosition.y, mPosition.z);
	mVertex[1].Normal = XMFLOAT3(0, 1, 0);
	mVertex[1].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[1].TexCoord = XMFLOAT2(1, 0);

	mVertex[2].Position = XMFLOAT3(mPosition.x, mPosition.y + mSize.y, mPosition.z);
	mVertex[2].Normal = XMFLOAT3(0, 1, 0);
	mVertex[2].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[2].TexCoord = XMFLOAT2(0, 1);

	mVertex[3].Position = XMFLOAT3(mPosition.x + mSize.x, mPosition.y + mSize.y, mPosition.z);
	mVertex[3].Normal = XMFLOAT3(0, 1, 0);
	mVertex[3].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[3].TexCoord = XMFLOAT2(1, 1);

	//頂点バッファ生成
	/*D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = mVertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &mpVertexBuffer);*/

	mpShader = make_unique<CShader>();
	mpShader->Init("shader_2d_vs.cso", "shader_2d_ps.cso");

	mpTexture = new CTexture();
	mpTexture->LoadTexture(file);
}

void CPolygon::Init(std::string file,float sizeX, float sizeY)
{
	mSize = XMFLOAT2(sizeX, sizeY);

	mpShader = make_unique<CShader>();
	mpShader->Init("shader_2d_vs.cso", "shader_2d_ps.cso");

	mpTexture = new CTexture();
	mpTexture->LoadTexture(file);
}

void CPolygon::InitBillBoard(std::string file, float sizeX, float sizeY)
{
	mSize = XMFLOAT2(sizeX, sizeY);

	mpShader = nullptr;

	mpTexture = new CTexture();
	mpTexture->LoadTexture(file);
}

void CPolygon::Uninit()
{
	if (mpShader)
		mpShader->Uninit();

	mpTexture->UnloadTexture();
	delete mpTexture;
}

void CPolygon::Update(XMFLOAT3 position)
{
	//mPosition = position;
}

void CPolygon::Draw()
{
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

	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);
	//CRenderer::SetWorldViewProjection2D();//2Dマトリクス設定

	XMFLOAT4X4 projection;
	XMStoreFloat4x4(&projection, XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
	mpShader->SetProjectionMatrix(&projection);

	mpShader->Set();

	//テクスチャ設定
	CRenderer::SetTexture(mpTexture, 0); 

	// プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);

	mpVertexBuffer->Release();
}

void CPolygon::Draw(XMFLOAT3 position)
{
	mVertex[0].Position = XMFLOAT3(position.x, position.y, position.z);
	mVertex[0].Normal = XMFLOAT3(0, 1, 0);
	mVertex[0].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[0].TexCoord = XMFLOAT2(0, 0);

	mVertex[1].Position = XMFLOAT3(position.x + mSize.x, position.y, position.z);
	mVertex[1].Normal = XMFLOAT3(0, 1, 0);
	mVertex[1].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[1].TexCoord = XMFLOAT2(1, 0);

	mVertex[2].Position = XMFLOAT3(position.x, position.y + mSize.y, position.z);
	mVertex[2].Normal = XMFLOAT3(0, 1, 0);
	mVertex[2].Diffuse = XMFLOAT4(1, 1, 1, 1);
	mVertex[2].TexCoord = XMFLOAT2(0, 1);

	mVertex[3].Position = XMFLOAT3(position.x + mSize.x, position.y + mSize.y, position.z);
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

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &mpVertexBuffer);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

	XMFLOAT4X4 projection;
	XMStoreFloat4x4(&projection, XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
	mpShader->SetProjectionMatrix(&projection);
	mpShader->Set();

	CRenderer::SetTexture(mpTexture, 0);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 0);

	mpVertexBuffer->Release();
}

void CPolygon::Draw(XMFLOAT3 position, int tx, int ty, int tw, int th)
{
	//mPosition = position;

	float u0 = (float)tx / mSize.x;
	float v0 = (float)ty / mSize.y;
	float u1 = (float)(tx + tw) / mSize.x;
	float v1 = (float)(ty + th) / mSize.y;

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

	CRenderer::GetDevice()->CreateBuffer(&mbd, &msd, &mpVertexBuffer);

	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

	XMFLOAT4X4 projection;
	XMStoreFloat4x4(&projection, XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
	mpShader->SetProjectionMatrix(&projection);
	mpShader->Set();

	CRenderer::SetTexture(mpTexture, 0);
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->Draw(4, 0);

	mpVertexBuffer->Release();
}

void CPolygon::DrawBillBoard(XMFLOAT3 position, int tx, int ty, int tw, int th)
{
	//mPosition = position;

	float u0 = (float)tx / mSize.x;
	float v0 = (float)ty / mSize.y;
	float u1 = (float)(tx + tw) / mSize.x;
	float v1 = (float)(ty + th) / mSize.y;

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

	CRenderer::GetDevice()->CreateBuffer(&mbd, &msd, &mpVertexBuffer);

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

	//UINT stride = sizeof(VERTEX_3D);
	//UINT offset = 0;
	//CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &mpVertexBuffer, &stride, &offset);

	CRenderer::SetVertexBuffers(mpVertexBuffer);
	CRenderer::SetIndexBuffer(mpIndexBuffer);

	//XMFLOAT4X4 projection;
	//XMStoreFloat4x4(&projection, XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
	//mpShader->SetProjectionMatrix(&projection);
	//mpShader->Set();

	CRenderer::SetTexture(mpTexture, 0);
	//CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//CRenderer::GetDeviceContext()->Draw(4, 0);

	mpVertexBuffer->Release();
	mpIndexBuffer->Release();
}