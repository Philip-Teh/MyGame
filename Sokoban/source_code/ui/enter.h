#pragma once

//============================================================================
//=																			 =
//=					ユーザーインターフェース	エンター					 =
//=																			 =
//============================================================================

#ifndef ENTER_H_
#define ENTER_H_

class CEnter
{

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();

	static void SetPosition(XMFLOAT2 position);
	static void SetEnable(bool enable) { mEnable = enable; }

private:
	static std::string mFile;
	static std::unique_ptr<CPolygon> mpPolygon;
	static unsigned int mFrame;	//表示するフレーム
	static bool mEnable;
	static XMFLOAT2 mPosition;
};

#endif // !ENTER_H_

