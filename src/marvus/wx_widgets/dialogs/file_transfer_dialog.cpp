//==============================================================================
// File       : FileTransferDialog.cpp
// Author     : riyufuchi
// Created on : Dec 08, 2025
// Last edit  : Jan 03, 2026
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "../../wx_widgets/dialogs/file_transfer_dialog.h"

namespace marvus
{

FileTransferDialog::FileTransferDialog(wxWindow* parent, const wxString& title, errorFunctionSignature& error_callback) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(300, 300)),
	error_callback(error_callback), network_operation(nullptr)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	progress_bar = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxSize(300, 30));
	status_text = new wxStaticText(this, wxID_ANY, "Idle");

	sizer->Add(progress_bar, 0, wxALL | wxEXPAND, 10);
	sizer->Add(status_text, 0, wxALL, 10);

	SetSizer(sizer);
	Layout();

	Bind(wxEVT_THREAD, &FileTransferDialog::OnUpdateProgress, this);
}

FileTransferDialog::~FileTransferDialog()
{
	safe_network_exit();
}

void FileTransferDialog::OnUpdateProgress(wxThreadEvent& event)
{
	int percent = event.GetInt();
	progress_bar->SetValue(percent);

	wxString message = wxString::Format("Progress: %d%%", percent);
	status_text->SetLabel(message);
}

void FileTransferDialog::safe_network_exit()
{
	if (network_operation)
	{
		delete network_operation;
		network_operation = nullptr;
	}
}

void FileTransferDialog::updateProgressBar(size_t bytes_sent, size_t total_bytes)
{
	wxThreadEvent event(wxEVT_THREAD, wxID_ANY);
	event.SetInt(static_cast<int>((bytes_sent * 100) / total_bytes));
	wxQueueEvent(this, event.Clone());
}


void FileTransferDialog::start_server(unsigned short port)
{
	network_operation = new FileServer([this](size_t bytes_sent, size_t total_bytes) { updateProgressBar(bytes_sent, total_bytes); }, port,  error_callback);
	if (network_operation)
		network_operation->start();
}

void FileTransferDialog::startClient(const wxString& server_ip, unsigned short port, const wxString& file_path)
{
	std::string ip = server_ip.ToStdString();
	std::string file = file_path.ToStdString();
	unsigned short portCopy = port;
}

} /* namespace marvus */
