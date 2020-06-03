//using namespace UI;


CReplay::CReplay()
{
	mFile = "asset/texture/scene/replay.png";

	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon->Init(mFile, mWidth, mHeight);
}

CReplay::~CReplay()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CReplay\n");
}

void CReplay::Update()
{
	
}

void CReplay::Draw()
{
	mpPolygon->Draw(XMFLOAT3(mPosition.x, mPosition.y, LAYER1));
}