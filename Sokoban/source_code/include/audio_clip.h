#pragma once

//============================================================================
//=																			 =
//=						サウンド関連　オディオクリップ						 =
//=																			 =
//============================================================================

#define SOUND_SOURCE_MAX (4)

enum class CBGM
{
	Start=0,
	Game=1,
	Clear=2,
	End=3
};

class CAudioClip
{

public:

	static void Init();
	static void Uninit();

	static void Load(const char *FileName);
	static void Unload();
	static void Play(bool Loop, CBGM bgm);
	static void Play(bool Loop = false);
	static void Stop(CBGM bgm);
	static void StopAll();


private:
	static IXAudio2*				m_Xaudio;
	static IXAudio2MasteringVoice*	m_MasteringVoice;

	static IXAudio2SourceVoice*	m_SourceVoice[SOUND_SOURCE_MAX];
	static BYTE*					m_SoundData[SOUND_SOURCE_MAX];

	static int						m_Length;
	static int						m_PlayLength;

	static int mNumBGM;
};

