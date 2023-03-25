// By @ByCubed7 on Twitter

//#define VERBOSE

//#include "Core.h"
//#include "Components.h"
//#include "Tilemaps.h"
//#include "Render.h"
//#include "Audio.h"
//#include "UI.h"
#include "All.h"

#include <iostream>

#include "Tests/VectorTest.h"

using namespace Engine;

int main(int argc, char* argv[])
{
	Tests::TestVector3();

	srand(static_cast <unsigned>(time(0)));

	//FreeConsole();
	App app = App();
	Scene* scene = app.CreateGame();

	// Prepares an OpenGL context so that we can send API calls
	app.Build();
	app.Load(scene);

	// Mainloop
	return app.Run();
}


 
