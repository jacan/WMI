#include "StdAfx.h"
#include "IntrinsicType.h"
#include "WMIValue.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Xml;

namespace JCK
{
	namespace WMI
	{
		/******************************************************************************************************************************************************/
		/* Constructor/Destructor
		/******************************************************************************************************************************************************/
		WMIValue::WMIValue(XmlNode^ propertyNode)
		{
			m_value = String::Empty;
			m_name = String::Empty;
			ReadXml(propertyNode);
		}

		WMIValue::~WMIValue()
		{
			delete m_value;
			delete m_name;
			delete m_type;
		}
		/******************************************************************************************************************************************************/
		/* Property implementation
		/******************************************************************************************************************************************************/
		String^ WMIValue::Value::get()
		{
			return m_value;
		}		
		String^ WMIValue::Name::get()
		{
			return m_name;
		}
		IntrinsicType^ WMIValue::Type::get()
		{
			return m_type;
		}
		/******************************************************************************************************************************************************/
		/* Read XML (Fills the object with the corresponding WMI PROPERTY VALUES)
		/******************************************************************************************************************************************************/
		void WMIValue::ReadXml(XmlNode^ propertyNode)
		{
			String^ type = propertyNode->Attributes["TYPE"]->Value;
			String^ name = propertyNode->Attributes["NAME"]->Value;

			Object^ wmi_datatype = Enum::Parse( IntrinsicType::typeid  , type, true);
			m_type = dynamic_cast<IntrinsicType^>(wmi_datatype);

			m_name = name;
			XmlNode^ value_node = propertyNode->SelectSingleNode("VALUE");

			if(value_node != nullptr)
				m_value = value_node->InnerText;
		}
	}
}
