#include "include\ProjectManager.h"

GD_Tool::Mainframework::ProjectManager::ProjectManager(const std::string name)
	:m_name(name)
	,m_objIndex(0)
{
}

void GD_Tool::Mainframework::ProjectManager::ChangeName(const std::string newName)
{
	m_name = newName; 
}

void GD_Tool::Mainframework::ProjectManager::CreateObject(const std::string & name)
{
	Object* newObj = new Object(m_objIndex,name);
	m_objIndex++;
	AddObject(newObj);
}

std::vector<GD_Tool::Mainframework::Object*> GD_Tool::Mainframework::ProjectManager::GetObjects()
{
	return m_baseObjects;
}

void GD_Tool::Mainframework::ProjectManager::AddObject(Object * obj)
{
	m_baseObjects.push_back(obj);
}

void GD_Tool::Mainframework::ProjectManager::CreateVariable()
{
	IntegerVariable newVar(0, "new_Var" + m_varIndex);
	m_varIndex++; 
	m_variables.push_back(newVar); 
}

void GD_Tool::Mainframework::ProjectManager::CreateFormula()
{
	Formula* newFormula = new Formula("Formula" + m_formulaIndex);
	m_formulaIndex++;
	m_formulas.push_back(newFormula);
}

GD_Tool::Mainframework::ProjectPackage GD_Tool::Mainframework::ProjectManager::PackageProject()
{
	GD_Tool::Mainframework::ProjectPackage package;
	package.FormulaIndex = m_formulaIndex; 
	package.Formulas = m_formulas; 
	package.Name = m_name; 
	package.Objects = m_baseObjects; 
	package.ObjIndex = m_objIndex; 
	package.VariableIndex = m_varIndex; 
	package.Variables = m_variables; 
}

