#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "Population.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class NOC_9_02_SmartRockets_superbasicApp : public AppNative {
  public:
	void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
	
	int mLifetime;				// How long should each generation live
	Population *mPopulation;		// Population
	int mLifeCounter;			// Timer for cycle of generation
	Vec2f mTarget;				// Target location
};

void NOC_9_02_SmartRockets_superbasicApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 640, 360 );
}

void NOC_9_02_SmartRockets_superbasicApp::setup()
{
	// The number of cycles we will allow a generation to live
	mLifetime = getWindowHeight();
	
	// Initialize variables
	mLifeCounter = 0;
	
	mTarget = Vec2f( getWindowWidth() / 2.0, 24.0 );
	
	// Create a population with a mutation rate, and population max
	float mutationRate = 0.01;
	mPopulation = new Population( mutationRate, 50 );
}

// Move the target if the mouse is pressed
// System will adapt to new target
void NOC_9_02_SmartRockets_superbasicApp::mouseDown( MouseEvent event )
{
	mTarget = event.getPos();
}

void NOC_9_02_SmartRockets_superbasicApp::update()
{
}

void NOC_9_02_SmartRockets_superbasicApp::draw()
{
	// clear out the window with black
	gl::clear( Color::white() );
	
	// Draw the start and target locations
	gl::color( Color::black() );
	gl::drawSolidEllipse( mTarget, 24.0, 24.0 );
	
	// If the generation hasn't ended yet
	if( mLifeCounter < mLifetime )
	{
		mPopulation->live();
		mLifeCounter++;
		// Otherwise a new generation
	}
	else
	{
		mLifeCounter = 0;
		mPopulation->fitness();
		mPopulation->selection();
		mPopulation->reproduction();
	}
	
	// Display some info
	gl::color( Color::black() );
	text("Generation #: " + population.getGenerations(), 10, 18);
	text("Cycles left: " + (lifetime-lifeCounter), 10, 36);
}

void NOC_9_02_SmartRockets_superbasicApp::drawText( string str, int fontSize, Vec2i pos )
{
	Font font = Font( mFont.getName(), fontSize );
	TextBox tbox = TextBox().alignment( TextBox::LEFT ).font( font ).size( Vec2i( getWindowWidth(), TextBox::GROW ) ).text( str );
	tbox.setColor( Color::black() );
	tbox.setBackgroundColor( ColorA( 0, 0, 0, 0 ) );
	gl::draw( tbox.render(), pos );
}

CINDER_APP_NATIVE( NOC_9_02_SmartRockets_superbasicApp, RendererGl )
