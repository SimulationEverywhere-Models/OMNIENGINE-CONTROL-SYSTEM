/*******************************************************************
*
*  DESCRIPTION: Atomic Model Start Capture
*
*  AUTHOR: Waqas Muhi
*
*
*  DATE: 29/10/2011
*
*******************************************************************/
#ifndef __STOPCAPTURE_H
#define __STOPCAPTURE_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
class Distribution ;

/** declarations **/
class StopCapture: public Atomic
{
public:
	StopCapture( const string &name = "StopCapture" ) ;	 // Default constructor

	~StopCapture();					// Destructor

	virtual string className() const
		{return "StopCapture";}

protected:
	Model &initFunction();

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	Port &cmd_in;
	Port &capture_stopped;
	int wait_for_cmd, process_cmd;

	Distribution *dist;
	Distribution &distribution()
				{return *dist;}
	};	// class


	#endif    //__STOPCAPTURE_H
