#ifndef LIKELIHOOD_MACHINE_H
#define LIKELIHOOD_MACHINE_H

#include "FormulaPDF.h"
#include "HistogramPDF.h"



class LikelihoodMachine : public IObject
{
public:
	virtual const char* classname() const { return "LikelihoodMachine"; }
	LikelihoodMachine() {}
	~LikelihoodMachine() {}

	void load( XmlConfig &cfg, string nodePath ){
		name = cfg.getString( nodePath + ":name", "LikelihoodMachine" );
		weight = cfg.getDouble( nodePath + ":weight", 1.0 );

		vector<string> paths = cfg.childrenOf( nodePath, "FormulaPDF" );
		INFO( classname(), "Found " << paths.size() << plural( paths.size(), " FormulaPDF", " FormulaPDFs" ) );
		for ( string path : paths ){
			shared_ptr<BasePDF> gpdf = shared_ptr<BasePDF>( new FormulaPDF( cfg, path ) );
			add( gpdf );
		}

		paths = cfg.childrenOf( nodePath, "HistogramPDF" );
		INFO( classname(), "Found " << paths.size() << plural( paths.size(), " HistogramPDF", " HistogramPDFs" ) );
		for ( string path : paths ){
			shared_ptr<BasePDF> gpdf = shared_ptr<BasePDF>( new HistogramPDF( cfg, path ) );
			add( gpdf );
		}

	}

	void add( shared_ptr<BasePDF> _pdf ){
		pdfs.push_back( _pdf );
		pdfByName[ _pdf->getName() ] = _pdf;
	}

	shared_ptr<BasePDF> get( string _name ){
		if ( pdfByName.count( _name ) > 0 ){
			return pdfByName[ _name ];
		}
		return nullptr;
	}

	double eval( string _name, double _x ) {
		// loop through eval on each, normalize
		if ( pdfByName.count( _name ) <= 0 ) {
			ERROR( classname(), "PDF<name=" << name << "> DNE" );
			return std::numeric_limits<double>::quiet_NaN();
		}

		double _p = pdfByName[ _name ]->eval( _x );

		// now get norm factor
		double total = 0.0;
		int N = 0;
		for ( shared_ptr<BasePDF> pdf : pdfs ){
			total += pdf->eval( _x );
			N++;
		}

		if ( N > 1 ){
			return _p / total * weight;
		} else {
			return 0;
		}
		
	}

	string toString() {
		string str = "";

		str += "LikelihoodMachine( name=" + quote( name );
		for ( shared_ptr<BasePDF> pdf : pdfs ){
			str += "\n BasePDF( " + pdf->toString() + " )";
		}
		str += " ) \n";
		return str;
	}

protected:
	
	vector< shared_ptr<BasePDF>> pdfs;
	map< string, shared_ptr<BasePDF> > pdfByName;
	string name;
	double weight;

};



#endif