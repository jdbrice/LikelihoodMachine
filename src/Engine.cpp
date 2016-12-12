

// RooBarb
#include "XmlConfig.h"
#include "TaskEngine.h"
#include "SharedTreeAnalyzer.h"
using namespace jdb;

// STL
#include <iostream>
#include <exception>


#include "LikelihoodMachine.h"


int main( int argc, char* argv[] ) {

	TaskEngine engine( argc, argv );



	XmlConfig xfg( "test.xml" );
	LikelihoodMachine lm;
	lm.load( xfg, "LikelihoodMachine" );

	INFO( "Engine", lm.toString() );

	INFO( "Engine", "p(Signal) = " << lm.eval( "signal", 0.0 ) );

	INFO( "Engine", "p(Background) = " << lm.eval( "background", 0.0 ) );



	return 0;
}
