//==============================================================================
// File       : ControllerWxW.cpp
// Author     : riyufuchi
// Created on : Dec 11, 2025
// Last edit  : Jan 03, 2026
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "controller_wx.h"

namespace marvus
{

ControllerWxW::ControllerWxW(const errorFunctionSignature& errorHandler) : Controller(errorHandler)
{
	this->is_network_running = false;
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

void ControllerWxW::recieve_file_from_network(wxWindow* parent)
{
	if (is_network_running)
		return;

	is_network_running = true;

	auto* network_dialog = new FileTransferDialog(parent, "Receive data", errorHandler);

	network_dialog->Bind(wxEVT_CLOSE_WINDOW, [this, network_dialog](wxCloseEvent&)
	{
		network_dialog->safe_network_exit();
		network_dialog->Destroy();
		is_network_running = false;
	});

	network_dialog->Show();
}

} /* namespace marvus */
