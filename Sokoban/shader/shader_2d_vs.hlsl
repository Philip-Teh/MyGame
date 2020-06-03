//========================================================
//=					2D頂点シェーダー					 =
//========================================================


//定数バッファ
cbuffer ConstantBuffer : register(b0)
{
	//グローバル変数と同じ役割
	matrix World;
	matrix View;
	matrix Projection;
}

//		　入力  型		引数　セマンティクス								出力(戻り値)
void main(in float4 inPosition : POSITION0, in float4 inDiffuse : COLOR0, in float2 inTexcoord : TEXCOORD0,
		  out float4 outPosition : SV_POSITION, out float4 outDiffuse : COLOR0, out float2 outTexcoord : TEXCOORD0)
{
	//座標変換関数( 頂点シェーダーxyzw, マトリクス )
	outPosition = mul(inPosition, Projection);
	
	outDiffuse = inDiffuse;
	outTexcoord = inTexcoord;
}