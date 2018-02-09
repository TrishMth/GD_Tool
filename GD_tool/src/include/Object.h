#pragma once
#pragma region Internal Includes
#include "IntegerVariable.h"
#include "IBaseVariable.h"
#pragma endregion 
#pragma region External Includes
#include <string>
#pragma endregion

namespace GD_Tool
{
	namespace Mainframewok
	{
		class Object
		{
		public: 
			/**
			* Default Constructor of the Object Class
			*/
			Object(); 
			/**
			* Method to add another Object to this Object 
			* @param obj The Object you wants to add to the current object
			*/
			void AddObject(Object* obj); 
			/**
			* Method to add some variables to the objcet
			* @param variable The current Variable you want to add to the Object
			*/
			void AddVariable(class IBaseVariable* variable);
			/**
			* Default Destructor of the Object Class
			*/
			~Object(); 
		};
	}
}