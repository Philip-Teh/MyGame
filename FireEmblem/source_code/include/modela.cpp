using namespace std;

void ModelA::Load(std::string filename)
{
	const aiScene* pScene = aiImportFile(filename.c_str(), aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);

	this->directory = filename;

	processNode(pScene->mRootNode, pScene);
}

void ModelA::Unload()
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Close();
	}
}

void ModelA::Draw()
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw();
	}
}

void ModelA::processNode(aiNode* node, const aiScene* scene)
{
	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(this->processMesh(mesh, scene));
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		this->processNode(node->mChildren[i], scene);
	}
}


Mesh ModelA::processMesh(aiMesh* mesh, const aiScene* scene)
{
	// Data to fill
	vector<VERTEX_3D> vertices;
	vector<UINT> indices;
	vector<CTexture*> textures;
	vector<MATERIAL> Material;

	// Walk through each of the mesh's vertices
	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		VERTEX_3D vertex;

		vertex.Position.x = mesh->mVertices[i].x;
		vertex.Position.y = mesh->mVertices[i].y;
		vertex.Position.z = mesh->mVertices[i].z;

		vertex.Normal.x = mesh->mNormals[i].x;
		vertex.Normal.y = mesh->mNormals[i].y;
		vertex.Normal.z = mesh->mNormals[i].z;

		//vertex.Diffuse.x = mesh->mColors[0][i].r;
		//vertex.Diffuse.y = mesh->mColors[0][i].g;
		//vertex.Diffuse.z = mesh->mColors[0][i].b;
		//vertex.Diffuse.w = mesh->mColors[0][i].a;

		if (mesh->mTextureCoords[0])
		{
			vertex.TexCoord.x = (float)mesh->mTextureCoords[0][i].x;
			vertex.TexCoord.y = (float)mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for (UINT j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		aiColor4D color;

		MATERIAL ma;

		aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);
		ma.Diffuse.r = color.r;
		ma.Diffuse.g = color.g;
		ma.Diffuse.b = color.b;
		ma.Diffuse.a = color.a;

		aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color);
		ma.Ambient.r = color.r;
		ma.Ambient.g = color.g;
		ma.Ambient.b = color.b;
		ma.Ambient.a = color.a;

		aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color);
		ma.Specular.r = color.r;
		ma.Specular.g = color.g;
		ma.Specular.b = color.b;
		ma.Specular.a = color.a;
		
		aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &color);
		ma.Emission.r = color.r;
		ma.Emission.g = color.g;
		ma.Emission.b = color.b;
		ma.Emission.a = color.a;
		
		aiGetMaterialColor(material, AI_MATKEY_COLOR_TRANSPARENT, &color);
		ma.Shininess = color.a;

		Material.push_back(ma);

		size_t pos = directory.find_last_of("\\/");
		std::string basePath = directory.substr(0, pos + 1);

		aiString path;
		if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
		{
			CTexture* text = new CTexture();

			std::string fileloc = basePath + path.data;

			//if (fileloc.find(".tga") == std::string::npos)
			//	text->Load(fileloc.c_str());
			//else
				text->LoadTexture(fileloc.c_str());

			textures.push_back(text);
		}
	}
	return Mesh(Material, vertices, indices, textures);
}