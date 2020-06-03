using namespace std;


void CNumber::Init(std::string texture,float sizeX,float sizeY)
{
	mpPolygon = make_unique<CPolygon>();
	mpPolygon->Init(texture, sizeX, sizeY);
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

void  CNumber::Draw(XMFLOAT3 position, int n, int tw, int th)
{
	if (n < 0 || n>9)
	{
		return;
	}
	mpPolygon->Draw(position, n * tw, 0, tw, th);
}