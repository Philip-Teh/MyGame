//using namespace Scene;

std::unique_ptr<CPolygon> CLoading::mpPolygon[2] = {};
float CLoading::mMove = 0.0f;
int CLoading::mFrame = 0;
bool CLoading::mMoveDirection = false;
bool CLoading::mChanging = false;
bool CLoading::mEnable = false;
int CLoading::mPatternX = 0;
int CLoading::mPatternY = 0;

const int gTexWidth = 243, gTexHeight = 150;
const int gLiveTexWidth = 81, gLiveTexHeight = 75;

const int gLiveX1 = 0, gLiveX2 = 81, gLiveX3 = 162;
const int gLiveY1 = 0, gLiveY2 = 75;

std::string mTexture1 = "asset/texture/scene/loading.png";

void CLoading::Init()
{
	for (int i = 0; i < 2; i++)
		mpPolygon[i] = std::make_unique<CPolygon>();

	mpPolygon[0]->Init(mTexture1, SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[1]->Init("asset/texture/scene/walk.png", gTexWidth, gTexHeight);

	mMove = SCREEN_WIDTH;
	mFrame = 0;
	mMoveDirection = false;
	mChanging = false;
	mEnable = false;
}

void CLoading::Uninit()
{
	for (int i = 0; i < 2; i++)
		mpPolygon[i]->Uninit();

	OutputDebugString("delete CLoading\n");
}

bool CLoading::Update()
{
	if (!mMoveDirection && mEnable)
	{
		mMove /= 1.5f;

		mPatternY = gLiveY1;

		if (mMove <= 1)
		{
			mMove = 1.0f;
			mMoveDirection = true;
			mChanging = true;
		}
	}

	if (mMove <= 1.0f && !mChanging)
		mFrame++;

	if (mMoveDirection && mFrame >= 5)
	{
		mMove += 100.0f;

		mPatternY = gLiveY2;

		if (mMove >= SCREEN_WIDTH)
		{
			mMove = (float)SCREEN_WIDTH;
			mMoveDirection = false;
			return true;
		}
	}

	mPatternX += gLiveX2;
	if (mPatternX >= gLiveX3 + 1)
		mPatternX = gLiveX1;

	return false;
}

void CLoading::Draw()
{
	mpPolygon[0]->Draw(XMFLOAT3(mMove, 0.0f, LAYER1), 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[1]->Draw(XMFLOAT3(mMove + 1150.0f, 590.0f, LAYER0), mPatternX, mPatternY, gLiveTexWidth, gLiveTexHeight);
}