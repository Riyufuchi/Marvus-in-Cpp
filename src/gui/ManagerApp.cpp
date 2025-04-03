#include "ManagerApp.h"

namespace keo
{
ManagerApp::ManagerApp(int argc, char** argv) : wxApp(), frame(nullptr), areArgs(false)
{
	this->args = ConsoleLib::ConsoleUtils::analyzeArgumentsInOrder(argc, argv, areArgs, text);
}

ManagerApp::~ManagerApp()
{
	//delete frame;
}

bool ManagerApp::OnInit()
{
	if (!areArgs)
		return false;
	this->frame = new MainFrame("KEO data manager", args);
	SetTopWindow(frame);
	frame->Show(true);
	return true;
}
}
