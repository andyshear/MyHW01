/**
	@author Jake Rego
	@filename MyHW01App.cpp
	*/

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include <iostream>
#include "cinder/ImageIo.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MyHW01App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	void prepare(Settings* windowSettings);
	void drawRectangle(int x_Coord, int y_Coord, int width, int height, uint8_t* data);
	void drawCircle(int x_Coord, int y_Coord, int radius, uint8_t* data);
	void drawLine(int length, int x_Coord, int y_Coord, uint8_t* data);
	void drawPixel(int index, uint8_t* data);
	void fill(int r, int b, int g);
	void clearScreen(uint8_t* data);
	int getIndex(int posX, int posY);

	int length;
	Settings* windowSettings;
	
private:
	Surface* pic_Surface; // The surface object with a pixel array to be changed	
	gl::Texture* pic_Texture;
};

	///Screen Dimensions
	static const int AppWidth = 800;
	static const int AppHeight = 600;
	static const int TextureSize = 1024;
	static const int data_Index = AppWidth+AppHeight*3;

	///Color Variables
	int red = 0;
	int blue = 0;
	int green = 0;
	
	int length = 200;

void  MyHW01App::fill(int r, int g, int b) {
	red = r;
	green = g;
	blue = b;
}

void  MyHW01App::clearScreen(uint8_t* data) {
	for( int i=0; i<data_Index; i++ ){
		data[i] = 0;
	}
}

void MyHW01App::drawPixel( int index, uint8_t* data) {
	if( index >= 0 && index < data_Index) {
		data[index] = red;
		data[index+1] = green;
		data[index+2] = blue;
	}
}

void  MyHW01App::drawRectangle(int x_Coord, int y_Coord, int width, int height, uint8_t* data) {
	int index;

	for( int tY = -height/2; tY <= height/2; tY++ ) {
		for( int tX = -width/2; tX <= width/2; tX++ ) {
			index = getIndex(tX+x_Coord, tY+y_Coord);
			if( index >= 0 && index < data_Index) {
				data[index] = red;
				data[index+1] = green;
				data[index+2] = blue;
			}
		}
	}

}


void  MyHW01App::drawLine( int length, int x_Coord, int y_Coord, uint8_t* data ) {
	for( int i = 0; i < length; i++ ) {
		data[3*(x_Coord+y_Coord*TextureSize)] = 255;
		data[3*(x_Coord+y_Coord*TextureSize)+1] = 0;
		data[3*(x_Coord+y_Coord*TextureSize)+2] = 0;
		
		x_Coord += 1;
		y_Coord += 1;
	}
}

/**
	Gets the number index location of the position in the array
*/
int MyHW01App::getIndex(int posX, int posY) {
	return 3*(posY*AppWidth+posX);
}

void MyHW01App::prepare(Settings* windowSettings) {
		(*windowSettings).setWindowSize(AppWidth, AppHeight); /// Setting the window size to AppWidth x AppHeight
		(*windowSettings).setResizable(false); /// Cannot resize window
}

void MyHW01App::setup()
{
	pic_Surface = new Surface(AppWidth, AppHeight, false);
	pic_Texture = new gl::Texture(*pic_Surface);
	uint8_t* data = (*pic_Surface).getData();
	clearScreen(data);
}

void MyHW01App::mouseDown( MouseEvent event )
{
}

void MyHW01App::update()
{
	uint8_t* data_array = (*pic_Surface).getData();
	fill(0, 0, 250);
	drawRectangle(200, AppHeight/2, 600, 700, data_array);
	drawLine(200, 160, 160, data_array);

	(*pic_Texture).update(*pic_Surface,(*pic_Surface).getBounds());
}

void MyHW01App::draw()
{
	gl::draw(*pic_Surface); 
}

CINDER_APP_BASIC( MyHW01App, RendererGl )
