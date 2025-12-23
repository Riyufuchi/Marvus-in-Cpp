//==============================================================================
// File       : ControllerWxW.h
// Author     : riyufuchi
// Created on : Dec 11, 2025
// Last edit  : Dec 11, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_WX_WIDGETS_CONTROLLER_WX_H_
#define MARVUS_WX_WIDGETS_CONTROLLER_WX_H_

#include <wx/wx.h>

#include "../base/controller.h"
#include "../wx_widgets/dialogs/file_transfer_dialog.h"

namespace marvus
{

class ControllerWxW : public Controller
{
public:
	ControllerWxW(errorFunctionSignature errorHandler);
	virtual ~ControllerWxW();
	void recieveFileFromNetwork(wxWindow* parent);
	void sendFileOverNetwork(wxWindow* parent);
};

} /* namespace marvus */

#endif /* MARVUS_WX_WIDGETS_CONTROLLER_WX_H_ */
