#pragma once

#ifndef _NUMDRAW_H_
#define _NUMDRAW_H_

class CNumDraw
{
public:
	void Init(float sizeX, float sizeY);
	void Uninit(void);
	void Draw(XMFLOAT3 position, int score);
	void Draw(XMFLOAT3 position, int score,int tw,int th);
private:
	std::unique_ptr<CNumber> mpNumber;
	int mDigit = 0;
	int mCounterStop = 0;
};



#endif _NUMDRAW_H_