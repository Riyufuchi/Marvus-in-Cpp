#ifndef MARVUSTWO_HPP
#define MARVUSTWO_HPP

#include <wx/wx.h>

#include "MainFrame.h"
#include "ConsoleUtils.h"

namespace keo
{
class ManagerApp : public wxApp
{
	private:
		MainFrame* frame;
		bool areArgs;
		std::string text;
		std::vector<std::pair<std::string, std::vector<std::string>>> args;
	public:
		ManagerApp(int argc, char** argv);
		~ManagerApp();
		virtual bool OnInit() override;
};
}
#endif /* MARVUSTWO_HPP */ 
