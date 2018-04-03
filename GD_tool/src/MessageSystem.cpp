#include "include\MessageSystem.h"


void GD_Tool::Mainframework::MessageSystem::Log(std::string classOfTheMsg, std::string headingOfMsg, std::string definitionOfMsg)
{
	std::string message = "LOG: " + classOfTheMsg + ":" + headingOfMsg + "\n" + definitionOfMsg;
	ImVec4 col(1, 1, 1, 1);
	char* m = new char[256];
	strcpy_s(m, 256, message.c_str());
	BaseGUI::GetInstance().AddLogToConsole(m, col);
}

void GD_Tool::Mainframework::MessageSystem::Warning(std::string classOfTheMsg, std::string headingOfMsg, std::string definitionOfMsg)
{
	std::string message = "WARNING: " + classOfTheMsg + ":" + headingOfMsg + "\n" + definitionOfMsg;
	ImVec4 col(1, .4f, 0, 1);
	char* m = new char[256];
	strcpy_s(m, 256, message.c_str());
	BaseGUI::GetInstance().AddLogToConsole(m, col);
}

void GD_Tool::Mainframework::MessageSystem::Error(std::string classOfTheMsg, std::string headingOfMsg, std::string definitionOfMsg)
{
	std::string message ="ERROR: " + classOfTheMsg + ":" + headingOfMsg + "\n" + definitionOfMsg;
	ImVec4 col(1, 0, 0, 1);
	char* m = new char[256];
	strcpy_s(m,256, message.c_str());
	BaseGUI::GetInstance().AddLogToConsole(m, col);
}
