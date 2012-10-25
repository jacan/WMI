#include "StdAfx.h"
#include "WMIResultSet.h"
#include "WMInstance.h"

using namespace System;
using namespace System::Collections::Generic;


namespace JCK
{
	namespace WMI
	{
		WMIResultSet::WMIResultSet(void)
		{
			m_machineName = L"";
		}

		WMIResultSet::~WMIResultSet(void)
		{
			delete m_resultSet;
			delete m_machineName;
		}

		void WMIResultSet::AddResultSet(IList<WMInstance^>^ resultSet)
		{
			this->m_resultSet = resultSet;
		}

		IList<WMInstance^>^ WMIResultSet::ResultSets::get()
		{
			return m_resultSet;
		}
	}
}
