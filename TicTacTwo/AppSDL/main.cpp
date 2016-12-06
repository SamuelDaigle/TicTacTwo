// AppSDL.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SDLWindowAPI.h"
#include "../GameRender/stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		//ScoreRepository repo;
		IWindowAPI * windowAPI = new SDLWindowAPI(640, 480, "MainWindow");
		WindowRender * windowRender = new WindowRender(*windowAPI);

		windowRender->run();
	}
	catch (exception & e)
	{
		std::cout << e.what() << std::endl;
		system("pause");
	}

	return 0;
}

