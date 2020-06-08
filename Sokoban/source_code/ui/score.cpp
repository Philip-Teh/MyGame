using namespace std;

CScore::CScore()
{
	mFile = "asset/texture/ui/score.png";

	//É|ÉCÉìÉ^çÏê¨
	mpPolygon = make_unique<CPolygon>();
	mpPolygon->Init(mFile, XMFLOAT3(STATUS_POSITIONX, STATUS_POSITIONY, LAYER7), STATUS_POLYGONX, STATUS_POLYGONY);

	mpNumDraw = make_unique<CNumDraw>();
	mpNumDraw->Init(NUMBER_SIZEX, NUMBER_HEIGHT);
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
	mpNumDraw->Draw(XMFLOAT3(STATUS_POSITIONX + NUMSPACEX, STATUS_POSITIONY + NUMSPACEY, LAYER7), score);
}