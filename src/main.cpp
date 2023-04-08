#include "config.h"	
#include "Control/game_app.h"	

int main() {
	// Set the window width and height 
	int w = 640;
	int h = 480;
	GameApp* app = new GameApp(w, h);
	returnCode nextAction = returnCode::CONTINUE;
	while (nextAction == returnCode::CONTINUE) {
		nextAction = app->mainLoop();
	}
	delete app;
	return 0;
}