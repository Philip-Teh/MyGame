#pragma once

//============================================================================
//=																			 =
//=							描画関連	数字描画							 =
//=																			 =
//============================================================================

#ifndef _NUMDRAW_H_
#define _NUMDRAW_H_

class CNumDraw
{
public:
	//白い数字
	void Init(float sizeX, float sizeY);

	//緑色の数字
	void InitGreen(float sizeX, float sizeY);

	void Uninit(void);
	void Draw(XMFLOAT3 position, int score);
	void Draw(XMFLOAT3 position, int score,int tw,int th);
private:
	std::unique_ptr<CNumber> mpNumber = nullptr;	//ナンバーを管理するポインタ
	std::string mTexture = "";

	int mDigit = 0;			//桁数
	int mCounterStop = 0;	//描画の最大数
};



#endif _NUMDRAW_H_