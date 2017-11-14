#include "pch.h"

#include <Kore/IO/FileReader.h>
#include <Kore/Math/Core.h>
#include <Kore/System.h>
#include <Kore/Input/Keyboard.h>
#include <Kore/Input/Mouse.h>
#include <Kore/Audio1/Audio.h>
#include <Kore/Graphics1/Graphics.h>
#include "GraphicsHelper.h"
#include "Memory.h"
#include "ObjLoader.h"

const int width = 512;
const int height = 512;

using namespace Kore;

namespace {
	double startTime;
	Mesh* mesh;
	
	// Add more simple variables if you like to
	// but put bigger things in memory.
	// Avoid any "new".
	u8* image;
	int imageWidth;
	int imageHeight;
	
	void update() {
		float t = (float)(System::time() - startTime);
		Kore::Audio2::update();
		
		Graphics1::begin();
		clear(0.0f, 0.0f, 0.0f);
		
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
			
			// Draw the triangle
			float drawScale = 128;
			drawTriangle(x1 * drawScale + width / 2, y1 * drawScale + height / 2, z1, u1, v1,
						 x2 * drawScale + width / 2, y2 * drawScale + height / 2, z2, u2, v2,
						 x3 * drawScale + width / 2, y3 * drawScale + height / 2, z3, u3, v3);
		}
		
		Graphics1::end();
	}
	
	void keyDown(KeyCode code) {
		if (code == KeyLeft) {
			// ...
		}
	}
	
	void keyUp(KeyCode code) {
		if (code == KeyLeft) {
			// ...
		}
	}
	
	void mouseMove(int window, int x, int y, int movementX, int movementY) {
		
	}
	
	void mousePress(int window, int button, int x, int y) {
		
	}
	
	void mouseRelease(int window, int button, int x, int y) {
		
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
	readPixel(image, imageWidth, imageHeight, (int) (u*imageWidth), (int) (v*imageHeight), redPixel, greenPixel, bluePixel);
	
	Graphics1::setPixel(x, y, redPixel, greenPixel, bluePixel);
}

int kore(int argc, char** argv) {
	System::init("Solution 4", width, height);
	
	Graphics1::init(width, height);
	Kore::System::setCallback(update);
	
	startTime = System::time();
	
	Kore::Audio2::init();
	Kore::Audio1::init();
	
	Memory::init();
	mesh = loadObj("tiger.obj");
	image = loadImage("tiger-atlas.jpg", &imageWidth, &imageHeight);
	
	Keyboard::the()->KeyDown = keyDown;
	Keyboard::the()->KeyUp = keyUp;
	Mouse::the()->Move = mouseMove;
	Mouse::the()->Press = mousePress;
	Mouse::the()->Release = mouseRelease;
	
	Kore::System::start();
	
	return 0;
}
