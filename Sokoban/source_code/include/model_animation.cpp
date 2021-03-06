


void CModelAnimation::Load(const char** Filename, std::shared_ptr<CShader> shader)
{
	//ファイル読み込み
	this->mDirectory = Filename[0];
	mHastexture = false;

	mpShader = shader;

	m_Scene[0] = aiImportFile(Filename[0], aiProcessPreset_TargetRealtime_MaxQuality);

	if (Filename[1])
		m_Scene[1] = aiImportFile(Filename[1], aiProcessPreset_TargetRealtime_MaxQuality);
	if(Filename[2])
		m_Scene[2] = aiImportFile(Filename[2], aiProcessPreset_TargetRealtime_MaxQuality);

	mMaxScene = 3;

	m_MeshNum = m_Scene[0]->mNumMeshes;
	m_Mesh = new MESH[m_MeshNum];

	for (unsigned int m = 0; m < m_MeshNum; m++)
	{
		aiMesh* mesh = m_Scene[0]->mMeshes[m];
		aiMaterial* material = m_Scene[0]->mMaterials[mesh->mMaterialIndex];
		aiColor4D diffuse;
		aiColor4D specular;
		aiColor4D ambient;
		//float shininess;

		aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient);
		
		//テクスチャロード
		size_t pos = mDirectory.find_last_of("\\/");
		std::string basePath = mDirectory.substr(0, pos + 1);
		aiString path;

		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
		{
			std::string fileloc = basePath + "modeltexture/" + path.data;
			mTexture = new CTexture();
			mTexture->LoadTexture(fileloc.c_str());
			mHastexture = true;
		}

		VERTEX_3D* vertex = new VERTEX_3D[mesh->mNumVertices];

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			vertex[i].Position = XMFLOAT3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			vertex[i].Normal = XMFLOAT3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			vertex[i].Diffuse = XMFLOAT4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
			if (mHastexture)
				vertex[i].TexCoord = XMFLOAT2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}

		//頂点バッファ
		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(VERTEX_3D) * mesh->mNumVertices;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = vertex;
			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[m].VertexBuffer);
		}

		unsigned short* index;
		index = new unsigned short[mesh->mNumFaces * 3];

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			index[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
			index[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
			index[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
		}
		m_Mesh[m].IndexNum = mesh->mNumFaces * 3;

		//インデックスバッファ
		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(unsigned short) * m_Mesh[m].IndexNum;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = index;
			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[m].IndexBuffer);
		}
		delete[]vertex;
		delete[]index;
	}
}

void CModelAnimation::LoadSingle(const char* Filename, std::shared_ptr<CShader> shader)
{
	this->mDirectory = Filename;
	mHastexture = false;

	mpShader = shader;

	m_Scene[0] = aiImportFile(Filename, aiProcessPreset_TargetRealtime_MaxQuality);

	mMaxScene = 1;

	m_MeshNum = m_Scene[0]->mNumMeshes;
	m_Mesh = new MESH[m_MeshNum];

	for (unsigned int m = 0; m < m_MeshNum; m++)
	{
		aiMesh* mesh = m_Scene[0]->mMeshes[m];
		aiMaterial* material = m_Scene[0]->mMaterials[mesh->mMaterialIndex];
		aiColor4D diffuse;
		aiColor4D specular;
		aiColor4D ambient;
		//float shininess;

		aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient);

		//テクスチャ
		size_t pos = mDirectory.find_last_of("\\/");
		std::string basePath = mDirectory.substr(0, pos + 1);
		aiString path;

		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
		{
			std::string fileloc = basePath + "modeltexture/" + path.data;
			mTexture = new CTexture();
			mTexture->LoadTexture(fileloc.c_str());
			mHastexture = true;
		}

		VERTEX_3D* vertex = new VERTEX_3D[mesh->mNumVertices];

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			vertex[i].Position = XMFLOAT3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
			vertex[i].Normal = XMFLOAT3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
			vertex[i].Diffuse = XMFLOAT4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
			if (mHastexture)
				vertex[i].TexCoord = XMFLOAT2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		}

		//VertexBuffer
		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(VERTEX_3D) * mesh->mNumVertices;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = vertex;
			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[m].VertexBuffer);
		}

		unsigned short* index;
		index = new unsigned short[mesh->mNumFaces * 3];

		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			index[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
			index[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
			index[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
		}
		m_Mesh[m].IndexNum = mesh->mNumFaces * 3;

		//IndexBuffer
		{
			D3D11_BUFFER_DESC bd;
			ZeroMemory(&bd, sizeof(bd));
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(unsigned short) * m_Mesh[m].IndexNum;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.pSysMem = index;
			CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_Mesh[m].IndexBuffer);
		}
		delete[]vertex;
		delete[]index;
	}
}

