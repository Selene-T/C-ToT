#include "ToT.h"
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <Windows.h>

using namespace System;
using namespace System::Windows::Forms;

//void main(array<String^>^ args) {
int main(array<System::String^>^ argv) {
	//::ShowWindow(::GetConsoleWindow(), SW_HIDE);

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	TrackerofTime::ToT form;
	Application::Run(% form);
}

