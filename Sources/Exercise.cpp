#include "pch.h"

#include <Kore/Application.h>
#include <Kore/IO/FileReader.h>
#include <Kore/Math/Core.h>
#include <Kore/System.h>
#include <Kore/Input/Keyboard.h>
#include <Kore/Input/Mouse.h>
#include <Kore/Audio/Mixer.h>
#include <Kore/Graphics/Image.h>
#include "SimpleGraphics.h"
#include "ObjLoader.h"

using namespace Kore;

namespace {
	double startTime;
	Mesh* mesh;
	Image* image;

	void update() {
		float t = (float)(System::time() - startTime);
		Kore::Audio::update();
		
		startFrame();

		clear(0, 0, 0);
		// Add some nice transformations
		for (int i = 0; i < mesh->numFaces; ++i) {
			int i1 = mesh->indices[i * 3 + 0];
			int i2 = mesh->indices[i * 3 + 1];
			int i3 = mesh->indices[i * 3 + 2];

			float x1 = mesh->vertices[i1 * 5 + 0];
			float y1 = -mesh->vertices[i1 * 5 + 1];
			float z1 = mesh->vertices[i1 * 5 + 2];
			float u1 = mesh->vertices[i1 * 5 + 3];
			float v1 = mesh->vertices[i1 * 5 + 4];

			float x2 = mesh->vertices[i2 * 5 + 0];
			float y2 = -mesh->vertices[i2 * 5 + 1];
			float z2 = mesh->vertices[i2 * 5 + 2];
			float u2 = mesh->vertices[i2 * 5 + 3];
			float v2 = mesh->vertices[i2 * 5 + 4];

			float x3 = mesh->vertices[i3 * 5 + 0];
			float y3 = -mesh->vertices[i3 * 5 + 1];
			float z3 = mesh->vertices[i3 * 5 + 2];
			float u3 = mesh->vertices[i3 * 5 + 3];
			float v3 = mesh->vertices[i3 * 5 + 4];

			float scale = 100.0f;

			drawTriangle(
				x1 * scale + width * 0.5f, y1 * scale + height * 0.5f, z1, u1, v1,
				x2 * scale + width * 0.5f, y2 * scale + height * 0.5f, z2, u2, v2,
				x3 * scale + width * 0.5f, y3 * scale + height * 0.5f, z3, u3, v3);
		}

		endFrame();
	}

	void keyDown(KeyCode code, wchar_t character) {
		if (code == Key_Left) {
			// ...
		}
	}

	void keyUp(KeyCode code, wchar_t character) {
		if (code == Key_Left) {
			// ...
		}
	}

	void mouseMove(int x, int y, int movementX, int movementY) {

	}
	
	void mousePress(int button, int x, int y) {

	}

	void mouseRelease(int button, int x, int y) {

	}
}

float zBuffer[width][height];

void shadePixel(int x, int y, float z, float u, float v) {
	/************************************************************************/
	/* Exercise 4: Practical Task                                           */
	/************************************************************************/
	// Use the passed values to draw a nice pixel using setPixel(x, y, ...).
	// Implement z-buffering
	// Use getPixel to read image data, which is returned in the reference parameters.
	// The texture is provided in the Image "image" (tiger-atlas.jpg in the Deployment-folder)
	
	if (z < zBuffer[x][y]) {
		return;
	}
	zBuffer[x][y] = z;
	float redPixel, greenPixel, bluePixel;
	getPixel(image, u*image->width, v*image->height, redPixel, greenPixel, bluePixel);
	setPixel(x, y, redPixel, greenPixel, bluePixel);
}

int kore(int argc, char** argv) {
	Application* app = new Application(argc, argv, width, height, 0, false, "Exercise4");
	
	initGraphics();
	app->setCallback(update);

	startTime = System::time();
	Kore::Mixer::init();
	Kore::Audio::init();
	//Kore::Mixer::play(new SoundStream("back.ogg", true));

	mesh = loadObj("tiger.obj");
	image = new Image("tiger-atlas.jpg", true);

	Keyboard::the()->KeyDown = keyDown;
	Keyboard::the()->KeyUp = keyUp;
	Mouse::the()->Move = mouseMove;
	Mouse::the()->Press = mousePress;
	Mouse::the()->Release = mouseRelease;

	app->start();

	delete app;
	
	return 0;
}
