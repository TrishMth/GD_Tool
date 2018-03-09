#include "include\MessageSystem.h"


void GD_Tool::Mainframework::MessageSystem::Log(std::string classOfTheMsg, std::string headingOfMsg, std::string definitionOfMsg)
{
	std::string message = classOfTheMsg + ":" + headingOfMsg + "\n" + definitionOfMsg;
}

void GD_Tool::Mainframework::MessageSystem::Warning(std::string classOfTheMsg, std::string headingOfMsg, std::string definitionOfMsg)
{
	std::string message = classOfTheMsg + ":" + headingOfMsg + "\n" + definitionOfMsg;
}

void GD_Tool::Mainframework::MessageSystem::Error(std::string classOfTheMsg, std::string headingOfMsg, std::string definitionOfMsg)
{
	std::string message = classOfTheMsg + ":" + headingOfMsg + "\n" + definitionOfMsg;
}
