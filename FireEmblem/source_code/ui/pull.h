#pragma once

#ifndef PULL_H_
#define PULL_H_

class CPull
{
public:
	CPull();
	~CPull();
	void Update();
	void Draw();

	void SetLock(bool lock) { mLock = lock; }
	void Appear() { mKeyDown = true; }

private:
	std::string mFile[3];
	std::unique_ptr<CPolygon> mpPolygon[3];

	const int mMaxMove = 80;
	const int mSpeed = 5;

	int mMove = 0;
	bool mKeyUp = false;
	bool mKeyDown = false;
	bool mLock = false;
};

#endif // !PULL_H_