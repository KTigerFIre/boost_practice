#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace boost;
using asio::ip::tcp;

std::string MakeDaytime()
{
	auto now = std::time(0);
	return ctime(&now);
}

int main()
{
	try
	{
		//가장 기본적인 객체
		asio::io_service io_service;
		
		//TCP 프로토콜의 13번 포트로 연결을 받는 수동 소켓을 생성
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));

		while (true)
		{
			//소켓 객체를 생성해 연결을 기다린다.
			std::cout << "소켓 생성" << std::endl;
			tcp::socket soc(io_service);
			std::cout << "accept()" << std::endl;
			acceptor.accept(soc);

			std::string message = MakeDaytime();
			std::cout << "메시지 write()" << std::endl;
			// 클라이언트에게 메시지를 담아 전송
			system::error_code ignored_error;
			asio::write(soc, asio::buffer(message), ignored_error);

		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}


	return 0;
}