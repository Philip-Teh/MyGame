#pragma once


struct CONSTANT
{
	XMFLOAT4X4 WorldMatrix;
	XMFLOAT4X4 ViewMatrix;
	XMFLOAT4X4 ProjectionMatrix;
	XMFLOAT4 CameraPosition;
};

class CShader
{
public:
	void Init( const char* VertexShader, const char* PixelShader );
	void Uninit();
	void Set();

	void SetWorldMatrix(XMFLOAT4X4* WorldMatrix){ m_Constant.WorldMatrix = Transpose(WorldMatrix); }
	void SetViewMatrix(XMFLOAT4X4* ViewMatrix){ m_Constant.ViewMatrix = Transpose(ViewMatrix); }
	void SetProjectionMatrix(XMFLOAT4X4* ProjectionMatrix) { m_Constant.ProjectionMatrix = Transpose( ProjectionMatrix ); }
	void SetCameraPosition(XMFLOAT4 cameraPosition) { m_Constant.CameraPosition = cameraPosition; }

	XMFLOAT4X4 Transpose(XMFLOAT4X4* Matrix)
	{
		XMFLOAT4X4 outMatrix;

		outMatrix._11 = Matrix->_11;
		outMatrix._12 = Matrix->_21;
		outMatrix._13 = Matrix->_31;
		outMatrix._14 = Matrix->_41;

		outMatrix._21 = Matrix->_12;
		outMatrix._22 = Matrix->_22;
		outMatrix._23 = Matrix->_32;
		outMatrix._24 = Matrix->_42;

		outMatrix._31 = Matrix->_13;
		outMatrix._32 = Matrix->_23;
		outMatrix._33 = Matrix->_33;
		outMatrix._34 = Matrix->_43;

		outMatrix._41 = Matrix->_14;
		outMatrix._42 = Matrix->_24;
		outMatrix._43 = Matrix->_34;
		outMatrix._44 = Matrix->_44;

		return outMatrix;
	}

private:
	ID3D11VertexShader*     m_VertexShader;
	ID3D11PixelShader*      m_PixelShader;
	ID3D11InputLayout*      m_VertexLayout;

	ID3D11Buffer*			m_ConstantBuffer;
	ID3D11Buffer*			m_LightBuffer;
	CONSTANT				m_Constant;
	LIGHT					m_Light;

	std::vector<unsigned char> mpBuffer;
	unsigned long mFsize = 0;

	unsigned char* mpInstruct = nullptr;	//���͍\���̂̏�񂪂���ʒu�ւ̃|�C���^
	int mVariable = 0;					//�ϐ��̐�
	int mVariablesystem = 0;			//�V�X�e���l�Z�}���e�B�N�X�����蓖�Ă�ꂽ�ϐ��̐�
	std::vector<char*> mSemanticsname;	//�Z�}���e�B�N�X��
	std::vector<UINT> mSemanticsindex;	//�Z�}���e�B�N�X�C���f�b�N�X
	std::vector<DXGI_FORMAT> mFormat;	//�ϐ��̌^
	unsigned char* str = nullptr;

	void CreateLayout();

};