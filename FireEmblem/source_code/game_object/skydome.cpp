using namespace std;

void CSkydome::Init()
{
	mQuaternion = XMQuaternionIdentity();

	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	float radius = 50;
	int numx = 10, numz = 10;

	//テクスチャ読み込み
	m_Texture = new CTexture();
	m_Texture->LoadTexture("asset/sky.jpg");

	mpShader = make_unique<CShader>();
	mpShader->Init("shader_3d_vs.cso", "shader_3d_ps.cso");

	NumVertex = (numx + 1) * (numz + 1);
	NumIndex = (2 + numx * 2) * numz + (numz - 1) * 2;

	Vertex = new VERTEX_3D[NumVertex];
	Index = new unsigned short[NumIndex];

	for (int i = 0; i <= numz; i++)
	{
		for (int j = 0; j <= numx; j++)
		{
			//DirectX Math ライブラリ
			Vertex[i + (numx + 1) * j].Position.x = cos(XMConvertToRadians((float)(360.0f / numx) * j)) * radius * cos(XMConvertToRadians((float)(90 / numz * (numz - i))));
			Vertex[i + (numx + 1) * j].Position.z= sin(XMConvertToRadians((float)(360.0f / numx) * j)) * radius * cos(XMConvertToRadians((float)(90 / numz * (numz - i))));
			Vertex[i + (numx + 1) * j].Position.y = radius * sin(XMConvertToRadians((float)(90 / numz * (numz - i))));
			Vertex[i + (numx + 1) * j].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			Vertex[i + (numx + 1) * j].TexCoord = XMFLOAT2((float)j / numx, (float)i / numz);
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

	int a = 0;
	int b = 0;

	for (a = 0; a < (numx + 1) * 2; a++)
	{
		if (a % 2 == 0)
		{
			Index[a] = (numx + 1) + b;
		}
		else
		{
			Index[a] = b;
			b++;
		}
	}
	Index[a] = b - 1;
	a++;

	int f = 0, g = 0;

	for (int c = 0; c < numz - 2; c++)
	{
		int d = 0, e = numz + 1;
		d += f;
		e += g;

		Index[a] = (numx + 1) + e;
		a++;

		for (d = 0; d < 2 * (numx + 1); d++)
		{
			if (d % 2 == 0)
			{
				Index[a] = (numx + 1) + e;
				a++;
			}
			else
			{
				Index[a] = e;
				a++;
				e++;
			}
		}
		Index[a] = e - 1;
		a++;
		f += numx + 1;
		g += numx + 1;
	}

	int h = 0, i = numx + 1;
	i += f;

	Index[a] = (numx + 1) + i;
	a++;

	for (h = 0; h < 2 * (numx + 1); h++)
	{
		if (h % 2 == 0)
		{
			Index[a] = (numx + 1) + i;
			a++;
		}
		else
		{
			Index[a] = i;
			a++;
			i++;
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

	delete[] Vertex;
	delete[] Index;
}

void CSkydome::Uninit()
{
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->UnloadTexture();
	delete m_Texture;

	mpShader->Uninit();
}

void CSkydome::Update()
{
	//m_Rotation.y -= 0.01f;

	XMFLOAT3 vz = XMFLOAT3(0.0f, 1.0f, 0.0f);
	XMVECTOR axis = XMLoadFloat3(&vz);
	XMVECTOR rotation = XMQuaternionRotationAxis(axis, 0.0005f);
	mQuaternion = XMQuaternionMultiply(mQuaternion, rotation);
	mQuaternion = XMQuaternionNormalize(mQuaternion);
}

void CSkydome::Draw()
{
	//頂点バッファ設定
	CRenderer::SetVertexBuffers(m_VertexBuffer);
	CRenderer::SetIndexBuffer(m_IndexBuffer);

	CRenderer::SetTexture(m_Texture, 0);					//テクスチャ設定

	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x, m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationQuaternion(mQuaternion);
	//world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, m_Position.z);

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

	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->DrawIndexed(NumIndex, 0, 0);
}