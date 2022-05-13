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
		//���� �⺻���� ��ü
		asio::io_service io_service;
		
		//TCP ���������� 13�� ��Ʈ�� ������ �޴� ���� ������ ����
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 13));

		while (true)
		{
			//���� ��ü�� ������ ������ ��ٸ���.
			std::cout << "���� ����" << std::endl;
			tcp::socket soc(io_service);
			std::cout << "accept()" << std::endl;
			acceptor.accept(soc);

			std::string message = MakeDaytime();
			std::cout << "�޽��� write()" << std::endl;
			// Ŭ���̾�Ʈ���� �޽����� ��� ����
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