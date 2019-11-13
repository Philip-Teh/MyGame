#ifndef RESULT_H_
#define RESULT_H_

class CResult : public CScene
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

#endif // !RESULT_H_
