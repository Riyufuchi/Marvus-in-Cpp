#include "gui/ManagerApp.h"

//wxIMPLEMENT_APP(keo::ManagerApp);

int main(int argc, char** argv)
{
	wxApp::SetInstance(new keo::ManagerApp(argc, argv));
	wxEntryStart(argc, argv);
	wxTheApp->CallOnInit();
	wxTheApp->OnRun();
	wxTheApp->OnExit();
	wxEntryCleanup();
}


