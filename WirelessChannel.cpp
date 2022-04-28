/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*		
*********************************************************************/

/** include files **/
#include "WirelessChannel.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include <math.h>            // fabs( ... )
#include <stdlib.h>
#include "randlib.h"         // Random numbers library
#include "strutil.h"       // str2float( ... )


/*******************************************************************
* Function Name: WirelessChannel
* Description: constructor
********************************************************************/
WirelessChannel::WirelessChannel( const string &name )
: Atomic( name )
, channel_go( addInputPort( "channel_go" ) )
, channel_done( addOutputPort( "channel_done" ) )
, channel_out( addOutputPort( "channel_out" ) )
{
	try
	{
		dist = Distribution::create( MainSimulator::Instance().getParameter( description(), "distribution" ) );

		MASSERT( dist );

		for ( register int i = 0 ; i < dist->varCount() ; i++ )
		{
			string parameter( MainSimulator::Instance().getParameter( description(), dist->getVar(i) ) ) ;
			dist->setVar( i, str2float( parameter ) ) ;
		}
	} catch( InvalidDistribution &e )
	{
		e.addText( "The model " + description() + " has distribution problems!" ) ;
		e.print(cerr);
		MTHROW( e ) ;
	} catch( MException &e )
	{
		MTHROW( e ) ;
	}
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &WirelessChannel::initFunction()
{
	start_set = 1;
	finish_set = 0;
 	
 	this->passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &WirelessChannel::externalFunction( const ExternalMessage &msg )
{
	if (this->state() == passive)
	{
		if (msg.port() == channel_go && start_set)
		{
			if (msg.value() == 1)
			{
				start_set = 0;
				finish_set = 1;
				channel = ((double)rand()/(double)RAND_MAX ) * 10;
				frequency = ((double)rand()/(double)RAND_MAX ) * 100;
				holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;

			}
		}

	}
	
	return *this ;
}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &WirelessChannel::internalFunction( const InternalMessage & )
{
	//TODO: implement the internal function here

	if (finish_set == 1)
	{
		finish_set = 0;
		start_set = 1;
	}

	// stays in passive state until an external event occurs;
	this->passivate();
	return *this;

}

/*******************************************************************
* Function Name: outputFunction
* Description: This method executes when the TA has expired. After this method the internalFunction is called.
*              Output values can be send through output ports
********************************************************************/
Model &WirelessChannel::outputFunction( const InternalMessage &msg )
{
	//TODO: implement the output function here
	// remember you can use sendOutput(time, outputPort, value) function.
	// sendOutput( msg.time(), out, 1) ;
	
	if (finish_set == 1)
	{
		sendOutput( msg.time(), channel_done, 1  );
		sendOutput( msg.time(), channel_out, (int)channel);
	}

	return *this;

}

WirelessChannel::~WirelessChannel()
{
	//TODO: add destruction code here. Free distribution memory, etc. 

	delete dist;
}
