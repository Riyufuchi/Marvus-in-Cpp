//==============================================================================
// File       : FileTransferDialog.cpp
// Author     : riyufuchi
// Created on : Dec 8, 2025
// Last edit  : Dec 9, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "FileTransferDialog.h"

namespace marvus
{

FileTransferDialog::FileTransferDialog(wxWindow* parent, const wxString& title) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(300, 300))
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
}

void FileTransferDialog::OnUpdateProgress(wxThreadEvent& event)
{
	int percent = event.GetInt();
	progress_bar_->SetValue(percent);

	wxString message = wxString::Format("Progress: %d%%", percent);
	status_text_->SetLabel(message);
}

void FileTransferDialog::OnClose(wxCloseEvent& event)
{
	stop_flag = true; // signal thread to stop
	if(network_thread.joinable())
	{
		network_thread.join(); // wait for thread to finish
	}
	Destroy();
}

void FileTransferDialog::startServer(unsigned short port, const wxString& output_file)
{
	stop_flag = false; // reset stop flag

	std::string file = output_file.ToStdString();

	network_thread = std::thread([file, port, this]() {
		clientServerTool.runFileServer(port, file, stop_flag,
		[this](size_t bytes_received, size_t total_bytes) {
			// Send progress to GUI
			int percent = static_cast<int>((bytes_received * 100) / total_bytes);
			wxThreadEvent event(wxEVT_THREAD, wxID_ANY);
			event.SetInt(percent);
			wxQueueEvent(this, event.Clone());
		});
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
		clientServerTool.runFileClient(ip, portCopy, file, stop_flag,
		[this](size_t bytes_sent, size_t total_bytes)
		{
			int percent = static_cast<int>((bytes_sent * 100) / total_bytes);
			wxThreadEvent event(wxEVT_THREAD, wxID_ANY);
			event.SetInt(percent);
			wxQueueEvent(this, event.Clone());
		});
	});
}

} /* namespace marvus */
