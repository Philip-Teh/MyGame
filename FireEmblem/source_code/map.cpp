
CMap::CMap()
{
	mpLoadMap = std::make_unique<CLoadMap>();

	mpAlliesTroop = std::make_unique<CAlliesTroop>();
	mpEnemyTroop = std::make_unique<CEnemyTroop>();
	mpMountain = std::make_unique<CMountain>();
	mpPlain = std::make_unique<CPlain>();
	mpForest = std::make_unique<CForest>();

	mpLoadMap->Load(1);

	mMapX = mpLoadMap->GetMapX();
	mMapZ = mpLoadMap->GetMapZ();
}

CMap::~CMap()
{
	OutputDebugString("delete CMap\n");
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
				mpAlliesTroop->Draw(XMFLOAT3((float)x, 0, (float)z));

			else if (mpLoadMap->GetType()[z][x] == CObjectType::Enemy)
				mpEnemyTroop->Draw(XMFLOAT3((float)x, 0, (float)z));

			else if (mpLoadMap->GetType()[z][x] == CObjectType::Plain)
				mpPlain->Draw(XMFLOAT3((float)x, 0, (float)z));

			else if (mpLoadMap->GetType()[z][x] == CObjectType::Forest)
				mpForest->Draw(XMFLOAT3((float)x, 0, (float)z));

			else if (mpLoadMap->GetType()[z][x] == CObjectType::Mountain)
				mpMountain->Draw(XMFLOAT3((float)x, 0, (float)z));

			else if (mpLoadMap->GetType()[z][x] == CObjectType::None)
				continue;
			else
				OutputDebugString("CMap unknown type");
		}
	}
}