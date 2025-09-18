#include "MarvusApp.h"

namespace riyufuchi
{
MarvusApp::MarvusApp(int argc, char** argv) : wxApp(), frame(nullptr), areArgs(false)
{
	this->args = ConsoleLib::ArgumentParser::analyzeInOrder(argc, argv, areArgs, text);
}

MarvusApp::~MarvusApp()
{
	//delete frame;
}

bool MarvusApp::OnInit()
{
	if (!areArgs)
		return false;
	this->frame = new MarvusFrame("Marvus in C++", args);
	SetTopWindow(frame);
	frame->Show(true);
	return true;
}
}
