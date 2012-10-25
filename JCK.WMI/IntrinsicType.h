#pragma once

using namespace System;

namespace JCK
{
	namespace WMI
	{
		public enum class IntrinsicType
		{
			boolean = 1,
  			char16 = 2,
			DATETIME = 3,
			object  =4,
			real32=5,
			real64=6,
			sint64 =7,
			sint32 =8,
			sint16=9,
			sint8=10,
			uint64=11,
			uint32=12,
			uint16=13,
			uint8=14,
			ArrayOf=15,
			string = 16
		};
	}
}