#include <stdafx.h>
#include "WMIThreadParm.h"

using namespace System;
using namespace System::Diagnostics;
using namespace System::Collections::Generic;

namespace Freeway
{
	namespace WMI
	{			
		/******************************************************************************************************************************************************/
		/* ctor/dtor
		/******************************************************************************************************************************************************/
		WMIThreadParm::WMIThreadParm(bool loop, array<String^>^ queryStrings)
		{
			m_queryList = gcnew array<String^>(queryStrings->Length);
				
			queryStrings->CopyTo(m_queryList, 0);
			this->Loop = loop;
			
		}

		WMIThreadParm::~WMIThreadParm()
		{
			Array::Clear( QueryList, 0, QueryList->Length);
		}

		/******************************************************************************************************************************************************/
		/* Property implementation
		/******************************************************************************************************************************************************/
 		array<String^>^ WMIThreadParm::QueryList::get()
		{
			return m_queryList;
		}
	}
}