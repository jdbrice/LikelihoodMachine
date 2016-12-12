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
	}
	
	string getName(){
		return name;
	}

	double eval( double _x ){
		if ( this->type == PdfType::Function ){
			return xfunc.eval(_x);
		}
		return std::numeric_limits<double>::quiet_NaN();
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
	enum class PdfType { Histogram, Function };
	PdfType type;
	
};


#endif