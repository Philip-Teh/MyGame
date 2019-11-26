//============================================================================
//=																			 =
//=								�����̕��m									 =
//=																			 =
//============================================================================

CAlliesTroop::CAlliesTroop()
{
	mTexture = "asset/texture/character/a_troop.png";

	mpField = make_unique<CField>();
	mpField->Init(mTexture);
}

CAlliesTroop::~CAlliesTroop()
{
	OutputDebugString("delete CAlliesTroop\n");
}

void CAlliesTroop::Update()
{
	mpField->Update();
}

void CAlliesTroop::Draw(XMFLOAT3 position)
{
	mpField->Draw(position);
}
