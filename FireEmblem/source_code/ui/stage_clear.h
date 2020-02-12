#pragma once

#ifndef STAGECLEAR_H
#define STAGECLEAR_H

//namespace StageSystem
//{
	class CStageClear
	{
	public:
		CStageClear();
		~CStageClear();

		void Update();
		void Draw();
		
		void SetMove(void);
		bool DrawCompleted(void);

	private:
		std::unique_ptr<CPolygon> mpPolygon = nullptr;
		int mMoveX = 0, mMoveY = 0;

	};
//}
#endif
