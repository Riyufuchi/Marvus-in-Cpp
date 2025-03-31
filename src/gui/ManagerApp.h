#ifndef MARVUSTWO_HPP
#define MARVUSTWO_HPP

#include <wx/wx.h>

#include "MainFrame.h"

namespace keo
{
class ManagerApp : public wxApp
{
	private:
		MainFrame* frame;
	public:
		ManagerApp();
		~ManagerApp();
		virtual bool OnInit() override;
};
}
#endif /* MARVUSTWO_HPP */ 
