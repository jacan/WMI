#pragma once
#include "stdafx.h"
#include "WMInstance.h"

using namespace System;
using namespace System::Collections::Generic;

#ifndef WMIRESULTSET_H_
#define WMIRESULTSET_H_
namespace JCK
{
	namespace WMI
	{
		public ref class WMIResultSet
		{
		
		public:
			WMIResultSet(void);
			virtual ~WMIResultSet(void);

			property IList<WMInstance^>^	ResultSets		{ IList<WMInstance^>^ get(); }
			property String^							MachineName{ String^ get() { return m_machineName; }  void set(String^ value) { m_machineName = value; }}

		internal:
			void AddResultSet(IList<WMInstance^>^ resultSet);
			
		private:
			IList<WMInstance^>^		m_resultSet;
			String^								m_machineName;
		};
	}
}
#endif WMIRESULTSET_H_

