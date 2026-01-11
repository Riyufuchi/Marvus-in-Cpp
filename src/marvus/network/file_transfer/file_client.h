//==============================================================================
// File       : file_slient.h
// Author     : Riyufuchi
// Created on : Dec 29, 2025
// Last edit  : Jan 11, 2026
//==============================================================================

#ifndef FILE_CLIENT_H
#define FILE_CLIENT_H

#include "../base/network_base.h"

namespace marvus
{
class FileClient : public NetworkBase
{
private:
	const std::string server_ip;
	const std::string file_path;
	std::function<void(size_t, size_t)> progress_callback;
	void send_file(std::stop_token st);
public:
	FileClient(const std::string& server_ip, unsigned short port, const std::string& file_path, const std::function<void(size_t, size_t)>& progress_callback, const ShowErrorFunction& efs);
	// NetworkBase interface
protected:
	virtual void run(std::stop_token st) override;
};
}
#endif // FILE_CLIENT_H
