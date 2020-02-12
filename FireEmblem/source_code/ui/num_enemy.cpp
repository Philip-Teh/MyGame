using namespace std;

CNumEnemy::CNumEnemy()
{
	mFile = "asset/texture/ui/enemy.png";
	mpPolygon = make_unique<CPolygon>();
	mpPolygon->Init(mFile, XMFLOAT3(STATUS_POSITIONX, STATUS_POSITIONY + 80.0f, LAYER5), STATUS_POLYGONX, STATUS_POLYGONY);

	mpNumDraw = make_unique<CNumDraw>();
	mpNumDraw->Init(NUMBER_SIZEX, NUMBER_HEIGHT);
}

CNumEnemy::~CNumEnemy()
{
	mpPolygon->Uninit();
	mpNumDraw->Uninit();

	OutputDebugString("delete CScore\n");
}

void CNumEnemy::Update()
{

}

void CNumEnemy::Draw(int num)
{
	mpPolygon->Draw();
	mpNumDraw->Draw(XMFLOAT3(STATUS_POSITIONX + NUMSPACEX, STATUS_POSITIONY + 80.0f + NUMSPACEY, LAYER5), num);
}