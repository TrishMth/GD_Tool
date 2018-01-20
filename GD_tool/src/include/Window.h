#pragma once
#pragma region Internal Includes
#pragma endregion 
#pragma region External Includes
#include <Windows.h>
#include <cstdint>
#pragma endregion 


namespace GD_Tool
{
	namespace Mainframework
	{
		///\class Window.h "src/include/Window.h
		///\brief this is the base window class which creates an window. 
		class Window
		{
		public: 
			///Constructor
			Window() {};  
			///Copy Constructor
			Window(const Window& window) {}; 
			///Initialize the window
			void const Init(const uint16_t& resolutionX, const uint16_t& resolutionY, const HINSTANCE& hInstance, const int32_t& nCmdShow);  
			///Shut down the current window
			void const ShutDown(); 
			///Destructor
			~Window(); 
		private: 
			///the private run function which will get startes after the window is initialized.
			void const Run(const HWND& hWnd, const int32_t& nCmdShow);  
			///private member variable of a MSG to set the message to WM_QUIT in the shut down and the run function. 
			MSG m_message; 

		};
	}
}