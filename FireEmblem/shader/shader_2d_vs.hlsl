//========================================================
//=					2D���_�V�F�[�_�[					 =
//========================================================


//�萔�o�b�t�@
cbuffer ConstantBuffer : register(b0)
{
	//�O���[�o���ϐ��Ɠ�������
	matrix World;
	matrix View;
	matrix Projection;
}

//		�@����  �^		�����@�Z�}���e�B�N�X								�o��(�߂�l)
void main(in float4 inPosition : POSITION0, in float4 inDiffuse : COLOR0, in float2 inTexcoord : TEXCOORD0,
		  out float4 outPosition : SV_POSITION, out float4 outDiffuse : COLOR0, out float2 outTexcoord : TEXCOORD0)
{
	//���W�ϊ��֐�( ���_�V�F�[�_�[xyzw, �}�g���N�X )
	outPosition = mul(inPosition, Projection);
	
	outDiffuse = inDiffuse;
	outTexcoord = inTexcoord;
}