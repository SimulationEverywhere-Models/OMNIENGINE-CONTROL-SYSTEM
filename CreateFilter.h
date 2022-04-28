/*******************************************************************
*
*  DESCRIPTION: Atomic Model Create Filter
*
*  AUTHOR: Waqas Muhi
*
*
*  DATE: 29/10/2011
*
*******************************************************************/
#ifndef __CREATEFILTER_H
#define __CREATEFILTER_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
class Distribution ;

/** declarations **/
class CreateFilter: public Atomic
{
public:
	CreateFilter( const string &name = "CreateFilter" ) ;	 // Default constructor

	~CreateFilter();					// Destructor

	virtual string className() const
		{return "CreateFilter";}

protected:
	Model &initFunction();

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	Port &filter_go;
	Port &filter_done;
	Port &filter_out;
	int start_create, finish_create;
	double filter_code;

	Distribution *dist;
	Distribution &distribution()
				{return *dist;}
	};	// class CreateFilter


	#endif    //__CREATEFILTER_H
