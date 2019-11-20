

void CStageManager::Init()
{
	mpMap = make_unique<CMap>();
}

void CStageManager::Uninit()
{

}

void CStageManager::Update()
{
	mpMap->Update();
}

void CStageManager::Draw() 
{
	mpMap->Draw();
}
