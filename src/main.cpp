#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "Game.h"

int main(){
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 800, 460, OF_WINDOW);			
    ofRunApp(new Game());
}
