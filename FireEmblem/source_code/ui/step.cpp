using namespace std;

CStep::CStep()
{
	mFile = "asset/texture/ui/step.png";
	mpPolygon = make_unique<CPolygon>();
	mpPolygon->Init(mFile, XMFLOAT3(800.0f, 50.0f, 0.0f), 100, 50);

	mpNumDraw = make_unique<CNumDraw>();
	mpNumDraw->Init(5, 320, NUMBER_HEIGHT);
}

CStep::~CStep()
{
	mpPolygon->Uninit();
	mpNumDraw->Uninit();

	OutputDebugString("delete CStep\n");
}

void CStep::Update()
{

}

void CStep::Draw(int step)
{
	mpPolygon->Draw();
	mpNumDraw->Draw(XMFLOAT3(950.0f, 50.0f, 0.0f), step);
}