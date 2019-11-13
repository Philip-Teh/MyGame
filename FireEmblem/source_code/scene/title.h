#ifndef TITLE_H_
#define TITLE_H_

class CTitle : public CScene
{
private:
	std::string texture;
	CPolygon* polygon;
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};

#endif // !TITLE_H_

