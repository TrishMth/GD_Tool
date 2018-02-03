#pragma region Internal Includes
#include "include\Window.h"
#include "FVector3D.h"
#pragma endregion 
#pragma region External Includes
#include <Windows.h>
#include <cstdint>
#pragma endregion 
/**
*\brief
*
* Main function 
*
*
* <CENTER>
* @param hInstance Handle of the current instance of the application. 
* @param hPrevInstance Handle of the previous Instance of the application. Use this to check if other instances of the application are open. 
* @param lpCmdLine The command line for the application excluding the program name. 
* @param nCmdShow Controls how the window is to be shown 
*<DL>
*<LI> SW_HIDE (0) = Hides the window and activates another window </LI>
*<LI> SW_MAXIMIZE (3) = Maximizes the specified Window.  </LI>
*<LI> SW_MINIMIZE (6) = Minimizes the specified window and activates the next top-level window in the Z-order. </LI>
*</DL>
*</CENTER>
*/

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	PhysicsLibrary::Basics::FVector3D* vec = new PhysicsLibrary::Basics::FVector3D();
	


	GD_Tool::Mainframework::Window* currentWindow = new GD_Tool::Mainframework::Window(); 
	currentWindow->Init(1024, 786, hInstance, nCmdShow);
	

	return 1; 
}