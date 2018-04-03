#pragma once
namespace GD_Tool
{
	namespace Mainframework
	{
		struct GlobalEnums 
		{
		enum class EVariableTypes
		{
			Integer = 0,
			Boolean,
			Float,
			Double,
		};

		enum class ENodeType
		{
			Intern = 0,
			Variable,
			Operator
		};

		enum class EMsgType
		{
			Default,
			Log,
			Warning,
			Error
		};

		enum class ENodeOutputs
		{
			Success = 0, 
			Warning, 
			Error
		};
		enum class EMapSizes
		{
			Size128,
			Size256,
			Size512,
			Size1k,
			Size2k,
			Size4k,
			Size8k,
			Size16k
		};
		};
	}
}
