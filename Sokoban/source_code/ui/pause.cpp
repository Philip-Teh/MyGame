//using namespace UI;


CPause::CPause()
{
	mFile = "asset/texture/ui/pause.png";
	mFile1 = "asset/texture/ui/pauseback.png";

	//ƒ|ƒCƒ“ƒ^ì¬
	mpPolygon = std::make_unique<CPolygon>();
	mpPolygon1 = std::make_unique<CPolygon>();

	mpPolygon->Init(mFile, 200, 100);
	mpPolygon1->Init(mFile1, SCREEN_WIDTH, SCREEN_HEIGHT);
}

CPause::~CPause()
{
	mpPolygon->Uninit();
	mpPolygon1->Uninit();

	OutputDebugString("delete CPause\n");
}

void CPause::Update()
{

}

void CPause::Draw()
{
	mpPolygon1->Draw(XMFLOAT3(0.0f, 0.0f, LAYER6));
	mpPolygon->Draw(XMFLOAT3(10.0f, 300.0f, LAYER4));
}