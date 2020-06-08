using namespace std;

string CEnter::mFile = "";
unique_ptr<CPolygon> CEnter::mpPolygon = nullptr;
unsigned int CEnter::mFrame = 0;
bool CEnter::mEnable = false;
XMFLOAT2 CEnter::mPosition = XMFLOAT2(1210.0f, 620.0f);

const int gWidth = 60;
const int gHeight = 90;

void CEnter::Init()
{
	mFile = "asset/texture/ui/enter.png";

	//É|ÉCÉìÉ^çÏê¨
	mpPolygon = make_unique<CPolygon>();
	mpPolygon->Init(mFile, gWidth, gHeight);

	mFrame = 0;
	mEnable = false;
}

void CEnter::Uninit()
{
	mpPolygon->Uninit();

	OutputDebugString("delete CEnter\n");
}

void CEnter::Update()
{
	if (mEnable)
	{
		mFrame++;
		if (mFrame >= 75)
			mFrame = 0;
	}
}

void CEnter::Draw()
{
	if (mEnable && mFrame >= 30)
		mpPolygon->Draw(XMFLOAT3(mPosition.x, mPosition.y, LAYER2));
}

void CEnter::SetPosition(XMFLOAT2 position)
{
	if (!mEnable)
	{
		mPosition = position;
		mEnable = true;
	}
}