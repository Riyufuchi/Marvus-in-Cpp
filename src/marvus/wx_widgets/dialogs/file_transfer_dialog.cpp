//==============================================================================
// File       : FileTransferDialog.cpp
// Author     : riyufuchi
// Created on : Dec 08, 2025
// Last edit  : Dec 11, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "../../wx_widgets/dialogs/file_transfer_dialog.h"

namespace marvus
{

FileTransferDialog::FileTransferDialog(wxWindow* parent, const wxString& title, errorFunctionSignature errorCallback) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(300, 300)), clientServerTool(errorCallback)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	progress_bar_ = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxSize(300, 30));
	status_text_ = new wxStaticText(this, wxID_ANY, "Idle");

	sizer->Add(progress_bar_, 0, wxALL | wxEXPAND, 10);
	sizer->Add(status_text_, 0, wxALL, 10);

	SetSizer(sizer);
	Layout();

	Bind(wxEVT_CLOSE_WINDOW, &FileTransferDialog::OnClose, this);
	Bind(wxEVT_THREAD, &FileTransferDialog::OnUpdateProgress, this);
}

FileTransferDialog::~FileTransferDialog()
{
	safeExit();
}

void FileTransferDialog::OnUpdateProgress(wxThreadEvent& event)
{
	int percent = event.GetInt();
	progress_bar_->SetValue(percent);

	wxString message = wxString::Format("Progress: %d%%", percent);
	status_text_->SetLabel(message);
}

void FileTransferDialog::OnClose(wxCloseEvent&)
{
	safeExit();
}

void FileTransferDialog::safeExit()
{
	stop_flag = true; // signal thread to stop
	if (network_thread.joinable())
	{
		network_thread.join(); // wait for thread to finish
	}
	Destroy();
}

void FileTransferDialog::updateProgressBar(size_t bytes_sent, size_t total_bytes)
{
	wxThreadEvent event(wxEVT_THREAD, wxID_ANY);
	event.SetInt(static_cast<int>((bytes_sent * 100) / total_bytes));
	wxQueueEvent(this, event.Clone());
}


void FileTransferDialog::startServer(unsigned short port)
{
	stop_flag = false; // reset stop flag

	network_thread = std::thread([port, this]() {
		clientServerTool.runFileServer(port, stop_flag,
		[this](size_t bytes_sent, size_t total_bytes) { updateProgressBar(bytes_sent, total_bytes); });
	});
}

void FileTransferDialog::startClient(const wxString& server_ip, unsigned short port, const wxString& file_path)
{
	stop_flag = false;

	std::string ip = server_ip.ToStdString();
	std::string file = file_path.ToStdString();
	unsigned short portCopy = port;

	network_thread = std::thread([ip, portCopy, file, this]()
	{
		if (clientServerTool.runFileClient(ip, portCopy, file, stop_flag,
		[this](size_t bytes_sent, size_t total_bytes) { updateProgressBar(bytes_sent, total_bytes); }))
		{
			wxMessageBox("Transfer of file " + file + " succeeded.", "Network success", wxICON_INFORMATION);
		}
		else
		{
			wxMessageBox("Transfer of file " + file + " failed.", "Network error", wxICON_ERROR);
		}
	});
}

} /* namespace marvus */
