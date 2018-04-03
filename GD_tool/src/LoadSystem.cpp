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
			else if (strBuffer == "_objDesc")
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
				if (objDescCount == 0)
				{
					objDesc.Count = atoi((strBuffer + "\n").c_str());
					objDescCount++;
				}
				else
				{
					objDesc.Names.push_back(strBuffer);		
					ProjectManager::GetInstance().CreateObject(strBuffer);
					LoadObjData(strBuffer);
				}
			}
			if (inFormDesc)
			{
				if (formDescCount == 0)
				{
					formDesc.Count = atoi((strBuffer + "\n").c_str());
					formDescCount++;
				}
				else
				{
					formDesc.Names.push_back(strBuffer);
					ProjectManager::GetInstance().CreateFormula(strBuffer);
				}
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
	desc.WindowWidth = 1024; 
	desc.WindowHeight = 768; 
	std::string buffer = std::to_string(desc.WindowWidth) + "\n" + std::to_string(desc.WindowHeight) + "\n"; 
	stream.write(buffer.c_str(), buffer.size()); 
	return desc; 
}

bool GD_Tool::Mainframework::LoadSystem::LoadObjData(const std::string & objName)
{
	return false;
}

bool GD_Tool::Mainframework::LoadSystem::LoadFormData(const std::string & formName)
{
	return false;
}
