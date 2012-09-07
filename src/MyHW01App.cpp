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

	// You should give brief descriptions here of your function declarations, stating what they do, 
	// and if necesarry, explain what the inputs will do. 
	// You could use something like the examples I've written below

	/*
	 Draws a rectangle, with center at (x_Coord,y_Coord), of height and width (height, width). 
	 Fills Requirment: Rectangle A.1
	*/
	void drawRectangle(int x_Coord, int y_Coord, int width, int height, uint8_t* data);

	/*
	 Draws a circle, with center at (x_Coord,y_Coord), of radius (radius). 
	 Fills Requirment: Circle A.2
	 Not Complete Yet
	*/
	void drawCircle(int x_Coord, int y_Coord, int radius, uint8_t* data);

	/*
	 Draws a line, with endpoints (x_Coord,y_Coord), of length (length). 
	 Fills Requirment: Line A.3
	*/
	void drawLine(int length, int x_Coord, int y_Coord, uint8_t* data);

	/*
	 Fills in a single pixel with colors specified in private variable declaration
	*/
	void drawPixel(int index, uint8_t* data);

	/*
	 Sets private variables red, green, blue to input values of (r, g, b)
	*/
	void fill(int r, int b, int g);

	/*
	 Clears screen to all black.
	*/
	void clearScreen(uint8_t* data);

	/*
	 returns index of pixel at pos (posX,posY).
	*/
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
	// If you want to have one variable you can use to input color you can use:
	// Color8u fill = Color8u(rValue,gValue,bValue)
	// you can then access the color with fill.r, fill.g, fill.b
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


//You could probably condense this function with MyHW01App::Fill; so that it 
// gets inputs of r,g,b and colors the pixel without using 2 functions. 
void MyHW01App::drawPixel( int index, uint8_t* data) {
	if( index >= 0 && index < data_Index) {
		data[index] = red;
		data[index+1] = green;
		data[index+2] = blue;
	}
}

void  MyHW01App::drawRectangle(int x_Coord, int y_Coord, int width, int height, uint8_t* data) {
	/*
	Might be easier to have the given coord's be the upper left corner, and use height and width from there.
	One way would be like this:

	int index;
	for( int tY = 0; tY < height; tY++ ) {
		for( int tX = 0; tX < width; tX++ ) {
			index = getIndex(tX+x_Coord, tY+y_Coord);
			if( index >= 0 && index < data_Index) {
				data[index] = red;
				data[index+1] = green;
				data[index+2] = blue;
			}
		}
	}

	*/

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
		/*this only works for one direction of line. If you want to try drawing a line between two points:
		drawLine(int x1,int y1, int x2, int y2){
			int length = int(sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))); // finds dist between points
			int fractionX;
			int fractionY;
			for(int i = 0; i < length; i++){
				fractionX = int(x1+(i/double(length))*(x2-x1));
				fractionY = int(y1+(i/double(length))*(y2-y1));
				data[3*(fractionX + fractionY*TextureSize)] = 255;
				data[3*(fractionX + fractionY*TextureSize)+1] = 0;
				data[3*(fractionX + fractionY*TextureSize)+2] = 0;
			}

		}
		*/ 
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
