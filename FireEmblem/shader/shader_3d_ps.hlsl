//========================================================
//=					3Dピクセルシェーダー				 =
//========================================================

Texture2D gTexture : register(t0);
//Texture2D Texture[2] : register(t0);
SamplerState gSampler : register(s0);

void main(in float4 inPosition : SV_POSITION, in float4 inWorldPosition : POSITION1, in float4 inNormal : NORMAL0, in float4 inDiffuse : COLOR0, in float4 inSpecular : COLOR1, in float2 inTexcoord : TEXCOORD0, in float4 inLightDirection : POSITION2,
		out float4 outDiffuse : SV_Target)
{
	outDiffuse = gTexture.Sample(gSampler, inTexcoord);

	//outDiffuse = Texture[0].Sample(Sampler, inTexcoord);
	//outDiffuse *= Texture[1].Sample(Sampler, inTexcoord);
	inNormal = normalize(inNormal);

	float light = -dot(inNormal.xyz, inLightDirection);
	light += 0.5 - inNormal * inDiffuse * 0.5;
	light = saturate(light);



	outDiffuse *= inDiffuse * light;

	outDiffuse += inSpecular;
	outDiffuse.a = 1.0;



	//モノクロ
	//outDiffuse = (outDiffuse.r + outDiffuse.g + outDiffuse.a) / 3.0;
	//outDiffuse = outDiffuse.r * 0.299 + outDiffuse.g * 0.587 + outDiffuse.b + 0.114;

	//セピア
	//outDiffuse.r *= 1.07;
	//outDiffuse.g *= 0.74;
	//outDiffuse.b *= 0.43;
}