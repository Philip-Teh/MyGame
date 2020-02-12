#pragma once

#ifndef _NUMBER_H_
#define _NUMBER_H_

class CNumber
{
public:
	void Init(float sizeX, float sizeY);
	void Uninit(void);
	void Draw(XMFLOAT3 position, int n);

	unsigned GetDigit(unsigned num)const {
		return (int)std::to_string(num).length();
	}

private:
	std::string mFile;
	std::unique_ptr<CPolygon> mpPolygon;

};



#endif _NUMBER_H_