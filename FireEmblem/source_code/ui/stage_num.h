#pragma once

#ifndef STAGE_NUM_H_
#define STAGE_NUM_H_

class CStageNum
{
public:
	CStageNum();
	~CStageNum();

	void Update();
	void Draw(int num);

private:
	std::string mFile;
	std::unique_ptr<CPolygon> mpPolygon;
	std::unique_ptr<CNumDraw> mpNumDraw;					//”š•`‰æ

	const int mSize = 2;
};

#endif // !STAGE_NUM_H_