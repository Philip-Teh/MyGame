#pragma once

//============================================================================
//=																			 =
//=							�`��֘A�@�e�N�X�`��							 =
//=																			 =
//============================================================================

#ifndef TEXTURE_H_
#define TEXTURE_H_

class CTexture
{

public:
	//TGA�`���̂�
	void Load( const char *FileName );
	void Unload();

	//TGA�ȊO(PNG,JPG)
	void LoadTexture(std::string FileName);
	void UnloadTexture();

	ID3D11ShaderResourceView* GetShaderResourceView(){ return m_ShaderResourceView; }

private:
	ID3D11Resource*             pTexture;
	ID3D11Texture2D*			m_Texture;
	ID3D11ShaderResourceView* m_ShaderResourceView;

};

#endif