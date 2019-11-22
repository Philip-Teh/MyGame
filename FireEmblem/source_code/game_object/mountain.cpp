

CMountain::CMountain()
{
	mTexture = "asset/texture/game_object/mountain.png";

	mpField = make_unique<CField>();
	mpField->Init(mTexture);
}

CMountain::~CMountain()
{
	mpField->Uninit();
}

void CMountain::Update()
{
	mpField->Update();
}

void CMountain::Draw(XMFLOAT3 position)
{
	m_Position = position;

	mpField->Draw(m_Position);
}