using namespace std;


void CNumber::Init(float sizeX,float sizeY)
{
	mFile = "asset/texture/number.png";
	
	mpPolygon = make_unique<CPolygon>();
	mpPolygon->Init(mFile, sizeX, sizeY);
}

void  CNumber::Uninit(void)
{
	mpPolygon->Uninit();
}

void  CNumber::Draw(XMFLOAT3 position,int n)
{
	if (n < 0 || n>9)
	{
		return;
	}
	mpPolygon->Draw(position, n * NUMBER_WIDTH, 0, NUMBER_WIDTH, NUMBER_HEIGHT);
}