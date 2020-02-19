//using namespace UI;


CPause::CPause()
{
	mFile[0] = "asset/texture/ui/pause.png";
	mFile[1] = "asset/texture/ui/pauseback.png";

	for (int i = 0; i < 2; i++)
		mpPolygon[i] = std::make_unique<CPolygon>();

	mpPolygon[0]->Init(mFile[0], 200, 100);
	mpPolygon[1]->Init(mFile[1], SCREEN_WIDTH, SCREEN_HEIGHT);
}

CPause::~CPause()
{
	for (int i = 0; i < 2; i++)
		mpPolygon[i]->Uninit();

	OutputDebugString("delete CPause\n");
}

void CPause::Update()
{

}

void CPause::Draw()
{
	mpPolygon[1]->Draw(XMFLOAT3(0.0f, 0.0f, LAYER6));
	mpPolygon[0]->Draw(XMFLOAT3(10.0f, 300.0f, LAYER4));
}