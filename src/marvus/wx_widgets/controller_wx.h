//==============================================================================
// File       : ControllerWxW.h
// Author     : riyufuchi
// Created on : Dec 11, 2025
// Last edit  : Jan 03, 2026
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_WX_WIDGETS_CONTROLLER_WX_H_
#define MARVUS_WX_WIDGETS_CONTROLLER_WX_H_

#include <wx/wx.h>
#include <wx/app.h>
#include <wx/event.h>
#include <wx/thread.h>
// STL
#include <thread>
// Local
#include "../base/controller.h"
#include "../wx_widgets/dialogs/file_transfer_dialog.h"

namespace marvus
{

class ControllerWxW : public Controller
{
private:
	bool is_network_running;
public:
	ControllerWxW(const errorFunctionSignature& errorHandler);
	virtual ~ControllerWxW();
	void recieve_file_from_network(wxWindow* parent);
	void send_file_over_network(wxWindow* parent);
};

} /* namespace marvus */

#endif /* MARVUS_WX_WIDGETS_CONTROLLER_WX_H_ */
