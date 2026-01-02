#include "file_server.h"

namespace marvus
{

FileServer::FileServer(const std::function<void(size_t, size_t)>& progress_callback, unsigned short port, errorFunctionSignature& efs) : NetworkBase(port, efs), progress_callback(progress_callback)
{}

FileServer::~FileServer()
{
	io_context.stop();
}

void FileServer::recieve_file()
{
	boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
	boost::asio::ip::tcp::socket socket(io_context);
	acceptor.accept(socket);

	uint64_t network_file_size = 0;
	read(socket, boost::asio::buffer(&network_file_size, sizeof(network_file_size)));
	size_t total_file_size =  boost::endian::big_to_native(network_file_size);
	// Read file name length
	uint64_t network_length;
	boost::asio::read(socket, boost::asio::buffer(&network_length, sizeof(network_length)));
	uint64_t name_length = boost::endian::big_to_native(network_length);
	// Read the file name
	std::string file_name(name_length, '\0');
	boost::asio::read(socket, boost::asio::buffer(file_name));

	std::ofstream out(file_name, std::ios::binary);

	char buffer_data[4096];
	size_t bytes_received = 0;
	boost::system::error_code ec;
	size_t n;

	while (bytes_received < total_file_size)
	{
		n = socket.read_some(boost::asio::buffer(buffer_data), ec);
		if ((ec == boost::asio::error::eof) || ec)
			return;

		out.write(buffer_data, n);
		bytes_received += n;

		if (progress_callback)
			progress_callback(bytes_received, total_file_size);
	}

	if (progress_callback)
		progress_callback(bytes_received, total_file_size);
}

void FileServer::run(std::stop_token st)
{
	while (!st.stop_requested())
		recieve_file();

}

}
