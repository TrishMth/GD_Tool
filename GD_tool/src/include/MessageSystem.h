#pragma once
#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
#include <string>
#pragma endregion 

namespace GD_Tool
{
	namespace Mainframework
	{
		static std::string Log(std::string str);
		static std::string Warning(std::string str); 
		static std::string Error(std::string str); 
	}
}