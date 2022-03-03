#include <iostream>	
#include <Ogre.h>
#include <SDL.h>
#include <SDL_syswm.h>

using namespace std;

void openSDLWindow() {

	int posX = SDL_WINDOWPOS_CENTERED;
	int posY = SDL_WINDOWPOS_CENTERED;
	int width = 800;
	int height = 600;
	Uint32 vflags = 0;


	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR, "Cannot initialize SDL2!",
			"BaseApplication::setup");
	}

	Ogre::Root* root = new Ogre::Root();
	root->restoreConfig();
	root->initialise(false);

	Ogre::NameValuePairList params; // ogre window / render system params
	SDL_Window* sdlWindow = SDL_CreateWindow("myWindow", posX, posY, width, height, vflags);
	// see SDL_CreateWindow docs / examples for how to populate posX, posY, width, height, and vflags according to your needs

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	if (SDL_GetWindowWMInfo(sdlWindow, &wmInfo) == SDL_FALSE) {
		OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,
			"Couldn't get WM Info! (SDL2)",
			"BaseApplication::setup");
	}

	params.insert(std::make_pair("macAPI", "cocoa"));
	params.insert(std::make_pair("macAPICocoaUseNSView", "true"));

	// grab a string representing the NSWindow pointer
	//Ogre::String winHandle = Ogre::StringConverter::toString((unsigned long)wmInfo.info.cocoa.window);

	// assign the NSWindow pointer to the parentWindowHandle parameter
	//params.insert(std::make_pair("parentWindowHandle", winHandle));

	bool isFullscreen = false;

	Ogre::RenderWindow* ogreWindow = root->createRenderWindow("myWindowTitle", width, height, isFullscreen, &params);
	// see OGRE documentation on how to populate width, height, and isFullscreen to suit your needs

	// create OGRE scene manager, camera, viewports, etc
}

int main(int argc, char** argv[]) {
	int susmuertos = 0;
	std::cout << "Bienvenido a Aegis Engine.\n";

	openSDLWindow();

	return 0;
}