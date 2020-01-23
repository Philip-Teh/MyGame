

void CLoadMap::Load(int mapID)
{
	FILE* file;
	std::string mapid = std::to_string(mapID);

	mFilename = "asset/map/map" + mapid + ".bin";

	if ((file = fopen(mFilename.c_str(), "rb")) == nullptr)
	{
		MessageBox(NULL, "�ǂݍ��ݎ��s", "�G���[", MB_OK);
	}

	mMapX = 0;
	mMapZ = 0;
	mMaxEnemyTroop = 0;

	//�}�b�v�T�C�Y���擾
	mMapX = fgetc(file);
	mMapZ = fgetc(file);

	//�������m��
	mpType = new CObjectType * [mMapZ];
	mpBox = new CBoxType * [mMapZ];

	for (int x = 0; x < mMapZ; x++)
	{
		mpType[x] = new CObjectType[mMapX];
		mpBox[x] = new CBoxType[mMapX];
	}

	//������
	Init();

	fgets(mMap, MapSizeX * MapSizeZ, file);

	//�}�b�v�̃I�u�W�F�N�g�̎��
	for (int i = 0; i < mMapX * mMapZ; i++)
	{
		switch ((CObjectType)mMap[i])
		{
		case CObjectType::Player:
			mpType[i / mMapX][i % mMapX] = CObjectType::Floor;
			SetPlayerPosition(XMINT2(i % mMapX, i / mMapX));
			break;
		case CObjectType::Enemy:
			mpType[i / mMapX][i % mMapX] = CObjectType::Floor;
			SetEnemyPosition(XMINT2(i % mMapX, i / mMapX));
			mMaxEnemyTroop++;
			break;
		case CObjectType::Floor:
			mpType[i / mMapX][i % mMapX] = CObjectType::Floor;
			break;
		case CObjectType::Wall:
			mpType[i / mMapX][i % mMapX] = CObjectType::Wall;
			break;
		case CObjectType::Goal:
			mpType[i / mMapX][i % mMapX] = CObjectType::Goal;
			break;
		case CObjectType::None:
			mpType[i / mMapX][i % mMapX] = CObjectType::None;
			break;
		default:
			mpType[i / mMapX][i % mMapX] = CObjectType::None;
			break;
		}
	}

	for (int i = 0; i < mMapX * mMapZ; i++)
	{
		switch ((CBoxType)mMap[i + mMapX * mMapZ])
		{
		case CBoxType::Exists:
			mpBox[i / mMapX][i % mMapX] = CBoxType::Exists;
			mFirstBoxPosition.push_back(XMINT2(i / mMapX, i % mMapX));
			break;
		case CBoxType::None:
			mpBox[i / mMapX][i % mMapX] = CBoxType::None;
			break;
		default:
			mpBox[i / mMapX][i % mMapX] = CBoxType::None;
			break;
		}
	}

	fclose(file);
}

void CLoadMap::ReleaseMap(void)
{
	for (int z = 0; z < mMapZ; z++)
	{
		delete[] mpType[z];
		delete[] mpBox[z];
	}

	delete[]mpType;
	delete[]mpBox;
}

void CLoadMap::Init()
{
	for (int i = 0; i < mMapX * mMapZ; i++)
	{
		mpType[i / mMapX][i % mMapX] = CObjectType::None;
		mpBox[i / mMapX][i % mMapX] = CBoxType::None;
	}
}