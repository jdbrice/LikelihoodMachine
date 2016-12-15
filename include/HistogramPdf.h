#ifndef HISTOGRAM_PDF_H
#define HISTOGRAM_PDF_H


// RooBarb

#include "XmlHistogram.h"
using namespace jdb;

// ROOT
#include "TF1.h"

// STL
#include <string>
#include <limits>
using namespace std;

#include "BasePDF.h"


class HistogramPDF : public BasePDF
{
public:
	HistogramPDF() {}
	~HistogramPDF() {}
	HistogramPDF( XmlConfig &cfg, string nodePath ) {
		load( cfg, nodePath );
	}

	virtual void load( XmlConfig &cfg, string nodePath ) {

		name = cfg.getString( nodePath + ":name", "HistogramPDF" );

		if ( cfg.exists( nodePath + ":url" ) ){ // XmlFunction
			xHisto.load( cfg, nodePath );
		}

		normalization = integral();
		INFO( classname(), "[" << name << "]Function normalization in (  ) = " << normalization );

	}
	
	virtual string getName(){
		return name;
	}

	virtual double eval( double _x ){
		shared_ptr<TH1> h1 = xHisto.getTH1();
		if ( nullptr != h1 ){
			int b = h1->GetXaxis()->FindBin( _x );

			return h1->GetBinContent( b ) / normalization;
		}
		return std::numeric_limits<double>::quiet_NaN();	
	}

	virtual double integral(double _min = 0, double _max = -10000 ) {
		shared_ptr<TH1> h1 = xHisto.getTH1();
		if ( nullptr != h1 )
			return h1->Integral();
		return std::numeric_limits<double>::quiet_NaN();
	}

	virtual string toString(){
		return xHisto.toString();
	}


protected:
	string name;

	// backer
	XmlHistogram xHisto;
	double normalization;
	
};


#endif