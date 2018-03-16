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

		enum class ENodeOutputs
		{
			Success = 0, 
			Warning, 
			Error
		};

		};
	}
}
