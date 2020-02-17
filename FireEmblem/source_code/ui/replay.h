#pragma once


#ifndef REPLAY_H
#define REPLAY_H

//namespace UI
//{

	class CReplay
	{
	public:
		CReplay();
		~CReplay();

		void Update();
		void Draw();

	private:
		std::string mTexture = "";
		std::unique_ptr<CPolygon> mpPolygon = nullptr;

		const float mWidth = 640.0f;
		const float mHeight = 480.0f;
		const XMFLOAT2 mPosition = XMFLOAT2(350.0f, 100.0f);
	};
//}
#endif


