#include "stdafx.h"
#include "MachineTarget.h"
#include "WMInstance.h"
#include "WMIResultSet.h"

using namespace System;
using namespace System::Net;
using namespace System::Collections::Generic;
using namespace System::Management;

#ifndef QUERYMANAGER_H_
#define QUERYMANAGER_H_

namespace JCK {
	namespace WMI {
	
		public ref class QueryManager
		{
		public:
			// ctor/dtor
			QueryManager();
			virtual ~QueryManager();

			// public methods to edit the machine collection. The machine collection is typically the list of
			// servers you wish to wql query 
			void AddTarget(MachineTarget^ targetMachine);
			void AddTargetRange(array<MachineTarget^>^ targetList);
			
			bool RemoveTarget(String^ machineName);
			bool RemoveTarget(IPAddress^ address);			

			// Query All Targets.
			// This method is used to query all machines
			// at once
			IList<WMIResultSet^>^ QueryAll();	
			
			// Add WQL Query To all machine targets
			void AddBroadcastQuery(String^ wqlQuery);
		
			// Available list of targets that can be queried.
			// Gives the possibility to query single machines
			property IList<MachineTarget^>^			MachineTargets		{ IList<MachineTarget^>^ get(); };			
				
		private:
			IList<MachineTarget^>^						m_machineTargets;
			// Local machine info
			
		protected:
			IList<WMIResultSet^>^ ExecuteQueryObjects();


		};
	}
}
#endif