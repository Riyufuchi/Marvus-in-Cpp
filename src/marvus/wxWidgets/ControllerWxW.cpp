//==============================================================================
// File       : ControllerWxW.cpp
// Author     : riyufuchi
// Created on : Dec 11, 2025
// Last edit  : Dec 15, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "ControllerWxW.h"

namespace marvus
{

ControllerWxW::ControllerWxW(errorFunctionSignature errorHandler) : Controller(errorHandler)
{
}

ControllerWxW::~ControllerWxW()
{
}

void ControllerWxW::sendFileOverNetwork(wxWindow* parent)
{
	FileTransferDialog networkDialog(parent, "Send data", errorHandler);
	wxString ipAddress = configFile.getServerIPv4();
	wxTextEntryDialog textDialog(parent, "IPv4 address:", "Network setup", ipAddress);

	wxString filters =
		"Data files (*.zip;*.db)|*.zip;*.db|"
		"All files (*.*)|*.*";

	wxFileDialog openFileDialog(parent, "Select a zip file",
		"", "", filters, wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (openFileDialog.ShowModal() == wxID_CANCEL)
		return;

	wxString path = openFileDialog.GetPath();

	if (textDialog.ShowModal() == wxID_OK)
	{
	networkDialog.startClient(textDialog.GetValue(), configFile.getPort(), path.ToStdString());
		networkDialog.ShowModal();
	}
}

void ControllerWxW::recieveFileFromNetwork(wxWindow* parent)
{
	marvus::FileTransferDialog networkDialog(parent, "Receive data", errorHandler);
	networkDialog.startServer(configFile.getPort());
	networkDialog.ShowModal();
}

} /* namespace marvus */
