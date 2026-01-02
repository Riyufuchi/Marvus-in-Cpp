#include "file_client.h"

namespace marvus
{

FileClient::FileClient(const std::string& server_ip, unsigned short port, const std::string& file_path, std::function<void(size_t, size_t)>& progress_callback, errorFunctionSignature& efs) : NetworkBase(port, efs),
	server_ip(server_ip), file_path(file_path), progress_callback(progress_callback)
{}

void FileClient::send_file()
{
	auto addr = boost::asio::ip::make_address(server_ip, ec);
	if (ec)
	{
		error_callback("Network error", "Invalid IP address '" + server_ip + "': " + ec.message());
		return;
	}

	boost::asio::ip::tcp::endpoint ep(addr, port);
	socket.connect(ep, ec);
	if (ec)
	{
		error_callback("Network error", "Connect failed: " + ec.message());
		return;
	}

	std::ifstream in(file_path, std::ios::binary | std::ios::ate);
	if(!in)
	{
		error_callback("Network error", "Invalid file for transfer");
		return;
	}
	size_t total_file_size = in.tellg();
	in.seekg(0);

	// Send file size
	uint64_t network_file_size = boost::endian::native_to_big(total_file_size);
	boost::asio::write(socket, boost::asio::buffer(&network_file_size, sizeof(network_file_size)));
	// Send file name with type
	std::string file_name = std::filesystem::path(file_path).filename().string();
	uint64_t name_length = boost::endian::native_to_big((uint64_t)file_name.size());
	boost::asio::write(socket, boost::asio::buffer(&name_length, sizeof(name_length)));
	boost::asio::write(socket, boost::asio::buffer(file_name));

	char buffer_data[4096];
	size_t bytes_sent = 0;
	std::streamsize n;

	while (!in.eof())
	{
		in.read(buffer_data, sizeof(buffer_data));
		n = in.gcount();
		if (n <= 0)
			break;

		boost::asio::write(socket, boost::asio::buffer(buffer_data, n));
		bytes_sent += n;

		if (progress_callback)
			progress_callback(bytes_sent, total_file_size);
	}

	if (progress_callback)
		progress_callback(bytes_sent, total_file_size);
}

void FileClient::run(std::stop_token st)
{
	send_file();
}

}
