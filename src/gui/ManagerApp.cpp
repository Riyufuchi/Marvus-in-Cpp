#include "ManagerApp.h"

namespace keo
{
ManagerApp::ManagerApp() : wxApp(), frame(nullptr)
{
}

ManagerApp::~ManagerApp()
{
	//delete frame;
}

bool ManagerApp::OnInit()
{
	this->frame = new MainFrame("KEO data manager");
	SetTopWindow(frame);
	frame->Show(true);
	return true;
}
}
