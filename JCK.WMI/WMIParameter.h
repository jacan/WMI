#pragma once

using namespace System;

namespace Freeway
{
	
	namespace WMI
	{
		public ref class WMIParameter
		{

		internal:
			// Change WMI Parameter value
			// this value can only change -when
			// valid wmi object
			void SetValue(Object^ val);
		
		public:
			// ctor/dtor
			WMIParameter(String^ name);			
			virtual ~WMIParameter();

			// GET properties
			property String^			Value				{ String^ get(); }
			property String^        ParameterName	{ String^ get(); }

		protected:
			// Data Members
			String^		m_value;				
			String^		m_paramName;

		};
	}
}