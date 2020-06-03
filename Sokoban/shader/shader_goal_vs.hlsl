

//*****************************************************************************
// 定数バッファ
//*****************************************************************************

// マトリクスバッファ
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
// 頂点シェーダ
//=============================================================================
void main(in float4 inPosition : POSITION0, in float4 inNormal : NORMAL0, in float4 inDiffuse : COLOR0, in float2 inTexcoord : TEXCOORD0,
	out float4 outPosition : SV_POSITION, out float4 outWorldPosition : POSITION1, out float4 outNormal : NORMAL0, out float4 outDiffuse : COLOR0, out float4 outSpecular : COLOR1, out float2 outTexcoord : TEXCOORD0, out float4 outLightDirection : POSITION2, out float4 outCameraPosition : POSITIONT3)
{
    matrix wvp;
	//マトリクス乗算
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    outPosition = mul(inPosition, wvp); //座標変換

    outWorldPosition = mul(inPosition, World);

	//法線ベクトルの移動成分を無くすため(回転すると伸びる)
    inNormal.w = 0.0;
    outNormal = mul(inNormal, World);

	//法線ベクトルも一緒に回転するため座標変換
    float4 worldNormal = mul(inNormal, World);
	//法線の拡大縮小を1にする
    worldNormal = normalize(worldNormal);

	//スペキュラ(鏡面反射)
    float4 worldPosition = mul(inPosition, World);
    float3 refv = reflect(Light.Direction.xyz, worldNormal.xyz); //反射
    refv = normalize(refv);

    float3 eyev = worldPosition - CameraPosition; //視線ベクトル
    eyev = normalize(eyev);

    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 10); //10乗

    outSpecular = specular;

    outDiffuse = inDiffuse * Light.Diffuse * Light.Ambient;
    outTexcoord = inTexcoord;
    outLightDirection = Light.Direction;
    outCameraPosition = CameraPosition;
}
