#pragma once
#include "WMIValue.h"

#ifndef WMI_INSTANCE_H_
#define WMI_INSTANCE_H_

using namespace System;
using namespace System::Collections::Generic;

namespace JCK
{
	namespace WMI
	{
		public ref class WMInstance
		{
		public:
			WMInstance(String^ xmlSource);
			virtual ~WMInstance();

			property String^						WMIClass				{ String^ get(); }
			property IList<WMIValue^>^	Values					{ IList<WMIValue^>^ get();	}		
			property String^						Locale					{ String^ get();						}
			property String^						Provider					{ String^ get();						}			
			property Guid							UUID						{ Guid get();							}			
			property WMIValue^				default[String^]		{ WMIValue^ get(String^ name); }

		private:
			IList<WMIValue^>^					m_values;
			SortedDictionary<String^, int>^	m_sortTree;
			String^										m_wmiClass;
			String^										m_locale;
			String^										m_wmiProvider;
			Guid											m_uuid;

		protected:
			virtual void ReadXml(String^ xmlSource);
		};
	}
}
#endif