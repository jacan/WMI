#include "StdAfx.h"
#include "WMInstance.h"
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
		WMInstance::WMInstance(String^ xmlSource)
		{
			m_locale			= String::Empty;
			m_uuid				= System::Guid::Empty;
			m_values			= gcnew List<WMIValue^>();
			m_wmiProvider	= String::Empty;
			m_sortTree		= gcnew SortedDictionary<String^, int>();

			ReadXml(xmlSource);
		}

		WMInstance::~WMInstance(void)
		{
			delete m_locale;
			delete m_uuid;
			
			m_values->Clear();
			m_sortTree->Clear();			
			
			delete m_wmiClass;
			delete m_sortTree;
			delete m_values;
			delete m_wmiProvider;			
		}
		
		/******************************************************************************************************************************************************/
		/* Property implementation
		/******************************************************************************************************************************************************/
		String^ WMInstance::Locale::get()
		{
			return m_locale;
		}
		String^ WMInstance::Provider::get()
		{
			return m_wmiProvider;
		}
		Guid WMInstance::UUID::get()
		{
			return m_uuid;
		}
		IList<WMIValue^>^ WMInstance::Values::get()
		{
			return m_values;
		}
		String^ WMInstance::WMIClass::get()
		{
			return m_wmiClass;
		}
		WMIValue^ WMInstance::default::get(String^ name)
		{
			if(m_sortTree->ContainsKey(name))	
				return m_values[ m_sortTree[name] ];

			return nullptr;
		}

		/******************************************************************************************************************************************************/
		/* Read ManagementObject dcdxml values
		/******************************************************************************************************************************************************/
		void WMInstance::ReadXml(String^ xmlSource)
		{
			XmlDocument^ doc = gcnew XmlDocument();			
			doc->LoadXml(xmlSource);

			XmlNode^			instance_node = doc->SelectSingleNode("/INSTANCE");
			XmlNodeList^		qualifiers         = doc->SelectNodes("/INSTANCE/QUALIFIER");
			XmlNodeList^    properties		  = doc->SelectNodes("/INSTANCE/PROPERTY");
			
			m_wmiClass = instance_node->Attributes["CLASSNAME"]->Value;
	
			String^ attribName = L"";
			String^ value			= L"";

			// Read Qualifiers
			for(int i=0; i<qualifiers->Count; i++)
			{			
				attribName =qualifiers[i]->Attributes["NAME"]->Value;
				XmlNode^ n		 =qualifiers[i]->SelectSingleNode("VALUE");				

				if(attribName->Equals("Locale"))
					m_locale = n->InnerText;

				else if(attribName->Equals("Provider"))
					m_wmiProvider = n->InnerText;

				/*else if(attribName->Equals("UUID"))
					m_uuid = Guid::ValueType((value);				*/
			}

			for(int i=0; i< properties->Count; i++)
			{
				m_values->Add( gcnew WMIValue( properties[i] ) );
				
				int index = m_values->Count -1;

				m_sortTree->Add( m_values[ index ]->Name, index);
			}
					
			delete instance_node;
			delete qualifiers;
			delete properties;

			delete doc;
		}
	}
}
