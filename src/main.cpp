#include "config.h"
#include "Control/game_app.h"

int main() {
	// Set the created windows width and height
	int w = 640;
	int h = 480;
	// Create the application and start its event loop. 
	GameApp* app = new GameApp(w, h);
	returnCode nextAction = returnCode::CONTINUE;
	while (nextAction == returnCode::CONTINUE) {
		nextAction = app->mainLoop();
	}
	// Clear up resources and exit
	delete app;
	return 0;
}