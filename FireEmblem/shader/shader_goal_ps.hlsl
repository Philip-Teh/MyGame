

//*****************************************************************************
// 定数バッファ
//*****************************************************************************

// マテリアルバッファ
cbuffer MaterialBuffer : register( b1 )
{
	float4		Ambient;
	float4		Diffuse;
	float4		Specular;
	float4		Emission;
	float		Shininess;
	float3		Dummy;//16bit境界用
}





//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D		g_Texture : register( t0 );
SamplerState	g_SamplerState : register( s0 );


//=============================================================================
// ピクセルシェーダ
//=============================================================================
void main(in float4 inPosition : SV_POSITION, in float4 inWorldPosition : POSITION1, in float4 inNormal : NORMAL0, in float4 inDiffuse : COLOR0, in float4 inSpecular : COLOR1, in float2 inTexcoord : TEXCOORD0, in float4 inLightDirection : POSITION2,
		out float4 outDiffuse : SV_Target)
{

    outDiffuse = g_Texture.Sample( g_SamplerState, inTexcoord );

    float light = -dot(inNormal.xyz, inLightDirection.xyz);
    light += 0.5 - inNormal * inDiffuse * 0.5;
    light = saturate(light);



    outDiffuse *= inDiffuse * light;
    outDiffuse += inSpecular;
}
