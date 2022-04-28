/*******************************************************************
*
*  DESCRIPTION: Atomic Model Create Capture
*
*  AUTHOR: Waqas Muhi
*
*
*  DATE: 29/10/2011
*
*******************************************************************/
#ifndef __CREATECAPTURE_H
#define __CREATECAPTURE_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
class Distribution ;

/** declarations **/
class CreateCapture: public Atomic
{
public:
	CreateCapture( const string &name = "CreateCapture" ) ;	 // Default constructor

	~CreateCapture();					// Destructor

	virtual string className() const
		{return "CreateCapture";}

protected:
	Model &initFunction();

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	Port &cmd_in;
	const Port &filter_done;
	Port &capture_created, &filter_go;
	int wait_for_cmd, create_filter, process_cmd;

	Distribution *dist;
	Distribution &distribution()
				{return *dist;}
	};	// class


	#endif    //__CREATECAPTURE_H
