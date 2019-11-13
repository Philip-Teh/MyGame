

VERTEX_3D vertex[4];

void CPolygon::Init()
{
	//for (int i = 1; i <= TEXTURE; i++) 
	{
		//DirectX Math ���C�u����
		vertex[0].Position = XMFLOAT3(0, 0, 0);
		vertex[0].Normal = XMFLOAT3(0, 1, 0);
		vertex[0].Diffuse = XMFLOAT4(1, 1, 1, 1);
		vertex[0].TexCoord = XMFLOAT2(0, 0);
		
		vertex[1].Position = XMFLOAT3(200, 0, 0);									//���_�ʒu
		vertex[1].Normal = XMFLOAT3(0, 1, 0);										//�@��
		vertex[1].Diffuse = XMFLOAT4(1, 1, 1, 1);									//�F
		vertex[1].TexCoord = XMFLOAT2(1, 0);											//�e�N�X�`�����W
		
		vertex[2].Position = XMFLOAT3(0, 200, 0);
		vertex[2].Normal = XMFLOAT3(0, 1, 0);
		vertex[2].Diffuse = XMFLOAT4(1, 1, 1, 1);
		vertex[2].TexCoord = XMFLOAT2(0, 1);
		
		vertex[3].Position = XMFLOAT3(200, 200, 0);
		vertex[3].Normal = XMFLOAT3(0, 1, 0);
		vertex[3].Diffuse = XMFLOAT4(1, 1, 1, 1);
		vertex[3].TexCoord = XMFLOAT2(1, 1);
		
		//���_�o�b�t�@����
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

		//�e�N�X�`���ǂݍ���
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
			CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);//���_�o�b�t�@�ݒ�
			CRenderer::SetTexture(m_Texture);//�e�N�X�`���ݒ�
			CRenderer::SetWorldViewProjection2D();//2D�}�g���N�X�ݒ�
			CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);//�g�|���W�ݒ�
			CRenderer::GetDeviceContext()->Draw(4, 0);//�|���S���`��
											  //���_��
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
	
	//���_�o�b�t�@����
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