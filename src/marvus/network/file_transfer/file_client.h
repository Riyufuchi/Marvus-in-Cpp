//==============================================================================
// File       : file_slient.h
// Author     : Riyufuchi
// Created on : Dec 29, 2025
// Last edit  : Dec 29, 2025
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
	void send_file();
public:
	FileClient(const std::string& server_ip, unsigned short port, const std::string& file_path, std::function<void(size_t, size_t)>& progress_callback, errorFunctionSignature& efs);
	// NetworkBase interface
protected:
	virtual void run(std::stop_token st) override;
};
}
#endif // FILE_CLIENT_H
