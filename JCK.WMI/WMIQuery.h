#pragma once

#include "WMInstance.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Management;
using namespace System::Threading;

#ifndef WMIQUERY_H_
#define WMIQUERY_H_

namespace JCK
{
	namespace WMI
	{		
		public ref class WMIQuery
		{
			public:
				// ctor/dtor
				WMIQuery();
				virtual ~WMIQuery();
			
				// It's possible to get information about
				// a single WQL Query object
				// and edit it.
				void									AddQuery(String^ query);
				void									ClearQueries();			
				array<String^>^ 				GetQueryList();			
				IList<WMInstance^>^		Execute();

				// Internal methods are used by MachineTarget wich 
				// implements public acces to a single query object
			internal: 
				void											ChangeConnectionOptions(ConnectionOptions^ value );
				property String^							PathToManage																		{	String^ get();	void set(String^ value);	}							
				
		private:
							
			protected:			
				// Thread method
				IList<WMInstance^>^		ExecuteQuery();
				// Data-members
				String^								m_strManagementPath;				
				ConnectionOptions^			m_wmiConOptions;				
				IList<String^>^					m_queryList;
				IDictionary<String^, int>^	m_paramsDictionary;				
		};
	}
}
#endif
