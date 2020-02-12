//#ifndef RENDERER_H_
//#define RENDERER_H_
//
//// 頂点構造体
//struct NVERTEX_3D
//{
//    XMFLOAT3 Position;
//    XMFLOAT3 Normal;
//    XMFLOAT4 Diffuse;
//    XMFLOAT2 TexCoord;
//};
//
//
//// 色構造体
//struct NCOLOR
//{
//	NCOLOR() = default;
//	NCOLOR( float _r, float _g, float _b, float _a )
//	{
//		r = _r;
//		g = _g;
//		b = _b;
//		a = _a;
//	}
//
//	float r = 0.0f;
//	float g = 0.0f;
//	float b = 0.0f;
//	float a = 0.0f;
//};
//
//// マテリアル構造体
//struct NMATERIAL
//{
//	NCOLOR		Ambient;
//	NCOLOR		Diffuse;
//	NCOLOR		Specular;
//	NCOLOR		Emission;
//	float		Shininess = 0.0f;
//	float		Dummy[3] = {};	//16bit境界用
//};
//
//
//
//
//// マテリアル構造体
//struct NDX11_MODEL_MATERIAL
//{
//	MATERIAL		Material;
//	class CTexture* Texture = nullptr;
//};
//
//
//// 描画サブセット構造体
//struct NDX11_SUBSET
//{
//	unsigned short	StartIndex = NULL;
//	unsigned short	IndexNum = NULL;
//	DX11_MODEL_MATERIAL	Material;
//};
//
//struct NLIGHT
//{
//	XMFLOAT4	Direction = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
//	NCOLOR		Diffuse;
//	NCOLOR		Ambient;
//
//};
//
//
//class CVertexBuffer;
//class CIndexBuffer;
//class CTexture;
//
//
//class Renderer
//{
//private:
//
//	static D3D_FEATURE_LEVEL       m_FeatureLevel;
//
//	static ID3D11Device*           m_D3DDevice;
//	static ID3D11DeviceContext*    m_ImmediateContext;
//	static IDXGISwapChain*         m_SwapChain;
//	static ID3D11RenderTargetView* m_RenderTargetView;
//	static ID3D11DepthStencilView* m_DepthStencilView;
//
//
//
//	static ID3D11VertexShader*     m_VertexShader;
//	static ID3D11PixelShader*      m_PixelShader;
//	static ID3D11InputLayout*      m_VertexLayout;
//	static ID3D11Buffer*			m_WorldBuffer;
//	static ID3D11Buffer*			m_ViewBuffer;
//	static ID3D11Buffer*			m_ProjectionBuffer;
//	static ID3D11Buffer*			m_MaterialBuffer;
//	static ID3D11Buffer*			m_LightBuffer;
//
///*
//	static XMMATRIX				m_WorldMatrix;
//	static XMMATRIX				m_ViewMatrix;
//	static XMMATRIX				m_ProjectionMatrix;
//*/
//	static ID3D11DepthStencilState* m_DepthStateEnable;
//	static ID3D11DepthStencilState* m_DepthStateDisable;
//
//
//public:
//	static void Init();
//	static void Uninit();
//	static void Begin();
//	static void End();
//
//	static void SetDepthEnable(bool Enable);
//	static void SetWorldViewProjection2D();
//	static void SetWorldMatrix(XMMATRIX * WorldMatrix);
//	static void SetViewMatrix(XMMATRIX * ViewMatrix);
//	static void SetProjectionMatrix(XMMATRIX * ProjectionMatrix);
//	static void SetMaterial(MATERIAL Material);
//	static void SetLight(LIGHT Light);
//	static void SetVertexBuffers( ID3D11Buffer* VertexBuffer );
//	static void SetIndexBuffer( ID3D11Buffer* IndexBuffer );
//	static void SetTexture(CTexture* Texture);
//	static void DrawIndexed( unsigned int IndexCount, unsigned int StartIndexLocation, int BaseVertexLocation );
//	static void DrawIndexedSTRIP(unsigned int IndexCount, unsigned int StartIndexLocation, int BaseVertexLocation);
//
//	static ID3D11Device* GetDevice( void ){ return m_D3DDevice; }
//	static ID3D11DeviceContext* GetDeviceContext( void ){ return m_ImmediateContext; }
//};
//
//#endif