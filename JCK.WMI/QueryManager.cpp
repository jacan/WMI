#include "stdafx.h"
#include "QueryManager.h"
#include "WMInstance.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Net;
using namespace System::Management;

namespace JCK
{
	namespace WMI
	{
		/******************************************************************************************************************************************************/
		/* Constructor/Destructor
		/******************************************************************************************************************************************************/
		QueryManager::QueryManager()
		{			
			m_machineTargets = gcnew List<MachineTarget^>();
		}

		QueryManager::~QueryManager()
		{
			m_machineTargets->Clear();
		
			delete m_machineTargets;
		}
		/******************************************************************************************************************************************************/
		/* Add Target Machines
		/******************************************************************************************************************************************************/
		void QueryManager::AddTarget(MachineTarget^ targetMachine) 
		{
			MachineTargets->Add(targetMachine);
		}
		
		void QueryManager::AddTargetRange(array<MachineTarget^>^ targetList)
		{
			for(int i=0; i<targetList->Length; i++)
				MachineTargets->Add( targetList[i] );
		}
		
		/******************************************************************************************************************************************************/
		/* Remove Target Machines
		/******************************************************************************************************************************************************/
		bool QueryManager::RemoveTarget(String^ machineName)
		{
			bool itemRemoved = false;

			for(int i=0; i<MachineTargets->Count && !itemRemoved; i++)
			{
				if(MachineTargets[i]->Hostname->ToLower()->Equals(machineName))
				{
					MachineTargets->RemoveAt(i);
					
					itemRemoved = true;
				}
			}

			return itemRemoved;
		}

		bool QueryManager::RemoveTarget(IPAddress ^address)
		{
			bool itemRemoved = false;

			for(int i=0; i<MachineTargets->Count && !itemRemoved; i++)
			{
				if(MachineTargets[i]->Address->Equals(address))
				{
					MachineTargets->RemoveAt(i);
					
					itemRemoved = true;
				}
			}

			return itemRemoved;
		}
		/******************************************************************************************************************************************************/
		/* Query Machines
		/******************************************************************************************************************************************************/
		IList<WMIResultSet^>^ QueryManager::QueryAll()
		{
			return ExecuteQueryObjects();
		}
		
		IList<WMIResultSet^>^ QueryManager::ExecuteQueryObjects()
		{	
			IList<WMIResultSet^>^ resultSet = gcnew List<WMIResultSet^>();
			
			for(int i=0; i<MachineTargets->Count ; i++)
			{
				IList<WMInstance^>^ instance_results = MachineTargets[i]->Query->Execute();

				WMIResultSet^ machineresult = gcnew WMIResultSet();
				machineresult->AddResultSet( instance_results );
				machineresult->MachineName = MachineTargets[i]->Hostname;
				
				resultSet->Add(machineresult);

				/*for each(WMInstance^ wi in instance_results)
					delete wi;
			
				instance_results->Clear();

				delete instance_results; */
			}

			return resultSet;
		}
		
		/******************************************************************************************************************************************************/
		/* Add WQL query to all target Machines
		/******************************************************************************************************************************************************/
		void QueryManager::AddBroadcastQuery(String^ wqlQuery)
		{
			for(int i=0; i<MachineTargets->Count; i++)
			{
				MachineTarget^ target = MachineTargets[i];

				MachineTargets[i]->Query->AddQuery(wqlQuery);			
			}
		}
		/******************************************************************************************************************************************************/
		/* Property implementation
		/******************************************************************************************************************************************************/		
		IList<MachineTarget^>^ QueryManager::MachineTargets::get()
		{
			return m_machineTargets;
		}				
	}
}