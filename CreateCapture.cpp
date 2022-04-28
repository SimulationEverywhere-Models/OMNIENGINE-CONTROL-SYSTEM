/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*
*********************************************************************/

/** include files **/
#include "CreateCapture.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include <math.h>            // fabs( ... )
#include <stdlib.h>
#include "randlib.h"         // Random numbers library
#include "strutil.h"       // str2float( ... )

/*******************************************************************
* Function Name: CreateCapture
* Description: constructor
********************************************************************/
CreateCapture::CreateCapture( const string &name )
: Atomic( name )
, cmd_in( addInputPort( "cmd_in"))
, filter_done( addInputPort( "filter_done" ) )
, filter_go( addOutputPort( "filter_go" ) )
, capture_created( addOutputPort( "capture_created" ) )
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
Model &CreateCapture::initFunction()
{
	wait_for_cmd = 1;
	create_filter = 0;
	process_cmd = 0;

	this->passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &CreateCapture::externalFunction( const ExternalMessage &msg )
{
	if (this->state() == passive)
	{
		if (msg.port() == cmd_in && wait_for_cmd)
		{
			if (msg.value() == 1)
			{
				wait_for_cmd = 0;
				create_filter = 1;
				holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
			}
		}
		else if (msg.port() == filter_done && create_filter)
		{
			create_filter = 0;
			process_cmd = 1;
			holdIn( active, Time( static_cast<float>( fabs( distribution().get() ) ) ) ) ;
		}

	}

}

/*******************************************************************
* Function Name: internalFunction
* Description: This method executes when the TA has expired, right after the outputFunction has finished.
* 			   The new state and TA should be set.
********************************************************************/
Model &CreateCapture::internalFunction( const InternalMessage & )
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
Model &CreateCapture::outputFunction( const InternalMessage &msg )
{
	//TODO: implement the output function here
	// remember you can use sendOutput(time, outputPort, value) function.
	// sendOutput( msg.time(), out, 1) ;

	if (create_filter == 1)
	{
		sendOutput( msg.time(), filter_go, 1  );
	}
	if (process_cmd == 1)
	{
		sendOutput( msg.time(), capture_created, 1 );
	}

	return *this;

}

CreateCapture::~CreateCapture()
{
	delete dist;
}
