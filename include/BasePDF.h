#ifndef BASE_PDF_H
#define BASE_PDF_H

#include "IObject.h"
#include "XmlConfig.h"
using namespace jdb;

#include <string>
using namespace std;

class BasePDF : public IObject
{
public:
	virtual const char* classname() const { return "BasePDF"; }
	BasePDF() {}
	~BasePDF() {}

	virtual void load( XmlConfig &cfg, string nodePath ) = 0;
	virtual string getName()= 0;
	virtual double eval( double _x )= 0;
	virtual double integral(double _min = 0, double _max = -10000 )= 0;
	virtual string toString()= 0;
	
};


#endif