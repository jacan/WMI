#include "stdafx.h"
#include "WMIQuery.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace System::Management;


namespace JCK
{
	namespace WMI
	{
		/******************************************************************************************************************************************************/
		/* Constructor/Destructor
		/******************************************************************************************************************************************************/
		WMIQuery::WMIQuery()
		{			
			m_queryList						= gcnew List<String^>();	
			m_strManagementPath		= String::Empty;
			m_wmiConOptions				= nullptr;
		}
		
		WMIQuery::~WMIQuery()
		{					
			delete m_queryList;			
			delete m_strManagementPath;
			delete m_wmiConOptions;
		}		
		/******************************************************************************************************************************************************/
		/* Add Query
		/******************************************************************************************************************************************************/
		void WMIQuery::AddQuery(String^ query)
		{
			if(m_queryList == nullptr)
				m_queryList = gcnew List<String^>();

			m_queryList->Add(query);					
		}
		/******************************************************************************************************************************************************/
		/* Clear Query List
		/******************************************************************************************************************************************************/
		void WMIQuery::ClearQueries()
		{			
			m_queryList->Clear();
		}		
		/******************************************************************************************************************************************************/
		/*  Get WMI Query List
		/******************************************************************************************************************************************************/
		array<String^>^  WMIQuery::GetQueryList()
		{
			array<String^>^ list = gcnew array<String^>(m_queryList->Count);

			m_queryList->CopyTo(list, 0);

			return list;
		}
		/******************************************************************************************************************************************************/
		/* Change Connection options
		/******************************************************************************************************************************************************/
		void WMIQuery::ChangeConnectionOptions(ConnectionOptions^ value)
		{
			m_wmiConOptions = value;
			m_wmiConOptions->Authentication = AuthenticationLevel::Default;
			m_wmiConOptions->Impersonation = ImpersonationLevel::Impersonate;			
		}		
		/******************************************************************************************************************************************************/
		/* Properties
		/******************************************************************************************************************************************************/
		String^ WMIQuery::PathToManage::get()
		{
			return m_strManagementPath;
		}

		void WMIQuery::PathToManage::set(String^ value)
		{
			m_strManagementPath = value;
		}
		/******************************************************************************************************************************************************/
		/* Execute Query
		/******************************************************************************************************************************************************/
		IList<WMInstance^>^ WMIQuery::Execute()
		{
			return ExecuteQuery();
		}
		/******************************************************************************************************************************************************/
		/* WMI execution
		/******************************************************************************************************************************************************/		
		IList<WMInstance^>^ WMIQuery::ExecuteQuery()
		{
			WqlObjectQuery						^ wmi_cmd;
			ManagementObjectSearcher	^ search;
			ManagementScope					^ scope;
			IList<WMInstance^>^			result;
			

			try
			{
			// Create Query instance
			wmi_cmd	= gcnew WqlObjectQuery();

			// Set management scope
			// Through machine name \root\cimv2 and connection options
			
			scope = m_wmiConOptions != nullptr ? gcnew ManagementScope( m_strManagementPath, m_wmiConOptions) : gcnew ManagementScope( m_strManagementPath);
			
			// Connect to machine WMI 
			scope->Connect();

			// Create instance that searches for desired query items
			search		= gcnew ManagementObjectSearcher(scope, wmi_cmd);		

			// Create result array
			result = gcnew List<WMInstance^>();			
			

			}
			// If some error occurs
			// Typically this would be
			// on scope->Connect
			catch(ManagementException^ xWMI)
			{
				throw xWMI;
			}
			// Unexpected
			catch(Exception^) {
				// HRESULT ERROR!
				// No data available.
				// returning empty set

				return result;
			}

			// Run through each query
			for(int i=0; i<m_queryList->Count   ; i++)
			{
				try
				{			
					// setup object searcher
					wmi_cmd->QueryString = m_queryList[i];
					search->Query = wmi_cmd;

					// Search
					ManagementObjectCollection^ wmi_result= search->Get();

					// Any objects available
					if(wmi_result->Count > 0) {	
						for each( ManagementObject^ wmi_obj in wmi_result)
							result->Add( gcnew WMInstance(wmi_obj->GetText( TextFormat::CimDtd20))  );						
					}
				}
				catch(InvalidOperationException^) {} // occurs when Machine cannot be queried
				catch(Exception^) { /* Do not stop querying... (Analyse log)*/ }			
			}
			
			delete scope;						
			delete search;
			delete wmi_cmd;

			return result;
		}
	}
}