#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MyHW01App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void MyHW01App::setup()
{
}

void MyHW01App::mouseDown( MouseEvent event )
{
}

void MyHW01App::update()
{
}

void MyHW01App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( MyHW01App, RendererGl )
