#pragma once

#ifndef STAGE_BUTTON_H_
#define STAGE_BUTTON_H_


#define BUTTON (10)


//namespace UI
//{
	class CSelectButton
	{
	public:
		CSelectButton();
		~CSelectButton();

		void Update();
		void Draw();

	private:
		std::string mTexture[2] = {};
		std::unique_ptr<CPolygon> mpPolygon[BUTTON + 2] = {};

		const float mSize = 100.0f;
		const float mPositionX = 125.0f;
		const float mPositionY = 300.0f;
		const float mSpace = 200.0f;
		const int mButtonX = 5;

		char mFilename[50] = "";

		int mChoose = 0;
		bool mClear[BUTTON + 1] = {};

		void KeyInput();
	};
//}

#endif // !STAGE_BUTTON_H_
