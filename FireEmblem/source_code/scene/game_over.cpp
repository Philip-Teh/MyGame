using namespace std;


void CGameOver::Init()
{
	mFile[0] = "asset/texture/over.png";
	mFile[1] = "asset/texture/gameover.png";
	mFile[2] = "asset/texture/troop.png";

	for (int i = 0; i < 3; i++)
		mpPolygon[i] = make_unique<CPolygon>();

	mpPolygon[0]->Init(mFile[0], XMFLOAT3(0.0f, 0.0f, 0.2f), SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[1]->Init(mFile[1], XMFLOAT3(350.0f, 130.0f, 0.1f), 600, 250);
	mpPolygon[2]->Init(mFile[2], XMFLOAT3(100.0f, 430.0f, 0.0f), 1050, 250);

	mMove = mMove1 = mMove2 = 0;
	mKeypress = false;
}

void CGameOver::Uninit()
{
	for (int i = 0; i < 3; i++)
		mpPolygon[i]->Uninit();

	OutputDebugString("delete CGameOver\n");
}

void CGameOver::Update()
{
	if (!mKeypress) {
		mMove += 10;
		if (mMove >= 500)
			mMove1 += 10;

		if (mMove1 >= 500)
			mMove2 += 10;
	}

	mMove = MaxMove(mMove);
	mMove1 = MaxMove(mMove1);
	mMove2 = MaxMove(mMove2);

	if (mKeypress) {
		mMove -= 10;
		mMove1 -= 10;
		mMove2 -= 10;
	}

	if (mMove <= 0)mMove = 0;
	if (mMove1 <= 0)mMove1 = 0;
	if (mMove2 <= 0)mMove2 = 0;

	//mpPolygon[0]->Update(XMFLOAT3(0.0f, mMove - SCREEN_HEIGHT, 0.2f));
	//mpPolygon[1]->Update(XMFLOAT3(350.0f, mMove1 - 600, 0.1f));
	//mpPolygon[2]->Update(XMFLOAT3(100.0f, mMove2 - 300, 0.0f));

	if (CInput::GetKeyTrigger(VK_RETURN))
	{
		CSceneManager::SetScene<CTitle>();
	}
}

void CGameOver::Draw()
{
	for (int i = 0; i < 3; i++)
		mpPolygon[i]->Draw();
}

int CGameOver::MaxMove(int move)
{
	if (move >= SCREEN_HEIGHT)
		move = SCREEN_HEIGHT;

	return move;
}

bool CGameOver::ShowEnd(void)
{
	if (mMove2 == SCREEN_HEIGHT)
		return true;
	else
		return false;
}

bool CGameOver::ResetShow(void)
{
	if (mMove2 == 0)
		return true;
	else
		return false;
}
