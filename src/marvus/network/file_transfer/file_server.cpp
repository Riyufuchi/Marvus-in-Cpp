//==============================================================================
// File       : file_server.cpp
// Author     : Riyufuchi
// Created on : Dec 29, 2025
// Last edit  : Jan 03, 2026
//==============================================================================

#include "file_server.h"

namespace marvus
{

FileServer::FileServer(const std::function<void(size_t, size_t)>& progress_callback, unsigned short port, errorFunctionSignature& efs) : NetworkBase(port, efs), progress_callback(progress_callback)
{}

FileServer::~FileServer()
{
}

void FileServer::recieve_file(std::stop_token st)
{
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
	size_t n;

	while (bytes_received < total_file_size && !st.stop_requested())
	{
		n = socket.read_some(boost::asio::buffer(buffer_data), ec);
		if ((ec == boost::asio::error::eof) || ec == boost::asio::error::operation_aborted || ec)
			break;

		out.write(buffer_data, n);
		bytes_received += n;

		if (progress_callback)
			progress_callback(bytes_received, total_file_size);
	}

	if (progress_callback)
		progress_callback(bytes_received, total_file_size);

	if (bytes_received != total_file_size)
	{
		out.close();
		std::filesystem::remove(file_name);
	}
}

void FileServer::run(std::stop_token st)
{
	recieve_file(st);
}

}
