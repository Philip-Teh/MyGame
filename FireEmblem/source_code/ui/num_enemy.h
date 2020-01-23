#pragma once

#ifndef NUMENEMY_H_
#define NUMENEMY_H_

class CNumEnemy
{
public:
	CNumEnemy();
	~CNumEnemy();
	void Update();
	void Draw(int num);

private:
	std::string mFile;
	std::unique_ptr<CPolygon> mpPolygon;
	std::unique_ptr<CNumDraw> mpNumDraw;					//”š•`‰æ
};

#endif // !NUMENEMY_H_