#pragma once

#ifndef BGM_MANAGER_H_
#define BGM_MANAGER_H_

//============================================================================
//=																			 =
//=							背景音楽マネージャー							 =
//=																			 =
//============================================================================

class CBGM_Manager
{
public:
	static void SetBGM(std::string bgm);
	static void UnloadBGM();

private:
	static std::unique_ptr<CAudioClip> mp_BGM;

};

#endif // !BGM_MANAGER_H_

