//==============================================================================
// File       : FileTransferDialog.h
// Author     : riyufuchi
// Created on : Dec 08, 2025
// Last edit  : Dec 11, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#ifndef MARVUS_WXW_FILETRANSFERDIALOG_H_
#define MARVUS_WXW_FILETRANSFERDIALOG_H_

#include <thread>
#include <atomic>

#include <wx/wx.h>

#include "../../network/file_transfer/file_client.h"
#include "../../network/file_transfer/file_server.h"

namespace marvus
{

class FileTransferDialog : public wxDialog
{
private:
	std::thread network_thread;
	std::atomic_bool stop_flag{false};
	wxGauge* progress_bar_;
	wxStaticText* status_text_;
	errorFunctionSignature error_callback;
	NetworkBase* network_operation;
	void OnUpdateProgress(wxThreadEvent& event);
	void OnClose(wxCloseEvent& event);
	void safeExit();
	void updateProgressBar(size_t bytes_sent, size_t total_bytes);
public:
	FileTransferDialog(wxWindow* parent, const wxString& title, errorFunctionSignature& error_callback);
	virtual ~FileTransferDialog();
	void startServer(unsigned short port);
	void startClient(const wxString& server_ip, unsigned short port, const wxString& file_path);
};

} /* namespace marvus */

#endif /* MARVUS_WXW_FILETRANSFERDIALOG_H_ */
