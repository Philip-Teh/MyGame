#pragma once


#ifndef PAUSE_H
#define PAUSE_H

//namespace UI
//{

	class CPause
	{
	public:
		CPause();
		~CPause();

		void Update();
		void Draw();

	private:
		std::string mFile[2] = {};
		std::unique_ptr<CPolygon> mpPolygon[2] = {};
	};
//}
#endif


