#pragma once

//============================================================================
//=																			 =
//=								“o‚ê‚È‚¢ŽR									 =
//=																			 =
//============================================================================

#ifndef MOUNTAIN_H_
#define MOUNTAIN_H_

class CMountain : public CGameObject
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw(XMFLOAT3 position);

private:
	
};

#endif // !MOUNTAIN_H_

