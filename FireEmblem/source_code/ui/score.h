#pragma once

#ifndef SCORE_H_
#define SCORE_H_

class CScore
{
public:
	CScore();
	~CScore();
	void Update();
	void Draw(int score);

private:
	std::string mFile;
	std::unique_ptr<CPolygon> mpPolygon;
	std::unique_ptr<CNumDraw> mpNumDraw;					//”š•`‰æ
};

#endif // !SCORE_H_