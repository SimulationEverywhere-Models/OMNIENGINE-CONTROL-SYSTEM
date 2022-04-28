/********************************************************************
*																	*
*      				 Auto Generated File                            *
*                     												*
*********************************************************************/

/** include files **/
#include "CreateFilter.h"           // base header
#include "message.h"       // InternalMessage ....
#include "distri.h"        // class Distribution
#include "mainsimu.h"      // class MainSimulator
#include <math.h>            // fabs( ... )
#include <stdlib.h>
#include "randlib.h"         // Random numbers library
#include "strutil.h"       // str2float( ... )


/*******************************************************************
* Function Name: CreateFilter
* Description: constructor
********************************************************************/
CreateFilter::CreateFilter( const string &name )
: Atomic( name )
, filter_go( addInputPort( "filter_go" ) )
, filter_done( addOutputPort( "filter_done" ) )
, filter_out( addOutputPort( "filter_out" ) )
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
Model &CreateFilter::initFunction()
{
	start_create = 1;
	finish_create = 0;

 	this->passivate();
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: This method executes when an external event is received.
********************************************************************/
Model &CreateFilter::externalFunction( const ExternalMessage &msg )
{
	if (this->state() == passive)
	{
		if (msg.port() == filter_go && start_create)
		{
			if (msg.value() == 1)
			{
				start_create = 0;
				finish_create = 1;
				filter_code = ((double)rand()/(double)RAND_MAX ) * 10;
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
Model &CreateFilter::internalFunction( const InternalMessage & )
{
	//TODO: implement the internal function here

	if (finish_create == 1)
	{
		finish_create = 0;
		start_create = 1;
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
Model &CreateFilter::outputFunction( const InternalMessage &msg )
{
	//TODO: implement the output function here
	// remember you can use sendOutput(time, outputPort, value) function.
	// sendOutput( msg.time(), out, 1) ;

	if (finish_create == 1)
	{
		sendOutput( msg.time(), filter_done, 1  );
		sendOutput( msg.time(), filter_out, filter_code );
	}

	return *this;

}

CreateFilter::~CreateFilter()
{
	//TODO: add destruction code here. Free distribution memory, etc.

	delete dist;
}
