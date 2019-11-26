//============================================================================
//=																			 =
//=								“G‚Ì•ºŽm									 =
//=																			 =
//============================================================================

CEnemyTroop::CEnemyTroop()
{
	mTexture = "asset/texture/character/e_troop.png";

	mpField = make_unique<CField>();
	mpField->Init(mTexture);
}

CEnemyTroop::~CEnemyTroop()
{
	OutputDebugString("delete CEnemyTroop\n");
}

void CEnemyTroop::Update()
{
	mpField->Update();
}

void CEnemyTroop::Draw(XMFLOAT3 position)
{
	mpField->Draw(position);
}
