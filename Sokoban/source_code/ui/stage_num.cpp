using namespace std;

CStageNum::CStageNum()
{
	mFile = "asset/texture/ui/stage.png";

	//É|ÉCÉìÉ^çÏê¨
	mpPolygon =  make_unique<CPolygon>();
	mpPolygon->Init(mFile, XMFLOAT3(10.0f, 0.0f, LAYER7), STATUS_POLYGONX * mSize, STATUS_POLYGONY * mSize);

	mpNumDraw = make_unique<CNumDraw>();
	mpNumDraw->Init((float)NUMBER_SIZEX * mSize, (float)NUMBER_HEIGHT * mSize);
}

CStageNum::~CStageNum()
{
	mpPolygon->Uninit();
	mpNumDraw->Uninit();

	OutputDebugString("delete CStageNum\n");
}

void CStageNum::Update()
{

}

void CStageNum::Draw(int num)
{
	mpPolygon->Draw();
	mpNumDraw->Draw(XMFLOAT3(0.0f + NUMSPACEX, 0.0f + NUMSPACEY, LAYER7), num, NUMBER_WIDTH* (int)mSize, NUMBER_HEIGHT * (int)mSize);
}