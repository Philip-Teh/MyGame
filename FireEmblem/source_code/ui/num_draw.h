#pragma once

#ifndef _NUMDRAW_H_
#define _NUMDRAW_H_

class CNumDraw
{
public:
	void Init(int digit, float sizeX, float sizeY);
	void Uninit(void);
	void Draw(XMFLOAT3 position, int score);
private:
	std::unique_ptr<CNumber> mpNumber;
	int mDigit = 0;
	int mCounterStop = 0;
};



#endif _NUMDRAW_H_