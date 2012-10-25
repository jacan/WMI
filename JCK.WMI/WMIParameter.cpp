#include "stdafx.h"
#include "WMIParameter.h"

using namespace System;

namespace Freeway
{
	namespace WMI
	{
		/******************************************************************************************************************************************************/
		/* ctor/dtor
		/******************************************************************************************************************************************************/
		WMIParameter::WMIParameter(String^ name)
		{
			m_paramName	=name;
			m_value			= String::Empty;
		}

		WMIParameter::~WMIParameter()
		{
			delete m_value;
		}
		/******************************************************************************************************************************************************/
		/* Internally change parameter value
		/******************************************************************************************************************************************************/
		void WMIParameter::SetValue(Object^ val)
		{
			m_value = val->ToString();
		}
		/******************************************************************************************************************************************************/
		/* Property implementation
		/******************************************************************************************************************************************************/
		String^ WMIParameter::Value::get()
		{
			return m_value;
		}

		String^ WMIParameter::ParameterName::get()
		{
			return m_paramName;
		}
	}
}