#pragma once

#ifndef GAMEOVER_H
#define GAMEOVER_H

class CGameOver : public CScene
{

public:
	void Init();
	void Uninit();

	void Update();
	void Draw();
	bool ResetShow(void);
	bool ShowEnd(void);
	void SetKey(bool press) { mKeypress = press; }
	bool GetKey() { return mKeypress; }

private:
	std::string mFile[3];
	std::unique_ptr<CPolygon> mpPolygon[3];
	int mMove, mMove1, mMove2;
	bool mKeypress;

	int MaxMove(int move);
};

#endif
