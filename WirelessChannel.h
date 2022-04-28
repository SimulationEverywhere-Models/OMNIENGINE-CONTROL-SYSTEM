/*******************************************************************
*
*  DESCRIPTION: Atomic Model Wireless Channel
*
*  AUTHOR: Waqas Muhi
*
*
*  DATE: 29/10/2011
*
*******************************************************************/
#ifndef __WIRELESSCHANNEL_H
#define __WIRELESSCHANNEL_H

/** include files **/
#include "atomic.h"  // class Atomic

/** forward declarations **/
class Distribution ;

/** declarations **/
class WirelessChannel: public Atomic
{
public:
	WirelessChannel( const string &name = "WirelessChannel" ) ;	 // Default constructor

	~WirelessChannel();					// Destructor

	virtual string className() const
		{return "WirelessChannel";}

protected:
	Model &initFunction();

	Model &externalFunction( const ExternalMessage & );

	Model &internalFunction( const InternalMessage & );

	Model &outputFunction( const InternalMessage & );

private:
	Port &channel_go;
	Port &channel_done;
	Port &channel_out;
	int start_set, finish_set;
	double channel, frequency;

	Distribution *dist;
	Distribution &distribution()
				{return *dist;}
	};	// class WirelessChannel


	#endif    //__WIRELESSCHANNEL_H
