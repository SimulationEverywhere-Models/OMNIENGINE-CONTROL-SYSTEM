/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "queue.h"                // class Queue
#include "generat.h"             // class Generator
#include "cpu.h"                 // class CPU
#include "transduc.h"             // class Transducer
#include "trafico.h"              // class Trafico
#include "WirelessChannel.h"      // class WirelessChannel
#include "StartCapture.h"       // class StartCapture
#include "StopCapture.h"        // class StopCapture
#include "CreateFilter.h"       // class CreateFilter
#include "CreateCapture.h"      // class CreateCapture


void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<WirelessChannel>() , "WirelessChannel" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<StartCapture>() , "StartCapture" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<StopCapture>() , "StopCapture" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CreateFilter>() , "CreateFilter" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CreateCapture>() , "CreateCapture" ) ;
}
