#include "include\LoadSystem.h"


void GD_Tool::Mainframework::LoadSystem::LoadProject(const std::string & filePath)
{
	std::fstream fileStream; 
	fileStream.open(filePath, std::fstream::in);
	GD_Tool::Mainframework::ProjectDesc proDesc{};
	GD_Tool::Mainframework::ObjectDesc objDesc{};
	GD_Tool::Mainframework::FormulaDesc formDesc{};
	bool inProDesc = false; 
	bool inObjDesc = false; 
	bool inFormDesc = false; 
	uint32_t proDescCount = 0;
	uint32_t objDescCount = 0;
	uint32_t formDescCount = 0;
	if (fileStream.is_open())
	{
		fileStream.seekg(0, fileStream.end);
		size_t size = fileStream.tellg();
		fileStream.seekg(0, fileStream.beg);
		char* buffer = (char*)malloc(size);
		std::string strBuffer; 
		while (!fileStream.eof())
		{
			fileStream.getline(buffer, size);
			strBuffer = buffer; 
			if (strBuffer == "_pDesc")
			{
				inProDesc = true;
				continue;
			}
			else if (strBuffer ==  "_objDesc")
			{
				inProDesc = false;
				inObjDesc = true;
				continue;
			}
			else if (strBuffer == "_FormDesc")
			{
				inObjDesc = false; 
				inFormDesc = true;
				continue;
			}
			else if (strBuffer == "_End")
			{
				break;
			}
			if (inProDesc)
			{
				switch (proDescCount)
				{
				case 0:
					proDesc.Name = strBuffer + "\n";
					ProjectManager::CreateInstance(strBuffer);

					break;
				}
			}
			if (inObjDesc)
			{
				LoadObjData(strBuffer);
			}
			if (inFormDesc)
			{
				LoadFormData(strBuffer);
			}			
		}
		ProjectManager::GetInstance().Save();
	}
	fileStream.close();
}

GD_Tool::Mainframework::AppConfigDesc GD_Tool::Mainframework::LoadSystem::LoadConfig()
{
	std::fstream fileStream;
	AppConfigDesc configDesc{};
	fileStream.open(".//config.txt", std::fstream::in);
	if (fileStream.is_open())
	{
		uint32_t lineCount = 0; 
		fileStream.seekg(0, fileStream.end);
		size_t size = fileStream.tellg();
		fileStream.seekg(0, fileStream.beg);
		char* buffer = (char*)malloc(size);
		while (!fileStream.eof())
		{
			fileStream.getline(buffer, size);
			std::string str = buffer; 
			configDesc.SetAppConfigDesc(buffer, lineCount);
			lineCount++;
		}
	}
	else
	{
		fileStream.open(".//config.txt", std::fstream::out);
		if (fileStream.is_open())
		{
			fileStream.seekg(0, fileStream.end);
			size_t size = fileStream.tellg();
			fileStream.seekg(0, fileStream.beg);
			if (size == 0)
			{
				
				configDesc = CreateDefaultConfigFile(fileStream, configDesc);
				return configDesc;
			}
		}
	}
	fileStream.close();
	return configDesc;
}

GD_Tool::Mainframework::AppConfigDesc GD_Tool::Mainframework::LoadSystem::CreateDefaultConfigFile(std::fstream& stream, GD_Tool::Mainframework::AppConfigDesc& desc)
{
	std::string buffer = std::to_string(desc.WindowWidth) + "\n" + std::to_string(desc.WindowHeight) + "\n" + std::to_string(desc.WindowPosX) + "\n" + std::to_string(desc.WindowPosY) +"\n" 
		+ std::to_string(desc.Maximized) + "\n" + std::to_string(desc.Styles) + "\n" + std::to_string(desc.VSync) +"\n";
	stream.write(buffer.c_str(), buffer.size()); 
	return desc; 
}

bool GD_Tool::Mainframework::LoadSystem::LoadObjData(const std::string & objName)
{
	if (!ProjectManager::GetInstance().IsInstantiated())
	{
		MessageSystem::Error("Load System", "Couldn't load project", "The project isn't instaniated yet, please check the project.txt file for the right format");
		return false;
	}
	std::fstream fileStream; 
	fileStream.open(ProjectManager::GetInstance().GetFilePath() + "//Objects//" + objName + "_Obj.txt");
	if (fileStream.is_open())	
	{ 
		ProjectManager::GetInstance().CreateObject(objName);
	}
	else
	{
		MessageSystem::Error("Load system", "Couldn't load object: " + objName + " of: " + ProjectManager::GetInstance().GetName(), "There is no file to load the object");
		return false; 
	}
	fileStream.close();
	return true; 
}

bool GD_Tool::Mainframework::LoadSystem::LoadFormData(const std::string & formName)
{
	if (!ProjectManager::GetInstance().IsInstantiated())
	{
		MessageSystem::Error("Load System", "Couldn't load project", "The project isn't instaniated yet, please check the project.txt file for the right format");
		return false;
	}
	std::fstream fileStream;
	fileStream.open(ProjectManager::GetInstance().GetFilePath() + "//Formulas//" + formName + "_Formula.txt");
	if (fileStream.is_open())
	{
		ProjectManager::GetInstance().CreateFormula(formName);
	}
	else
	{
		MessageSystem::Error("Load system", "Couldn't load formula: " + formName + " of: " + ProjectManager::GetInstance().GetName(), "There is no file to load the formula");
		return false;
	}
	fileStream.close();
	return true;
}
