

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
	

	{
		INFO( "Engine", "Testing FormulaPDFs" );
		LikelihoodMachine lm;
		lm.load( xfg, "LikelihoodMachine" );
	
		INFO( "Engine", lm.toString() );
	
		INFO( "Engine", "p(Signal) = " << lm.eval( "signal", 9.0 ) );
	
		INFO( "Engine", "p(Background) = " << lm.eval( "background", 9.0 ) );
	}
	{
		INFO( "Engine", "Testing HistogramPDFs" ); 
		LikelihoodMachine lm;
		lm.load( xfg, "LikelihoodMachine[1]" );
	
		INFO( "Engine", lm.toString() );
	
		INFO( "Engine", "p(Signal) = " << lm.eval( "signal", 1.0 ) );
	
		INFO( "Engine", "p(Background) = " << lm.eval( "background", 1.0 ) );
	}



	return 0;
}
