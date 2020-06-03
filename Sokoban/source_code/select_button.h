#pragma once

#ifndef STAGE_BUTTON_H_
#define STAGE_BUTTON_H_


#define BUTTON (3)	//選択できるステージの数


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
		//テクスチャ
		std::string mTexture[2] = {};

		//テクスチャポインタ
		std::unique_ptr<CPolygon> mpPolygon[BUTTON + 2] = {};

		const float mSize = 100.0f;			//テクスチャのサイズ
		const float mPositionX = 125.0f;	//テクスチャのX位置
		const float mPositionY = 300.0f;	//テクスチャのY位置
		const float mSpace = 200.0f;		//ボタンの間のスペース
		const int mButtonX = 5;				//一行のボタンの数

		//ファイルパスを保存し、読み込みの変数
		char mFilename[50] = "";

		//選んだボタンのナンバー
		int mChoose = 0;

		//クリアしたステージの判定
		bool mClear[BUTTON + 1] = {};

		//キーボード入力操作
		void KeyInput();
	};
//}

#endif // !STAGE_BUTTON_H_
