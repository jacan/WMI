// This is the main DLL file.

#include "stdafx.h"
#include <stdlib.h>
#include "MachineTarget.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Management;
using namespace System::Diagnostics;

namespace JCK
{
	namespace WMI
	{
		/******************************************************************************************************************************************************/
		/* Constructor / Destructor
		/******************************************************************************************************************************************************/
		MachineTarget::MachineTarget(IPAddress ^addres, String ^ username , String ^ password)
		{
			Address = addres;

			IPHostEntry^ hostEntry = Dns::GetHostEntry( addres );
			this->Hostname		= hostEntry->HostName;

			InitializeMachineTarget(username, password);
		}
		
		MachineTarget::MachineTarget(String ^hostname, String ^username, String ^password)
		{
			Hostname = hostname;
		
			IPHostEntry^ hostEntry = Dns::GetHostEntry(hostname);
			this->Address			= hostEntry->AddressList[0];					

			InitializeMachineTarget(username, password);		
		}

		MachineTarget::~MachineTarget() {
			delete this->m_pConOptions;
			delete this->m_query;
		}
		
		void MachineTarget::InitializeMachineTarget(String^ username, String^ password)
		{
			// Create Query
			m_query = gcnew WMIQuery();
			// Create Connection
			// Authority is not set to ntdm:<domain>
			// this causes the WMIManagementScope->Connect
			// to fails
			// If the local machine is targeted no connection options
			// are required and they will fail is set.
			// Get Local Address		
			IPAddress^ localAddress = Dns::GetHostEntry( Dns::GetHostName() )->AddressList[0];
			
			if(!Address->Equals(localAddress))
			{
				// Store info 
				// security login info
				
				Username = username;
				Password = password;

				m_pConOptions = gcnew ConnectionOptions();

				m_pConOptions->Username = username;
				m_pConOptions->Password = password;

				m_query->ChangeConnectionOptions(m_pConOptions);
			}

			// always use address
			m_query->PathToManage = "\\\\"+Address->ToString()+"\\root\\cimv2";						
		}

		WMIQuery^ MachineTarget::Query::get()
		{
			return m_query;
		}		
	}
}