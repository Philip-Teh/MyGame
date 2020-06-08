using namespace std;


CFloor::CFloor()
{
	mTexture = "asset/texture/game_object/floor.png";

	//ƒ|ƒCƒ“ƒ^ì¬
	mpField = make_unique<CField>();
	mpField->Init(mTexture);
}

CFloor::~CFloor()
{
	mpField->Uninit();

	OutputDebugString("delete CFloor\n");
}

void CFloor::Update()
{
	mpField->Update();
}

void CFloor::Draw(XMFLOAT3 position)
{
	m_Position = position;

	mpField->Draw(m_Position, 0);
}