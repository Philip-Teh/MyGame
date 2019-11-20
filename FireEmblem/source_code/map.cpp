
CMap::CMap()
{
	mpLoadMap = std::make_unique<CLoadMap>();

	mpAllies = std::make_unique<CAllies>();
	mpEnemy = std::make_unique<CEnemy>();
	mpMountain = std::make_unique<CMountain>();
	mpPlain = std::make_unique<CPlain>();
	mpForest = std::make_unique<CForest>();

	mpLoadMap->Load(1);

	mMapX = mpLoadMap->GetMapX();
	mMapZ = mpLoadMap->GetMapZ();
}

CMap::~CMap()
{

}

void CMap::Update()
{

}

void CMap::Draw()
{
	for (int z = 0; z < mMapZ; z++)
	{
		for (int x = 0; x < mMapX; x++)
		{
			if (mpLoadMap->GetType()[z][x] == CObjectType::Allies)
				mpAllies->Draw(XMFLOAT3((float)x, 0, (float)z));

			else if (mpLoadMap->GetType()[z][x] == CObjectType::Enemy)
				mpEnemy->Draw(XMFLOAT3((float)x, 0, (float)z));

			else if (mpLoadMap->GetType()[z][x] == CObjectType::Plain)
				mpPlain->Draw(XMFLOAT3((float)x, 0, (float)z));

			else if (mpLoadMap->GetType()[z][x] == CObjectType::Forest)
				mpForest->Draw(XMFLOAT3((float)x, 0, (float)z));

			else if (mpLoadMap->GetType()[z][x] == CObjectType::Mountain)
				mpMountain->Draw(XMFLOAT3((float)x, 0, (float)z));

			else return;
		}
	}
}