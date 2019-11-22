

CPlain::CPlain()
{
	mTexture = "asset/texture/game_object/plain.png";

	mpField = make_unique<CField>();
	mpField->Init(mTexture);
}

CPlain::~CPlain()
{
	mpField->Uninit();
}

void CPlain::Update()
{
	mpField->Update();
}

void CPlain::Draw(XMFLOAT3 position)
{
	m_Position = position;

	mpField->Draw(m_Position);
}