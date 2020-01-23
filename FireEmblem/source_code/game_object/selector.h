#pragma once

#ifndef SELECTOR_H_
#define SELECTOR_H_

class CSelector : public CGameObject
{
public:
	void Init();
	void Uninti();
	void Update();
	void Draw();

	XMINT2 GetPosition() { return XMINT2((int)m_Position.x, (int)m_Position.z); }

private:
	const char* mModel[2];
	std::unique_ptr<CModelAnimation> mpModelA[2];
	unsigned int mFrame = 0;
};

#endif // !SELECTOR_H_

