#pragma once

//============================================================================
//=																			 =
//=							ï`âÊä÷òAÅ@ÉÇÉfÉãï`âÊ							 =
//=																			 =
//============================================================================

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
	void Load(const char** Filename, std::shared_ptr<CShader> shader);
	void LoadSingle(const char* Filename, std::shared_ptr<CShader> shader);
	void Unload();
	void Update(int Animation,unsigned int Frame);
	void Animation(int Animation1, int Animation2, float Blend, int Frame);
	void Draw(XMMATRIX Matrix);
	void DrawMesh(aiNode* Node, XMMATRIX Matrix);

private:
	MESH* m_Mesh = nullptr;
	unsigned int m_MeshNum = NULL;

	const aiScene* m_Scene[3] = {};
	std::map<std::string, aiQuaternion> m_NodeRotation = {};
	std::map<std::string, aiVector3D> m_NodePosition = {};

	CTexture* mTexture = nullptr;
	CTexture* mTextures[3] = {};
	std::shared_ptr<CShader> mpShader = nullptr;

	std::string mDirectory = "";
	bool mHastexture = false;
	int mMaxScene = 0;
};

#endif // !MODELANIMATION_H_

