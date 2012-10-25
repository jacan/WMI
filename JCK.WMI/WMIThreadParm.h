#pragma once
#include "stdafx.h"

using namespace System;
using namespace System::Collections::Generic;


namespace Freeway
{
	namespace WMI
	{
		ref class WMIThreadParm
		{
		internal:
			// ctor/dtor
			WMIThreadParm(bool loop, array<String^>^ queryList);
			virtual ~WMIThreadParm();
		
			// Data used by the WQL Query Thread
			property array<String^>^	QueryList  { array<String^>^ get();  };
			property bool						Loop;

		protected:
			array<String^>^ m_queryList;
		};
	}
}