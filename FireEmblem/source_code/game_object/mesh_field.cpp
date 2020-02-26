using namespace std;

float FieldY[6][6] = {
	{ 1.0f,2.0f,1.0f,0.0f,-1.0f,-1.0f },
	{ 2.0f,3.0f,2.0f,1.0f,-1.0f,-1.0f },
	{ 2.0f,1.0f,2.0f,1.0f,0.0f,0.0f },
	{ 1.0f,0.0f,0.0f,0.0f,1.0f,1.0f },
	{ 1.0f,0.0f,0.0f,0.0f,1.0f,1.0f },
	{ 2.0f,1.0f,0.0f,0.0f,1.0f,2.0f },
};

void CMeshfield::Init()
{
	m_Position = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Rotation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Scale = XMFLOAT3(1.0f, 1.0f, 1.0f);

	sizex = 5.0f, sizez = 5.0f;
	numx = 20, numz = 20;

	//�e�N�X�`���ǂݍ���
	m_Texture = new CTexture();
	m_Texture->LoadTexture("asset/texture/game_object/floor2.png");
	
	mpShader = make_unique<CShader>();
	mpShader->Init("shader_3d_vs.cso", "shader_3d_ps.cso");

	NumVertex = (numx + 1) * (numz + 1);
	NumIndex = (2 + numx * 2)*numz + (numz - 1) * 2;

	Vertex = new VERTEX_3D[NumVertex];
	Index = new unsigned short[NumIndex];

	for (int i = 0; i < numz + 1; i++)
	{
		for (int j = 0; j < numx + 1; j++)
		{
			//DirectX Math ���C�u����
			Vertex[j + (numx + 1) * i].Position =  XMFLOAT3(-(sizex * numx * 0.5f) + sizex * j, -1.5f, (sizez * numz * 0.5f) - sizez * i);		//�ʒu
			Vertex[j + (numx + 1) * i].Normal = XMFLOAT3(0.0f, 1.0f, 0.0f);																			//�@��
			Vertex[j + (numx + 1) * i].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);																		//�F
			Vertex[j + (numx + 1) * i].TexCoord = XMFLOAT2((float)j,(float)i);														//�e�N�X�`�����W
		}
	}

	XMFLOAT3 va, vb, n;

	for (int z = 1; z < numz; z++)
	{
		for (int x = 1; x < numx;x++)
		{
			//��O���牜
			va.x = Vertex[(z - 1) * (numx+1) + x].Position.x - Vertex[(z + 1) * (numx+1) + x].Position.x;
			va.y = Vertex[(z - 1) * (numx+1) + x].Position.y - Vertex[(z + 1) * (numx+1) + x].Position.y;
			va.z = Vertex[(z - 1) * (numx+1) + x].Position.z - Vertex[(z + 1) * (numx+1) + x].Position.z;

			//������E
			vb.x = Vertex[z * (numx+1) + (x + 1)].Position.x - Vertex[z * (numx+1) + (x - 1)].Position.x;
			vb.y = Vertex[z * (numx+1) + (x + 1)].Position.y - Vertex[z * (numx+1) + (x - 1)].Position.y;
			vb.z = Vertex[z * (numx+1) + (x + 1)].Position.z - Vertex[z * (numx+1) + (x - 1)].Position.z;

			//�O�όv�Z
			n.x = va.y * vb.z - va.z * vb.y;
			n.y = va.z * vb.x - va.x * vb.z;
			n.z = va.x * vb.y - va.y - vb.x;

			//n�̒���
			float length = sqrtf(n.x * n.x + n.y * n.y + n.z * n.z);

			//���K��(Normalize)
			n.x = n.x / length;
			n.y = n.y / length;
			n.z = n.z / length;
			
			Vertex[z * numx + x].Normal = n;
		}
	}

	//���_�o�b�t�@����
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

	// �㉺�Q���������
	for (int j = 0; j < numz; j++)
	{
		for (int i = 0; i <= numx; i++)
		{
			Index[p] = (numx + 1) * (j + 1) + i;
			Index[p + 1] = numx * j + i + j;
			p += 2;
		}

		// �J��Ԃ�
		if (j != numz - 1)
		{
			Index[p] = numx * j + numx + j;
			Index[p + 1] = (numx + 1) * (j + 2);
			p += 2;
		}
	}

	//�C���f�b�N�X�o�b�t�@����
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

