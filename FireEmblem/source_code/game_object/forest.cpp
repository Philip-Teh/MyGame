
CForest::CForest()
{
	mTexture = "asset/texture/game_object/tree.png";

	mpField = make_unique<CField>();
	mpField->Init(mTexture);
}

CForest::~CForest()
{
	mpField->Uninit();
}

void CForest::Update()
{
	mpField->Update();
}

void CForest::Draw(XMFLOAT3 position)
{
	m_Position = position;

	mpField->Draw(m_Position);
}
