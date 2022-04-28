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
#ifndef __STARTCAPTURE_H
#define __STARTCAPTURE_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
class Distribution ;

/** declarations **/
class StartCapture: public Atomic
{
public:
	StartCapture( const string &name = "StartCapture" ) ;	 // Default constructor

	~StartCapture();					// Destructor

	virtual string className() const
		{return "StartCapture";}

protected:
	Model &initFunction();

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	Port &cmd_in;
	const Port &channel_done;
	Port &capture_started, &channel_go;
	int wait_for_cmd, set_channel, process_cmd;

	Distribution *dist;
	Distribution &distribution()
				{return *dist;}
	};	// class


	#endif    //__STARTCAPTURE_H