void CMeshfield::Uninit()
{
	delete[] Vertex;
	delete[] Index;
	m_VertexBuffer->Release();
	m_IndexBuffer->Release();
	m_Texture->UnloadTexture();
	delete m_Texture;

	mpShader->Uninit();
}

void CMeshfield::Update()
{

}

void CMeshfield::Draw()
{
	//���_�o�b�t�@�ݒ�
	CRenderer::SetVertexBuffers(m_VertexBuffer);

	//�C���f�N�X�o�b�t�@�ݒ�
	CRenderer::SetIndexBuffer(m_IndexBuffer);

	//�e�N�X�`���ݒ�
	CRenderer::SetTexture(m_Texture, 0);

	//�}�g���N�X�ݒ�
	XMMATRIX world;
	world = XMMatrixScaling(m_Scale.x,m_Scale.y, m_Scale.z);
	world *= XMMatrixRotationRollPitchYaw(m_Rotation.x, m_Rotation.y, m_Rotation.z);
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

	//�g�|���W�ݒ�&Draw
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	CRenderer::GetDeviceContext()->DrawIndexed(NumIndex, 0, 0);
}

float CMeshfield::GetHeight(XMFLOAT3 position)
{
	int x, z;
	XMFLOAT3 p0, p1, p2, v01, v02, n, v, hp, va, vb;
	float dp0n, dvn, dpn, t;

	v = XMFLOAT3(0.0f, -10.0f, 0.0f);

	//Player�̏��ݎl�p
	x = (int)((position.x+(sizex*numx/2)) / sizex);
	z = (int)((-position.z+(sizez*numz/2)) / sizez);

	//Player�ʒu���v�Z���邽�߂̖@��
	va.x = Vertex[(z + 1) * (numx+1) + (x + 1)].Position.x - Vertex[z * (numx+1) + x].Position.x;
	va.y = Vertex[(z + 1) * (numx+1) + (x + 1)].Position.y - Vertex[z * (numx+1) + x].Position.y;
	va.z = Vertex[(z + 1) * (numx+1) + (x + 1)].Position.z - Vertex[z * (numx+1) + x].Position.z;
	//Player���w���@��
	vb.x = position.x - Vertex[z * (numx+1) + x].Position.x;
	vb.y = position.y - Vertex[z * (numx+1) + x].Position.y;
	vb.z = position.z - Vertex[z * (numx+1) + x].Position.z;

	//Player�̏��ݎO�p
	if (va.z * vb.x - va.x * vb.z > 0.0f)
	{
		p0 = Vertex[(z + 1) * (numx+1) + x].Position;
		p1 = Vertex[z * (numx+1) + x].Position;
		p2 = Vertex[(z + 1) * (numx+1) + (x + 1)].Position;
	}
	else
	{
		p0 = Vertex[z * (numx+1) + (x + 1)].Position;
		p1 = Vertex[(z + 1) * (numx+1) + (x + 1)].Position;
		p2 = Vertex[z * (numx+1) + x].Position;
	}

	v01.x = p1.x - p0.x;	v01.y = p1.y - p0.y;	v01.z = p1.z - p0.z;
	v02.x = p2.x - p0.x;	v02.y = p2.y - p0.y;	v02.z = p2.z - p0.z;
	n.x = v01.y * v02.z - v01.z * v02.y;	n.y = v01.z * v02.x - v01.x * v02.z;	n.z = v01.x * v02.y - v01.y * v02.x;

	dvn = v.x * n.x + v.y * n.y + v.z * n.z;
	dp0n = p0.x * n.x + p0.y * n.y + p0.z * n.z;
	dpn = position.x * n.x + position.y * n.y + position.z * n.z;

	t = (dp0n - dpn) / dvn;

	hp.y = position.y+0.7f + v.y * t;

	return hp.y;
}


//�����搶
void MURASE_Field(void)
{
	VERTEX_3D m_Vertex[25];
	for (int z = 0; z < 5; z++)
	{
		for (int x = 0; x < 5; x++)
		{
			m_Vertex[z * 5 + x].Position.x = x * 2.0f;
			m_Vertex[z * 5 + x].Position.z = -z * 2.0f;
			m_Vertex[z * 5 + x].Position.y = FieldY[z][x];
			//.......
		}
	}
	//���_�o�b�t�@����....
	unsigned short index[25];
	index[0] = 6;
	index[1] = 0;
	index[2] = 7;
	index[3] = 1;
	index[4] = 8;
	index[5] = 2;	//for��
	//......
	//�C���f�b�N�X�o�b�t�@����....
}