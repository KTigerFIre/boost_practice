#define _CRT_SECURE_NO_WARNINGS

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace boost;
using asio::ip::tcp;

int main()
{

	try
	{
		boost::asio::io_service io; // io service ��ü 

		//������ �̸��� tcp ������(ip, ��Ʈ)�� �ٲٱ� ���� resolver�� ���
		tcp::resolver resolver(io);

		//���� ������ �� localhost, ���񽺴� Daytime ��������
		tcp::resolver::query query_pro("localhost", "daytime");

		//DNS�� ���� IP�ּ� �� ��Ʈ ��ȣ�� ���ɴϴ�.
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query_pro);

		tcp::socket soc(io);

		asio::connect(soc, endpoint_iterator);
		while (true)
		{
			char buf[128];
			system::error_code error;
			// ���۸� �̿��� �����κ��� �����͸� �޾ƿ´�.
			size_t len = soc.read_some(asio::buffer(buf), error);

			if (asio::error::eof == error) break;
			else if (error) throw system::system_error(error);



			std::cout.write(buf, len);
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}



	return 0;
}