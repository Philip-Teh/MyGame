#pragma once

#ifndef STEP_H_
#define STEP_H_

class CStep
{
public:
	CStep();
	~CStep();
	void Update();
	void Draw(int step);

private:
	std::string mFile;
	std::unique_ptr<CPolygon> mpPolygon;
	std::unique_ptr<CNumDraw> mpNumDraw;					//”š•`‰æ
};

#endif // !STEP_H_