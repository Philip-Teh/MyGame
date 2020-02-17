using namespace std;

CStep::CStep()
{
	mFile = "asset/texture/ui/step.png";
	mpPolygon = make_unique<CPolygon>();
	mpPolygon->Init(mFile, XMFLOAT3(STATUS_POSITIONX, STATUS_POSITIONY + 40.0f, LAYER6), STATUS_POLYGONX, STATUS_POLYGONY);

	mpNumDraw = make_unique<CNumDraw>();
	mpNumDraw->Init(NUMBER_SIZEX, NUMBER_HEIGHT);
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
	mpNumDraw->Draw(XMFLOAT3(STATUS_POSITIONX + NUMSPACEX, STATUS_POSITIONY + 40.0f + NUMSPACEY, LAYER6), step);
}