void CModelAnimation::Unload()
{
	for (unsigned int m = 0; m < m_MeshNum; m++)
	{
		m_Mesh[m].VertexBuffer->Release();
		m_Mesh[m].IndexBuffer->Release();
	}
	delete[]m_Mesh;

	for (int i = 0; i < mMaxScene; i++)
		aiReleaseImport(m_Scene[i]);

	if (mHastexture)
	{
		mTexture->UnloadTexture();
		delete mTexture;
	}
}

void CModelAnimation::Update(int Animation,unsigned int Frame)
{
	//アニメーションを動作
	aiAnimation* animation = m_Scene[Animation]->mAnimations[0];

	for (unsigned int c = 0; c < animation->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim = animation->mChannels[c];
		unsigned int f = Frame % nodeAnim->mNumRotationKeys;
		m_NodeRotation[nodeAnim->mNodeName.C_Str()] = nodeAnim->mRotationKeys[f].mValue;

		f = Frame % nodeAnim->mNumPositionKeys;
		m_NodePosition[nodeAnim->mNodeName.C_Str()] = nodeAnim->mPositionKeys[f].mValue;
	}
}

void CModelAnimation::Animation(int Animation1, int Animation2, float Blend, int Frame)
{
	aiAnimation* animation1 = m_Scene[Animation1]->mAnimations[0];
	aiAnimation* animation2 = m_Scene[Animation2]->mAnimations[0];

	for (unsigned int c = 0; c < animation1->mNumChannels; c++)
	{
		aiNodeAnim* nodeAnim1 = animation1->mChannels[c];
		aiNodeAnim* nodeAnim2 = animation2->mChannels[c];

		//int f = Frame % nodeAnim->mNumRotationKeys;
		//m_NodeRotation[nodeAnim->mNodeName.C_Str()] = 球面線形補間 aiQuantion::Interpolate
		//
		//f = Frame % nodeAnim->mNumPositionKeys;
		//m_NodePosition[nodeAnim->mNodeName.C_Str()] = 線形補間
	}
}

void CModelAnimation::Draw(XMMATRIX Matrix)
{
	DrawMesh(m_Scene[0]->mRootNode, Matrix);
}

void CModelAnimation::DrawMesh(aiNode* Node, XMMATRIX Matrix)
{
	XMMATRIX world;

	aiQuaternion aiQuat = m_NodeRotation[Node->mName.C_Str()];
	XMVECTOR quat = XMLoadFloat4(&XMFLOAT4(aiQuat.x, aiQuat.y, aiQuat.z, aiQuat.w));
	world = XMMatrixRotationQuaternion(quat);

	aiVector3D aiVec = m_NodePosition[Node->mName.C_Str()];
	XMVECTOR vector = XMLoadFloat3(&XMFLOAT3(aiVec.x, aiVec.y, aiVec.z));
	world *= XMMatrixTranslationFromVector(vector);

	world *= Matrix;											//自分のmatrix * 親のmatrix

	XMFLOAT4X4 w;
	XMStoreFloat4x4(&w, world);

	mpShader->SetWorldMatrix(&w);
	mpShader->Set();

	for (unsigned int n = 0; n < Node->mNumMeshes; n++)
	{
		unsigned int m = Node->mMeshes[n];
		CRenderer::SetVertexBuffers(m_Mesh[m].VertexBuffer);
		CRenderer::SetIndexBuffer(m_Mesh[m].IndexBuffer);
		if (mHastexture)
			CRenderer::SetTexture(mTexture, 0);

		CRenderer::DrawIndexed(m_Mesh[m].IndexNum, 0, 0);
	}
	//再帰呼び出し
	for (unsigned int i = 0; i < Node->mNumChildren; i++)
	{
		DrawMesh(Node->mChildren[i], world);
	}
}