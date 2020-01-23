#pragma once

#ifndef _NUMBER_H_
#define _NUMBER_H_

#define NUMBER_WIDTH (32)
#define NUMBER_HEIGHT (32)

class CNumber
{
public:
	void Init(float sizeX, float sizeY);
	void Uninit(void);
	void Draw(XMFLOAT3 position, int n);

private:
	std::string mFile;
	std::unique_ptr<CPolygon> mpPolygon;

};



#endif _NUMBER_H_