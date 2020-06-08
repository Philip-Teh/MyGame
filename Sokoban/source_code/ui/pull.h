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

	//引けるか引けないかをセット
	void SetLock(bool lock) { mLock = lock; }

	//隠しインターフェースを表示
	void Appear() { mKeyDown = true; }

private:
	std::string mFile2;
	std::unique_ptr<CPolygon> mpPolygon2;

	const int mMaxMove = 80;
	const int mSpeed = 5;

	bool mLock = false;
};

#endif // !PULL_H_