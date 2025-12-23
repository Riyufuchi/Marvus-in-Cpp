//==============================================================================
// File       : ControllerWxW.h
// Author     : riyufuchi
// Created on : Dec 11, 2025
// Last edit  : Dec 11, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_WXWIDGETS_CONTROLLER_WX_H_
#define MARVUS_WXWIDGETS_CONTROLLER_WX_H_

#include <wx/wx.h>

#include "../base/controller.h"
#include "dialogs/file_transfer_dialog.h"

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

#endif /* MARVUS_WXWIDGETS_CONTROLLER_WX_H_ */
