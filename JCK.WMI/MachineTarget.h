// MachineTarget.h
#pragma once
#include "WMIQuery.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Net;
using namespace System::Management;

#ifndef MACHINETARGET_H_
#define MACHINETARGET_H_

namespace JCK
{
	namespace WMI
	{	

		public ref class MachineTarget
		{		
		public:
			MachineTarget(IPAddress ^ addres , String ^ username, String ^ password);
			MachineTarget(String ^ hostname, String ^ username, String ^ password);
			
			virtual ~MachineTarget();

			property	String							^ Hostname;
			property    IPAddress						^ Address;
			property	String							^ Username;
			property	String							^ Password;
			property WMIQuery						^ Query				{ WMIQuery^			get(); }
			
		protected:			
			void InitializeMachineTarget(String^ username, String^ password);		

		private:
			ConnectionOptions^	m_pConOptions;
			WMIQuery^				m_query;
		
		internal:
			event EventHandler^ MachineDataReady;
		};
	}
}
#endif