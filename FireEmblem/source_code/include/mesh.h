#ifndef MESH_H_
#define MESH_H_

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Mesh {
public:

	Mesh(vector<MATERIAL> Material,vector<VERTEX_3D> vertices, vector<UINT> indices, vector<CTexture*> textures)
	{
		this->material = Material;
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		this->setupMesh();
	}

	void Draw()
	{
		// 頂点バッファ設定
		CRenderer::SetVertexBuffers(VertexBuffer);

		// インデックスバッファ設定
		CRenderer::SetIndexBuffer(IndexBuffer);

			// マテリアル設定
		CRenderer::SetMaterial(material[0]);

			// テクスチャ設定
		CRenderer::SetTexture(textures[0]);

			// ポリゴン描画
		CRenderer::DrawIndexed(indices.size(), 0, 0);
		
	}

	void Close()
	{
		VertexBuffer->Release();
		IndexBuffer->Release();

		for (CTexture* texture : textures)
		{
			texture->UnloadTexture();
			delete texture;
		}

	}
private:
	/*  Render data  */
	vector<VERTEX_3D> vertices;
	vector<UINT> indices;
	vector<CTexture*> textures;
	ID3D11Buffer* VertexBuffer, * IndexBuffer;
	vector<MATERIAL> material;

	/*  Functions    */
	// Initializes all the buffer objects/arrays
	bool setupMesh()
	{
		HRESULT hr;

		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(VERTEX_3D) * vertices.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &vertices[0];

		hr = CRenderer::GetDevice()->CreateBuffer(&vbd, &initData, &VertexBuffer);
		if (FAILED(hr))
			return false;

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = sizeof(UINT) * indices.size();
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;

		initData.pSysMem = &indices[0];

		hr = CRenderer::GetDevice()->CreateBuffer(&ibd, &initData, &IndexBuffer);
		if (FAILED(hr))
			return false;
	}
};

#endif // !MESH_H_
