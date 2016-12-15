#ifndef FORMULA_PDF_H
#define FORMULA_PDF_H

// RooBarb

#include "XmlFunction.h"
using namespace jdb;

// ROOT
#include "TF1.h"

// STL
#include <string>
#include <limits>
using namespace std;

#include "BasePDF.h"

class FormulaPDF : public BasePDF
{
public:
	virtual const char* classname() const { return "FormulaPDF"; }
	FormulaPDF() {}
	FormulaPDF( XmlConfig &cfg, string nodePath ) {
		load( cfg, nodePath );
	}
	~FormulaPDF() {}

	virtual void load( XmlConfig &cfg, string nodePath ) {

		name = cfg.getString( nodePath + ":name", "FormulaPDF" );
		cfg.set( nodePath + ":name", "" );	// remove name so that TF1 uses some unique gerneated name

		if ( cfg.exists( nodePath + ":formula" ) ){ // XmlFunction
			xfunc.set( cfg, nodePath );
		}

		normalization = integral();
		INFO( classname(), "[" << name << "]Function normalization in ( " << xfunc.getTF1()->GetXmin() << ", " << xfunc.getTF1()->GetXmax() << " ) = " << normalization );

	}
	
	virtual string getName(){
		return name;
	}

	virtual double eval( double _x ){
		return xfunc.eval(_x) / normalization;
	}

	virtual double integral(double _min = 0, double _max = -10000 ) {
		if ( _max < _min ){
			_min = xfunc.getTF1()->GetXmin();
			_max = xfunc.getTF1()->GetXmax();
		}

		return xfunc.getTF1()->Integral( _min, _max );
	}

	virtual string toString(){
		return xfunc.toString();
	}


protected:
	string name;

	// backer
	XmlFunction xfunc;
	double normalization;
	
};


#endif