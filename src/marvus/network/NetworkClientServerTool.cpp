//==============================================================================
// File       : NetworkClientServerTool.cpp
// Author     : riyufuchi
// Created on : Dec 08, 2025
// Last edit  : Dec 11, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "NetworkClientServerTool.h"

namespace marvus
{

NetworkClientServerTool::NetworkClientServerTool(errorFunctionSignature errorCallback) : errorCallback(errorCallback)
{
}

NetworkClientServerTool::~NetworkClientServerTool()
{
}

void NetworkClientServerTool::runFileServer(unsigned short port, std::atomic_bool& stop_flag, std::function<void(size_t, size_t)> progress_callback)
{
	boost::asio::io_context io_context;
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

	while (!stop_flag)
	{
		size_t n = socket.read_some(boost::asio::buffer(buffer_data), ec);
		if (ec == boost::asio::error::eof)
			break;
		if (ec)
			break;

		out.write(buffer_data, n);
		bytes_received += n;

		if (progress_callback)
			progress_callback(bytes_received, total_file_size);
	}

	if (progress_callback)
		progress_callback(bytes_received, total_file_size);
}

void NetworkClientServerTool::runFileClient(const std::string& server_ip, unsigned short port, const std::string& file_path, std::atomic_bool& stop_flag, std::function<void(size_t, size_t)> progress_callback)
{
	boost::asio::io_context io_context;
	boost::asio::ip::tcp::socket socket(io_context);

	boost::system::error_code ec;

	auto addr = boost::asio::ip::make_address(server_ip, ec);
	if (ec)
	{
		errorCallback("Network error", "Invalid IP address '" + server_ip + "': " + ec.message());
		return;
	}

	boost::asio::ip::tcp::endpoint ep(addr, port);
	socket.connect(ep, ec);
	if (ec)
	{
		errorCallback("Network error", "Connect failed: " + ec.message());
		return;
	}

	std::ifstream in(file_path, std::ios::binary | std::ios::ate);
	if(!in)
	{
		errorCallback("Network error", "Invalid file for transfer");
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

	while (!stop_flag && !in.eof())
	{
		in.read(buffer_data, sizeof(buffer_data));
		std::streamsize n = in.gcount();
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

}/* namespace marvus */
