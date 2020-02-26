#pragma once

//============================================================================
//=																			 =
//=					ユーザーインターフェース	引く						 =
//=																			 =
//============================================================================

#ifndef PULL_H_
#define PULL_H_

class CPull : public CUI
{
public:
	CPull();
	~CPull();

	void Update();
	void Draw();

	void SetLock(bool lock) { mLock = lock; }
	void Appear() { mKeyDown = true; }

private:
	std::string mFile2;
	std::unique_ptr<CPolygon> mpPolygon2;

	const int mMaxMove = 80;
	const int mSpeed = 5;

	bool mLock = false;
};

#endif // !PULL_H_