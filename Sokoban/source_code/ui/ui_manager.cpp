using namespace std;
//using namespace UI;

CUIManager::CUIManager()
{
	//ポインタ作成
	mpScore = make_unique<CScore>();
	mpStep = make_unique<CStep>();
	mpNumEnemy = make_unique<CNumEnemy>();
	mpPull = make_unique<CPull>();
	mpStageNum = make_unique<CStageNum>();

	mpMenu = make_unique<CMenu>();
	mpHelp = make_unique<CHelp>();
	mpKeyInfo = make_unique<CKeyInfo>();
	mpTitle = make_unique<CReturnTitle>();
	mpReturn = make_unique<CReturnStageSelect>();

	mpReset = make_unique<CReset>();
	mpExit = make_unique<CExit>();

	mpPause = make_unique<CPause>();
}

CUIManager::~CUIManager()
{
	OutputDebugString("delete CUIMAnager\n");
}

void CUIManager::Update()
{
	mpMenu->Update();

	//メニュー操作中
	if (mpMenu->GetKeyUp())
	{
		mpHelp->Update();
		mpKeyInfo->Update();
		mpTitle->Update();
		mpReturn->Update();
	}

	//メニュー退出時に全てのインターフェースを終了
	if (mpMenu->GetKeyDown())
	{
		mpHelp->TabCancel();
		mpKeyInfo->TabCancel();
		mpTitle->TabCancel();
		mpReturn->TabCancel();
	}

	mpReset->Update();

	mpExit->Update();

	//ゲーム退出時に確認インターフェースを表示
	if (mpExit->GetKeyUp())
	{
		if (CInput::GetKeyTrigger(VK_YEA))
			CExitTrigger::SetExit(true);

		else if (CInput::GetKeyTrigger(VK_NAY))
			mpExit->TabCancel();
	}
}

void CUIManager::Update(bool enable)
{
	if (enable)
	{
		mpNumEnemy->Update();
		mpPull->Update();
	}
}

//スコアとステップの描画
void CUIManager::DrawStatus(int score,int step)
{
	mpScore->Draw(score);
	mpStep->Draw(step);
}

//敵と引く鍵の描画
void CUIManager::DrawEnemyStatus(int num)
{
	mpNumEnemy->Draw(num);
	mpPull->Draw();
}

//ステージナンバー描画
void CUIManager::DrawStageNum(int num)
{
	mpStageNum->Draw(num);
}

//メニュー描画
void CUIManager::DrawMenu()
{
	//メニュー操作時にゲーム一時停止画面を描画
	if (mpMenu->GetKeyUp())
		mpPause->Draw();

	mpMenu->Draw();
	mpHelp->Draw();
	mpKeyInfo->Draw();
	mpTitle->Draw();
	mpReturn->Draw();

	mpReset->Draw();
	mpExit->Draw();
}

//隠しインターフェースを描画
void CUIManager::Appear()
{
	mpNumEnemy->Appear();
	mpPull->Appear();
}