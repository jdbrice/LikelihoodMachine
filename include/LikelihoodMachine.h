#ifndef LIKELIHOOD_MACHINE_H
#define LIKELIHOOD_MACHINE_H

#include "GenericPDF.h"



class LikelihoodMachine : public IObject
{
public:
	virtual const char* classname() const { return "LikelihoodMachine"; }
	LikelihoodMachine() {}
	~LikelihoodMachine() {}

	void load( XmlConfig &cfg, string nodePath ){
		name = cfg.getString( nodePath + ":name", "LikelihoodMachine" );
		weight = cfg.getDouble( nodePath + ":weight", 1.0 );

		vector<string> paths = cfg.childrenOf( nodePath, "GenericPDF" );
		INFO( classname(), "Found " << paths.size() << plural( paths.size(), " PDF", " PDFs" ) );
		for ( string path : paths ){
			shared_ptr<GenericPDF> gpdf = shared_ptr<GenericPDF>( new GenericPDF( cfg, path ) );
			add( gpdf );
		}

	}

	void add( shared_ptr<GenericPDF> _pdf ){
		pdfs.push_back( _pdf );
		pdfByName[ _pdf->getName() ] = _pdf;
	}

	shared_ptr<GenericPDF> get( string _name ){
		if ( pdfByName.count( _name ) > 0 ){
			return pdfByName[ _name ];
		}
		return nullptr;
	}

	double eval( string _name, double _x ) {
		// loop through eval on each, normalize
		double _p = pdfByName[ _name ]->eval( _x );

		// now get norm factor
		double total = 0.0;
		for ( shared_ptr<GenericPDF> pdf : pdfs ){
			total += pdf->eval( _x );
		}

		return _p / total * weight;
	}

	string toString() {
		string str = "";

		str += "LikelihoodMachine( name=" + quote( name );
		for ( shared_ptr<GenericPDF> pdf : pdfs ){
			str += "\n GenericPDF( " + pdf->toString() + " )";
		}
		str += " ) \n";
		return str;
	}

protected:
	
	vector< shared_ptr<GenericPDF>> pdfs;
	map< string, shared_ptr<GenericPDF> > pdfByName;
	string name;
	double weight;

};



#endif