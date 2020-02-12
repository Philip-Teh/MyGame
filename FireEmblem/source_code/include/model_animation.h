#pragma once



#ifndef MODELANIMATION_H_
#define MODELANIMATION_H_

struct MESH
{
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
	unsigned int IndexNum;			//å≥ÇÕÉ|ÉäÉSÉìêîÇ™,Direct11ÇÕIndexêî
};

class CModelAnimation
{
public:
	void Load(const char** Filename, CShader* shader);
	void Unload();
	void Update(int Animation,unsigned int Frame);
	void Animation(int Animation1, int Animation2, float Blend, int Frame);
	void Draw(XMMATRIX Matrix);
	void DrawMesh(aiNode* Node, XMMATRIX Matrix);

private:
	MESH* m_Mesh = nullptr;
	unsigned int m_MeshNum = NULL;
	const aiScene* m_Scene[3] = {};
	std::map<std::string, aiQuaternion> m_NodeRotation;
	std::map<std::string, aiVector3D> m_NodePosition;
	CTexture* texture;
	CShader* mpShader;
	std::string directory;
	bool hastexture = false;
};

#endif // !MODELANIMATION_H_

