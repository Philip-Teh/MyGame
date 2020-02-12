//========================================================
//=					2Dピクセルシェーダー				 =
//========================================================

Texture2D Texture : register(t0);
SamplerState Sampler : register(s0);


void main(in float4 inPosition : SV_POSITION, in float4 inDiffuse : COLOR0, in float2 inTexcoord : TEXCOORD0,
		  out float4 outDiffuse : SV_Target)
{
	outDiffuse = Texture.Sample(Sampler, inTexcoord);
	//outDiffuse *= Texture[1].Sample(Sampler, inTexcoord);

	outDiffuse *= inDiffuse;

	//モノクロ
	//outDiffuse = (outDiffuse.r + outDiffuse.g + outDiffuse.a) / 3.0;
	//outDiffuse = outDiffuse.r * 0.299 + outDiffuse.g * 0.587 + outDiffuse.b + 0.114;

	//セピア
	//outDiffuse.r *= 1.07;
	//outDiffuse.g *= 0.74;
	//outDiffuse.b *= 0.43;
}