

void CMountain::Init()
{
	mTexture = "asset/texture/game_object/mountain.png";

	mpField = make_unique<CField>();
	mpField->Init(mTexture);
}

void CMountain::Uninit()
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