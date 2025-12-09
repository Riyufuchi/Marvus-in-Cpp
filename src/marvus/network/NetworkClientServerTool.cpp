//==============================================================================
// File       : NetworkClientServerTool.cpp
// Author     : riyufuchi
// Created on : Dec 8, 2025
// Last edit  : Dec 9, 2025
// Copyright  : Copyright (c) 2025, riyufuchi
// Description: Marvus-in-Cpp
//==============================================================================

#include "NetworkClientServerTool.h"

namespace marvus
{

NetworkClientServerTool::NetworkClientServerTool()
{
}

NetworkClientServerTool::~NetworkClientServerTool()
{
}

void NetworkClientServerTool::runFileServer(unsigned short port, const std::string& output_file, std::atomic_bool& stop_flag, std::function<void(size_t, size_t)> progress_callback)
{
	boost::asio::io_context io_context;
	boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));
	boost::asio::ip::tcp::socket socket(io_context);
	acceptor.accept(socket);

	std::ofstream out(output_file, std::ios::binary);

	uint64_t network_file_size = 0;
	read(socket, boost::asio::buffer(&network_file_size, sizeof(network_file_size)));
	size_t total_file_size =  boost::endian::big_to_native(network_file_size);

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
		std::cerr << "Invalid IP address '" << server_ip << "': " << ec.message() << "\n";
		return;
	}

	boost::asio::ip::tcp::endpoint ep(addr, port);
	socket.connect(ep, ec);
	if (ec)
	{
		std::cerr << "Connect failed: " << ec.message() << "\n";
		return;
	}

	std::ifstream in(file_path, std::ios::binary | std::ios::ate);
	if(!in)
		return;
	size_t total_file_size = in.tellg();
	in.seekg(0);

	uint64_t network_file_size = boost::endian::native_to_big(total_file_size);
	boost::asio::write(socket, boost::asio::buffer(&network_file_size, sizeof(network_file_size)));

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
