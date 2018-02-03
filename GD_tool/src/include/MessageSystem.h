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
		static void Log(std::string classOfTheMsg, std::string headingOfMsg, std::string definitionOfMsg);
		static void Warning(std::string classOfTheMsg, std::string headingOfMsg, std::string definitionOfMsg);
		static void Error(std::string classOfTheMsg, std::string headingOfMsg, std::string definitionOfMsg);
	}
}