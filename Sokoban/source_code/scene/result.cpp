using namespace std;
 
void CResult::Init()
{
	mTexture[0] = "asset/texture/scene/result.png";
	mTexture[1] = "asset/texture/scene/Rclear.png";
	mTexture[2] = "asset/texture/scene/Rover.png";
	mTexture[3] = "asset/texture/ui/score.png";

	//ポインタ作成
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

	//ファイル読み込み
	mFilename = "score/score.txt";
	mFile = fopen(mFilename.c_str(), "r");

	for (int i = 0; i < mMaxScore; i++) {
		fgets(mRead, 15, mFile);

		mGet.push_back(atoi(mRead));
	}
	fclose(mFile);

	//ゲームのスコアを比較し、整列
	if (mGet.back() < CGameStatus::GetScore()) {

		mGet.pop_back();
		mGet.push_back(CGameStatus::GetScore());
		mGet.sort();
		mGet.reverse();
	}

	mScore = 0;

	//ローディングシーン終了
	CLoading::SetChange(false);

	//エンターインターフェース表示
	CEnter::SetEnable(true);
}

void CResult::Uninit()
{	
	//ゲーム状態によって音声は違います
	if (CGameStatus::GetGameOver())
		CAudioClip::Stop(CBGM::End);

	else if (CGameStatus::GetGameClear())
		CAudioClip::Stop(CBGM::Clear);

	//最新スコアを保存
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

	//エンターインターフェース非表示
	CEnter::SetEnable(false);

	OutputDebugString("delete CResult\n");
}

void CResult::Update()
{
	//スコアの演出
	mScore += 15;
	if (mScore >= CGameStatus::GetScore())
		mScore = CGameStatus::GetScore();

	if (mScore == CGameStatus::GetScore())
		mMove -= 15;

	if (mMove <= 0)
		mMove = 0;

	//ローディングシーン表示
	if (mMove <= 500 && CInput::GetKeyTrigger(VK_RETURN))
		CLoading::SetEnable(true);

	//シーンチェンジ
	if (mMove == 0 && CLoading::GetChange())
		CSceneManager::SetScene<CTitle>();
}

void CResult::Draw()
{
	//ゲームの状態によって背景が変わります
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

	//高いスコアから順に並んで描画
	for (auto i : mGet) {

		//今回のゲームスコア
		if (i == CGameStatus::GetScore() && !flag) {

			//順位
			mpNumDraw[1]->Draw(XMFLOAT3(120.0f, 250.0f + mMove+j, LAYER3), num);

			//スコア
			mpNumDraw[1]->Draw(XMFLOAT3(320.0f, 250.0f + mMove+j, LAYER3), i);

			j += NUMBER_HEIGHT;
			num++;
			flag = true;

			continue;
		}

		//保存したハイスコア
		//順位
		mpNumDraw[0]->Draw(XMFLOAT3(120.0f, 250.0f+j, LAYER3), num);

		//スコア
		mpNumDraw[0]->Draw(XMFLOAT3(320.0f, 250.0f+j, LAYER3), i);

		j += NUMBER_HEIGHT;
		num++;
	}

}
