#ifndef GENERIC_PDF_H
#define GENERIC_PDF_H

// RooBarb
#include "IObject.h"
#include "XmlConfig.h"
#include "XmlFunction.h"
using namespace jdb;

// ROOT
#include "TF1.h"
#include "TH1.h"

// STL
#include <string>
#include <limits>
using namespace std;

class GenericPDF : public IObject
{
public:
	virtual const char* classname() const { return "GenericPDF"; }
	GenericPDF() {}
	GenericPDF( XmlConfig &cfg, string nodePath ) {
		load( cfg, nodePath );
	}
	~GenericPDF() {}

	virtual void load( XmlConfig &cfg, string nodePath ) {

		name = cfg.getString( nodePath + ":name", "GenericPDF" );
		cfg.set( nodePath + ":name", "" );	// remove name so that TF1 uses some unique gerneated name

		if ( cfg.exists( nodePath + ":formula" ) ){ // XmlFunction
			xfunc.set( cfg, nodePath );
			this->type = PdfType::Function;
		} else if ( cfg.exists( nodePath + ":url" ) ){ // XmlHisto
			this->type = PdfType::Histogram;
			// TODO: add histo support
		}

		funcNormalization = integral();
		INFO( classname(), "[" << name << "]Function normalization : " << funcNormalization );

	}
	
	string getName(){
		return name;
	}

	double eval( double _x ){
		if ( this->type == PdfType::Function ){
			return xfunc.eval(_x) / funcNormalization;
		}
		return std::numeric_limits<double>::quiet_NaN();
	}

	double integral(double _min = 0, double _max = -10000 ) {
		if ( _max < _min ){
			_min = xfunc.getTF1()->GetXmin();
			_max = xfunc.getTF1()->GetXmax();
		}

		return xfunc.getTF1()->Integral( _min, _max );
	}

	string toString(){
		if ( this->type == PdfType::Function ){
			return xfunc.toString();
		}
		return "";
	}


protected:
	string name;

	// backers
	// shared_ptr<TH1> h = nullptr;
	XmlFunction xfunc;
	double funcNormalization;
	enum class PdfType { Histogram, Function };
	PdfType type;
	
};


#endif