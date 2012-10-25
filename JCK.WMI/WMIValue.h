#pragma once

#ifndef WMIVALUE_H_
#define WMIVALUE_H_

#include "stdafx.h"
#include "IntrinsicType.h"

using namespace System;
using namespace System::Xml;

namespace JCK
{
	namespace WMI
	{
		public ref class WMIValue
		{
		public:
			WMIValue(XmlNode^ propertyNode);
			virtual ~WMIValue();

			property String^				Name		{ String^ get();				}		
			property String^				Value		{ String^ get();				}				
			property IntrinsicType^	Type			{ IntrinsicType^ get();	}

		private:
			String^				m_value;
			String^				m_name;
			IntrinsicType^	m_type;

		protected:
			virtual void ReadXml(XmlNode^ propertyNode);

		};
	}
}
#endif