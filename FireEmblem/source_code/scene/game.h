#pragma once

#ifndef GAME_H_
#define GAME_H_

class CGame : public CScene
{
public:
	void Init();
	void Uninit();
	void Update();
private:
	std::string texture;
	CAudioClip* m_BGM;
};

#endif // !GAME_H_

