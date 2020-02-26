#pragma once

//============================================================================
//=																			 =
//=								シーン　リザルト							 =
//=																			 =
//============================================================================

#ifndef RESULT_H
#define RESULT_H

//namespace Scene
//{
	class CResult : public CScene
	{

	public:
		void Init();
		void Uninit();
		void Update();							
		void Draw();						

	private:
		std::string mTexture[4] = {};
		std::unique_ptr<CPolygon> mpPolygon[4] = {};
		std::unique_ptr<CNumDraw> mpNumDraw[2] = {};
		
		FILE* mFile = nullptr;
		std::string mFilename = "";

		std::list<int> mGet = {};
		char mRead[15] = {};
		const int mMaxScore = 10;

		int mMove = SCREEN_HEIGHT;
		int mScore = 0;

	};
//}
#endif
