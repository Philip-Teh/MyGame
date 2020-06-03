using namespace std;
 
void CResult::Init()
{
	mTexture[0] = "asset/texture/scene/result.png";
	mTexture[1] = "asset/texture/scene/Rclear.png";
	mTexture[2] = "asset/texture/scene/Rover.png";
	mTexture[3] = "asset/texture/ui/score.png";

	for (int i = 0; i < 2; i++)
		mpNumDraw[i] = make_unique<CNumDraw>();

	mpNumDraw[0]->Init(NUMBER_SIZEX, NUMBER_HEIGHT);
	mpNumDraw[1]->InitGreen(NUMBER_SIZEX, NUMBER_HEIGHT);

	for (int i = 0; i < 4; i++)
		mpPolygon[i] = make_unique<CPolygon>();

	mpPolygon[0]->Init(mTexture[0], XMFLOAT3(0.0f, 0.0f, LAYER4), SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[1]->Init(mTexture[1], XMFLOAT3(0.0f, 0.0f, LAYER5), SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[2]->Init(mTexture[2], XMFLOAT3(0.0f, 0.0f, LAYER5), SCREEN_WIDTH, SCREEN_HEIGHT);
	mpPolygon[3]->Init(mTexture[3], XMFLOAT3(500.0f, 200.0f, LAYER3), 100, 50);

	mFilename = "score/score.txt";
	mFile = fopen(mFilename.c_str(), "r");

	for (int i = 0; i < mMaxScore; i++) {
		fgets(mRead, 15, mFile);

		mGet.push_back(atoi(mRead));
	}
	fclose(mFile);

	if (mGet.back() < CGameStatus::GetScore()) {

		mGet.pop_back();
		mGet.push_back(CGameStatus::GetScore());
		mGet.sort();
		mGet.reverse();
	}

	mScore = 0;

	CLoading::SetChange(false);
	CEnter::SetEnable(true);
}

void CResult::Uninit()
{	
	if (CGameStatus::GetGameOver())
		CAudioClip::Stop(CBGM::End);

	else if (CGameStatus::GetGameClear())
		CAudioClip::Stop(CBGM::Clear);

	mFile = fopen(mFilename.c_str(), "r+");
	
	for (auto i : mGet)
	{
		std::string a = std::to_string(i) + "\n";
		fprintf(mFile, a.c_str());
	}
	mGet.clear();
	
	for (int i = 0; i < 4; i++)
		mpPolygon[i]->Uninit();

	for (int i = 0; i < 2; i++)
		mpNumDraw[i]->Uninit();

	fclose(mFile);

	CEnter::SetEnable(false);

	OutputDebugString("delete CResult\n");
}

void CResult::Update()
{
	mScore += 15;
	if (mScore >= CGameStatus::GetScore())
		mScore = CGameStatus::GetScore();

	if (mScore == CGameStatus::GetScore())
		mMove -= 15;

	if (mMove <= 0)
		mMove = 0;

	if (mMove <= 500 && CInput::GetKeyTrigger(VK_RETURN))
		CLoading::SetEnable(true);

	if (mMove == 0 && CLoading::GetChange())
		CSceneManager::SetScene<CTitle>();
}

void CResult::Draw()
{
	if (CGameStatus::GetGameOver())
		mpPolygon[2]->Draw();
	if (CGameStatus::GetGameClear())
		mpPolygon[1]->Draw();

	mpPolygon[0]->Draw();

	bool flag = false;
	int j = 0;
	int num = 1;

	mpPolygon[3]->Draw();
	mpNumDraw[1]->Draw(XMFLOAT3(750.0f, 200.0f, LAYER3), mScore);


	for (auto i : mGet) {

		if (i == CGameStatus::GetScore() && !flag) {

			mpNumDraw[1]->Draw(XMFLOAT3(120.0f, 250.0f + mMove+j, LAYER3), num);
			//DrawString((int)(225 * Screen::X()), (int)((425 + j + mMove)* Screen::Y()), "o", GetColor(0, 255, 0));

			mpNumDraw[1]->Draw(XMFLOAT3(320.0f, 250.0f + mMove+j, LAYER3), i);

			j += NUMBER_HEIGHT;
			num++;
			flag = true;
			continue;
		}

		mpNumDraw[0]->Draw(XMFLOAT3(120.0f, 250.0f+j, LAYER3), num);
		//DrawString((int)(225 * Screen::X()), (int)((425 + j + mMove) * Screen::Y()), "o", GetColor(0, 255, 0));

		mpNumDraw[0]->Draw(XMFLOAT3(320.0f, 250.0f+j, LAYER3), i);
		j += NUMBER_HEIGHT;
		num++;
	}

}
