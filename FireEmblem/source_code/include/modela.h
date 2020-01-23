#ifndef _MODELA_H_
#define _MODELA_H_

class ModelA
{
public:
	void Load(std::string filename);
	void Draw();
	void Unload();

private:
	std::vector<Mesh> meshes;
	std::string directory;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif