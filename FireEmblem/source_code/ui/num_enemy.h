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

	void Appear() { mKeyDown = true; }

private:
	std::string mFile;
	std::unique_ptr<CPolygon> mpPolygon;
	std::unique_ptr<CNumDraw> mpNumDraw;					//êîéöï`âÊ

	const int mMaxMove = 40;
	const int mSpeed = 5;

	int mMove = 0;
	bool mKeyUp = false;
	bool mKeyDown = false;
};

#endif // !NUMENEMY_H_