#ifndef MODELANIMATION_H_
#define MODELANIMATION_H_

struct MESH
{
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
	unsigned int IndexNum;			//���̓|���S������,Direct11��Index��
};

class CModelAnimation
{
private:
	MESH* m_Mesh;
	unsigned int m_MeshNum;
	const aiScene* m_Scene[3];
	std::map<std::string, aiQuaternion> m_NodeRotation;
	std::map<std::string, aiVector3D> m_NodePosition;

public:
	void Load(const char* Filename);
	void Unload();
	void Update(int Animation,int Frame);
	void Animation(int Animation1, int Animation2, float Blend, int Frame);
	void Draw(XMMATRIX Matrix);
	void DrawMesh(aiNode* Node, XMMATRIX Matrix);
};

#endif // !MODELANIMATION_H_

