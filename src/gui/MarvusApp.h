#ifndef _MARVUS_APP_H_
#define _MARVUS_APP_H_

#include <wx/wx.h>

#include "ArgumentParser.h"
#include "MarvusFrame.h"

namespace riyufuchi
{
class MarvusApp : public wxApp
{
	private:
		MarvusFrame* frame;
		bool areArgs;
		std::string text;
		ConsoleLib::argVector args;
	public:
		MarvusApp(int argc, char** argv);
		virtual ~MarvusApp();
		virtual bool OnInit() override;
};
}
#endif /* MARVUSTWO_HPP */ 
