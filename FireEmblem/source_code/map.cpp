
CMap::CMap()
{
	mpLoadMap = std::make_unique<CLoadMap>();

	mpAllies = std::make_unique<CAllies>();

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
				mpAllies->Draw(XMFLOAT3(x,0,z));

			else if(mpLoadMap->GetType()[z][x]==CObjectType::Enemy)

		}
	}
}