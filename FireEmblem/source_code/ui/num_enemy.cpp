using namespace std;

CNumEnemy::CNumEnemy()
{
	mFile = "asset/texture/ui/enemy.png";
	mpPolygon = make_unique<CPolygon>();
	mpPolygon->Init(mFile, XMFLOAT3(800.0f, 90.0f, 0.0f), 100, 50);

	mpNumDraw = make_unique<CNumDraw>();
	mpNumDraw->Init(5, 320, NUMBER_HEIGHT);
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
	mpNumDraw->Draw(XMFLOAT3(950, 90, 0.0f), num);
}