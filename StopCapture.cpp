/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*
*********************************************************************/

/** include files **/
#include "StopCapture.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include <math.h>            // fabs( ... )
#include <stdlib.h>
#include "randlib.h"         // Random numbers library
#include "strutil.h"       // str2float( ... )


/*******************************************************************
* Function Name: StopCapture
* Description: constructor
********************************************************************/
StopCapture::StopCapture( const string &name )
: Atomic( name )
, cmd_in( addInputPort( "cmd_in" ) )
, capture_stopped( addOutputPort( "capture_stopped" ) )
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
Model &StopCapture::initFunction()
{
	wait_for_cmd = 1;
	process_cmd = 0;

 	this->passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &StopCapture::externalFunction( const ExternalMessage &msg )
{
	if (this->state() == passive)
	{
		if (msg.port() == cmd_in && wait_for_cmd)
		{
			if (msg.value() == 3)
			{
				wait_for_cmd = 0;
				process_cmd = 1;
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
Model &StopCapture::internalFunction( const InternalMessage & )
{
	//TODO: implement the internal function here

	if (process_cmd == 1)
	{
		process_cmd = 0;
		wait_for_cmd = 1;
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
Model &StopCapture::outputFunction( const InternalMessage &msg )
{
	//TODO: implement the output function here
	// remember you can use sendOutput(time, outputPort, value) function.
	// sendOutput( msg.time(), out, 1) ;

	if (process_cmd == 1)
	{
		sendOutput( msg.time(), capture_stopped, 1  );
	}

	return *this;

}

StopCapture::~StopCapture()
{
	//TODO: add destruction code here. Free distribution memory, etc.

	delete dist;
}
