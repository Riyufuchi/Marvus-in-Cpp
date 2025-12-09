//==============================================================================
// File       : FileTransferDialog.h
// Author     : riyufuchi
// Created on : Dec 8, 2025
// Last edit  : Dec 9, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_WXW_FILETRANSFERDIALOG_H_
#define MARVUS_WXW_FILETRANSFERDIALOG_H_

#include <thread>
#include <atomic>

#include <wx/wx.h>

#include "../network/NetworkClientServerTool.h"

namespace marvus
{

class FileTransferDialog : public wxDialog
{
private:
	std::thread network_thread;
	std::atomic_bool stop_flag{false};
	wxGauge* progress_bar_;
	wxStaticText* status_text_;
	NetworkClientServerTool clientServerTool;
	void OnUpdateProgress(wxThreadEvent& event);
	void OnClose(wxCloseEvent& event);
	void safeExit();
public:
	FileTransferDialog(wxWindow* parent, const wxString& title, errorFunctionSignature errorCallback);
	virtual ~FileTransferDialog();
	void startServer(unsigned short port, const wxString& output_file);
	void startClient(const wxString& server_ip, unsigned short port, const wxString& file_path);
};

} /* namespace marvus */

#endif /* MARVUS_WXW_FILETRANSFERDIALOG_H_ */
