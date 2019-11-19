#ifndef MODEL_H_
#define MODEL_H_

// マテリアル構造体
struct MODEL_MATERIAL
{
	char						Name[256] = "";
	MATERIAL					Material;
	char						TextureName[256] = "";
};

// 描画サブセット構造体
struct SUBSET
{
	unsigned short	StartIndex = NULL;
	unsigned short	IndexNum = NULL;
	MODEL_MATERIAL	Material;
};

// モデル構造体
struct MODEL
{
	VERTEX_3D		*VertexArray;
	unsigned short	VertexNum;
	unsigned short	*IndexArray;
	unsigned short	IndexNum;
	SUBSET			*SubsetArray;
	unsigned short	SubsetNum;
};


class CModel
{
public:
	void Draw();

	void Load( const char *FileName );
	void Unload();

private:

	ID3D11Buffer*	m_VertexBuffer = nullptr;
	ID3D11Buffer*	m_IndexBuffer = nullptr;

	DX11_SUBSET*	m_SubsetArray = nullptr;
	unsigned short	m_SubsetNum = NULL;

	void LoadObj( const char *FileName, MODEL *Model );
	void LoadMaterial( const char *FileName, MODEL_MATERIAL **MaterialArray, unsigned short *MaterialNum );

};

#endif