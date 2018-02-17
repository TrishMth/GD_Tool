#pragma once

enum class EVariableTypes
{
	Integer,
	Boolean,
	Float,
	Double,
};

enum class ENodeType
{
	Intern,
	Variable,
	Operator
};

enum class ENodeOutputs
{
	Success, 
	Warning, 
	Error
};
