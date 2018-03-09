#include "include\LoadSystem.h"


GD_Tool::Mainframework::ProjectManager* GD_Tool::Mainframework::LoadSystem::LoadProject(const std::string & filePath)
{
	std::fstream fileStream; 
	fileStream.open(filePath, std::fstream::in);
	ProjectManager* proMan = nullptr;
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
					proMan = new ProjectManager(proDesc.Name);

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
					proMan->CreateObject(strBuffer);
					LoadObjData(strBuffer, proMan);
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
					proMan->CreateFormula(strBuffer);
				}
			}			
		}
	}
	else
	{
		return nullptr;
	}
	fileStream.close();
	proMan->Save();
	return proMan;
}

bool GD_Tool::Mainframework::LoadSystem::LoadObjData(const std::string & objName, ProjectManager* proMan)
{
	return false;
}

bool GD_Tool::Mainframework::LoadSystem::LoadFormData(const std::string & formName, ProjectManager* proMan)
{
	return false;
}
