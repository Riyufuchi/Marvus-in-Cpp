#ifndef FILE_SERVER_H
#define FILE_SERVER_H

#include "../base/network_base.h"

namespace marvus
{
class FileServer : public NetworkBase
{
private:
	std::function<void(size_t, size_t)> progress_callback;
	void recieve_file();
public:
	FileServer(const std::function<void(size_t, size_t)>& progress_callback, unsigned short port, errorFunctionSignature& efs);
	~FileServer();
	// NetworkBase interface
protected:
	virtual void run(std::stop_token st) override;
};
}
#endif // FILE_SERVER_H
