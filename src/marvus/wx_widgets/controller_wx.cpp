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

void ControllerWxW::send_file_over_network(wxWindow* parent)
{
	if (is_network_running)
		return;

	is_network_running = true;

	wxString filters =
		"Data files (*.zip;*.db)|*.zip;*.db|"
		"All files (*.*)|*.*";

	wxFileDialog open_file_dialog(parent, "Select a zip file",
		"", "", filters, wxFD_OPEN | wxFD_FILE_MUST_EXIST);

	if (open_file_dialog.ShowModal() == wxID_CANCEL)
		return;

	wxString path_wxstr = open_file_dialog.GetPath();

	wxString ip_address_wxstr = configFile.getServerIPv4();
	wxTextEntryDialog text_dialog(parent, "IPv4 address:", "Network setup", ip_address_wxstr);
	if (text_dialog.ShowModal() != wxID_OK)
		return;

	auto* network_dialog = new FileTransferDialog(parent, "Send data", errorHandler);
	network_dialog->Bind(wxEVT_CLOSE_WINDOW, [this, network_dialog](wxCloseEvent&)
	{
		network_dialog->safe_network_exit();
		network_dialog->Destroy();
		is_network_running = false;
	});
	network_dialog->start_client(text_dialog.GetValue(), configFile.getPort(), path_wxstr.ToStdString());
	network_dialog->Show();

}

void ControllerWxW::recieve_file_from_network(wxWindow* parent)
{
	if (is_network_running)
		return;

	is_network_running = true;

	auto* network_dialog = new FileTransferDialog(parent, "Receive data", errorHandler);
	network_dialog->start_server(configFile.getPort());

	network_dialog->Bind(wxEVT_CLOSE_WINDOW, [network_dialog](wxCloseEvent&)
	{
		std::thread([network_dialog]
		{
			network_dialog->safe_network_exit();
			network_dialog->Destroy();
		}).detach();
	});

	network_dialog->Show();

	/*network_dialog->CallAfter([network_dialog]
	{
		network_dialog->Destroy();
	});*/
}

} /* namespace marvus */
