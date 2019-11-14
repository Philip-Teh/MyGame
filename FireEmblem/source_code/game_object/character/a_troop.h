#pragma once

//============================================================================
//=																			 =
//=								–¡•û‚Ì•ºŽm									 =
//=																			 =
//============================================================================

#ifndef ATROOP_H_
#define ATROOP_H_

class CAlliesTroop : public CAllies
{
public:
	void Init();
	void Uninit();
	void Update();
	void Draw(XMFLOAT3 position);
private:

};

#endif // !ATROOP_H_
