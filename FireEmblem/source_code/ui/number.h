#pragma once

//============================================================================
//=																			 =
//=							”š‚ğŠÇ—‚·‚éƒNƒ‰ƒX							 =
//=																			 =
//============================================================================

#ifndef _NUMBER_H_
#define _NUMBER_H_

class CNumber
{
public:
	void Init(std::string texture,float sizeX, float sizeY);
	void Uninit(void);
	void Draw(XMFLOAT3 position, int n);
	void Draw(XMFLOAT3 position, int n, int tw, int th);

	unsigned GetDigit(unsigned num)const {
		return (int)std::to_string(num).length();
	}

private:
	std::unique_ptr<CPolygon> mpPolygon = nullptr;

};



#endif _NUMBER_H_