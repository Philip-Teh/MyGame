

//*****************************************************************************
// �萔�o�b�t�@
//*****************************************************************************

// �}�g���N�X�o�b�t�@
cbuffer ConstantBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;
    float4 CameraPosition;
}

struct LIGHT
{
    float4 Direction;
    float4 Diffuse;
    float4 Ambient;
};

cbuffer LightBuffer : register(b1)
{
    LIGHT Light;
}


//=============================================================================
// ���_�V�F�[�_
//=============================================================================
void main(in float4 inPosition : POSITION0, in float4 inNormal : NORMAL0, in float4 inDiffuse : COLOR0, in float2 inTexcoord : TEXCOORD0,
	out float4 outPosition : SV_POSITION, out float4 outWorldPosition : POSITION1, out float4 outNormal : NORMAL0, out float4 outDiffuse : COLOR0, out float4 outSpecular : COLOR1, out float2 outTexcoord : TEXCOORD0, out float4 outLightDirection : POSITION2, out float4 outCameraPosition : POSITIONT3)
{
    matrix wvp;
	//�}�g���N�X��Z
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    outPosition = mul(inPosition, wvp); //���W�ϊ�

    outWorldPosition = mul(inPosition, World);

	//�@���x�N�g���̈ړ������𖳂�������(��]����ƐL�т�)
    inNormal.w = 0.0;
    outNormal = mul(inNormal, World);

	//�@���x�N�g�����ꏏ�ɉ�]���邽�ߍ��W�ϊ�
    float4 worldNormal = mul(inNormal, World);
	//�@���̊g��k����1�ɂ���
    worldNormal = normalize(worldNormal);

	//�X�y�L����(���ʔ���)
    float4 worldPosition = mul(inPosition, World);
    float3 refv = reflect(Light.Direction.xyz, worldNormal.xyz); //����
    refv = normalize(refv);

    float3 eyev = worldPosition - CameraPosition; //�����x�N�g��
    eyev = normalize(eyev);

    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 10); //10��

    outSpecular = specular;

    outDiffuse = inDiffuse * Light.Diffuse * Light.Ambient;
    outTexcoord = inTexcoord;
    outLightDirection = Light.Direction;
    outCameraPosition = CameraPosition;
}
