#include "main.h"
#include "renderer.h"
#include "shader.h"
#include <io.h>

void CShader::Init( const char* VertexShader, const char* PixelShader )
{

	// ���_�V�F�[�_����
	{
		FILE* file;

		file = fopen(VertexShader, "rb");
		mFsize = _filelength(_fileno(file));
		mpBuffer.resize(mFsize);
		fread(mpBuffer.data(), mFsize, 1, file);
		fclose(file);

		//���_�V�F�[�_�[
		CRenderer::GetDevice()->CreateVertexShader(mpBuffer.data(), mFsize, NULL, &m_VertexShader);

		 //���̓��C�A�E�g����
		{
			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				  //�Z�}���e�B�N�X  //�f�[�^�t�H�[�}�b�g
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};
			UINT numElements = ARRAYSIZE(layout);

			CRenderer::GetDevice()->CreateInputLayout(layout,
				numElements,
				mpBuffer.data(),
				mFsize,
				&m_VertexLayout);
		}

		//CreateLayout();

		//std::vector<D3D11_INPUT_ELEMENT_DESC> layout(mVariable);
		//for (int i = 0; i < mVariable; i++) {
		//	layout[i] = {
		//		mSemanticsname[i],
		//		mSemanticsindex[i],
		//		mFormat[i],
		//		0,
		//		D3D11_APPEND_ALIGNED_ELEMENT,
		//		D3D11_INPUT_PER_VERTEX_DATA,
		//		0
		//	};
		//}
		//CRenderer::GetDevice()->CreateInputLayout(layout.data(),
		//	mVariable,
		//	mpBuffer.data(),
		//	mFsize,
		//	&m_VertexLayout);

		mpBuffer.clear();
	}



	// �s�N�Z���V�F�[�_����
	{
		FILE* file;
		long int fsize;

		file = fopen(PixelShader, "rb");
		fsize = _filelength(_fileno(file));
		unsigned char* buffer = new unsigned char[fsize];
		fread(buffer, fsize, 1, file);
		fclose(file);

		//�s�N�Z���V�F�[�_�[
		CRenderer::GetDevice()->CreatePixelShader(buffer, fsize, NULL, &m_PixelShader);

		delete[] buffer;
	}



	// �萔�o�b�t�@����(�O���[�o���ϐ��Ɏ��Ă��܂�)
	{
		D3D11_BUFFER_DESC hBufferDesc;
		hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		hBufferDesc.CPUAccessFlags = 0;
		hBufferDesc.MiscFlags = 0;
		hBufferDesc.StructureByteStride = sizeof(float);

		hBufferDesc.ByteWidth = sizeof(CONSTANT);
		CRenderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, &m_ConstantBuffer);

		hBufferDesc.ByteWidth = sizeof(LIGHT);
		CRenderer::GetDevice()->CreateBuffer(&hBufferDesc, NULL, &m_LightBuffer);

		m_Light.Direction = XMFLOAT4(0.0f, -1.0f, 0.0f, 0.0f);
		m_Light.Diffuse = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
		m_Light.Ambient = COLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void CShader::Uninit()
{
	if (m_ConstantBuffer)	m_ConstantBuffer->Release();
	if (m_LightBuffer)	m_LightBuffer->Release();

	if (m_VertexLayout)		m_VertexLayout->Release();
	if (m_VertexShader)		m_VertexShader->Release();
	if (m_PixelShader)		m_PixelShader->Release();
}




void CShader::Set()
{

	// �V�F�[�_�ݒ�
	CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	CRenderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);


	// ���̓��C�A�E�g�ݒ�
	CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);


	// �萔�o�b�t�@�X�V
	CRenderer::GetDeviceContext()->UpdateSubresource(m_ConstantBuffer, 0, NULL, &m_Constant, 0, 0);
	CRenderer::GetDeviceContext()->UpdateSubresource(m_LightBuffer, 0, NULL, &m_Light, 0, 0);

	// �萔�o�b�t�@�ݒ�
	CRenderer::GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);
	CRenderer::GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_ConstantBuffer);

	CRenderer::GetDeviceContext()->VSSetConstantBuffers(1, 1, &m_LightBuffer);
	CRenderer::GetDeviceContext()->PSSetConstantBuffers(1, 1, &m_LightBuffer);
}

void CShader::CreateLayout()
{
	for (unsigned long i = 0L; i < mFsize - 4; i++) {
		if (memcmp(mpBuffer.data()+i, "ISGN", 4) == NULL) {
			mpInstruct = mpBuffer.data() + i;
			break;
		}
	}
	//if (mpInstruct == nullptr) {
	//	return FWP_E_NOT_FOUND;
	//}


	mVariable = mpInstruct[8];
	mSemanticsname.resize(mVariable);
	mSemanticsindex.resize(mVariable);
	mFormat.resize(mVariable);

	str = &mpInstruct[16];

	for (int i = 0; i < mVariable; i++) {
		mSemanticsname[i] = (char*)(str[i * 24] + mpInstruct + 8);

		if (strcmp(mSemanticsname[i], "SV_InstanceID") == 0) {		//�V�X�e���l�Z�}���e�B�N�X���t���Ă���ϐ��͖���
			mVariablesystem++;
			continue;
		}
		mSemanticsindex[i] = str[i * 24 + 4];

		switch (str[i * 24 + 20]) {
		case '\x0f'://4����
			switch (str[i * 24 + 12]) {
			case D3D_REGISTER_COMPONENT_FLOAT32://float
				mFormat[i] = DXGI_FORMAT_R32G32B32A32_FLOAT;
				break;
			default:
				mFormat[i] = DXGI_FORMAT_UNKNOWN;
				break;
			}
			break;
		case '\x07'://3����
			switch (str[i * 24 + 12]) {
			case D3D_REGISTER_COMPONENT_FLOAT32://float
				mFormat[i] = DXGI_FORMAT_R32G32B32_FLOAT;
				break;
			default:
				mFormat[i] = DXGI_FORMAT_UNKNOWN;
				break;
			}
			break;
		case '\x03'://2����
			switch (str[i * 24 + 12]) {
			case D3D_REGISTER_COMPONENT_FLOAT32://float
				mFormat[i] = DXGI_FORMAT_R32G32_FLOAT;
				break;
			default:
				mFormat[i] = DXGI_FORMAT_UNKNOWN;
				break;
			}
			break;
		case '\x01'://1����
			switch (str[i * 24 + 12]) {
			case D3D_REGISTER_COMPONENT_FLOAT32://float
				mFormat[i] = DXGI_FORMAT_R32_FLOAT;
				break;
			case D3D_REGISTER_COMPONENT_UINT32://uint
				mFormat[i] = DXGI_FORMAT_R32_UINT;
				break;
			default:
				mFormat[i] = DXGI_FORMAT_UNKNOWN;
				break;
			}
			break;
		default:
			mFormat[i] = DXGI_FORMAT_UNKNOWN;
			break;
		}
	}

	//�ϐ��̐�����V�X�e���l�Z�}���e�B�N�X���t���Ă���ϐ��̐��������Ė����������̂Ƃ���
	mVariable -= mVariablesystem;	

}