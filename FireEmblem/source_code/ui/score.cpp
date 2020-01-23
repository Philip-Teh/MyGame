using namespace std;

CScore::CScore()
{
	mFile = "asset/texture/ui/score.png";
	mpPolygon = make_unique<CPolygon>();
	mpPolygon->Init(mFile, XMFLOAT3(800.0f, 10.0f, 0.0f), 100, 50);

	mpNumDraw = make_unique<CNumDraw>();
	mpNumDraw->Init(5, 320, NUMBER_HEIGHT);
}

CScore::~CScore()
{
	mpPolygon->Uninit();
	mpNumDraw->Uninit();

	OutputDebugString("delete CScore\n");
}

void CScore::Update()
{

}

void CScore::Draw(int score)
{
	mpPolygon->Draw();
	mpNumDraw->Draw(XMFLOAT3(950, 10, 0.0f), score);
}