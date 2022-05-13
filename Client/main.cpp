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
		boost::asio::io_service io; // io service 객체 

		//도메인 이름을 tcp 종단점(ip, 포트)로 바꾸기 위해 resolver를 사용
		tcp::resolver resolver(io);

		//서버 도메인 명 localhost, 서비스는 Daytime 프로토콜
		tcp::resolver::query query_pro("localhost", "daytime");

		//DNS를 거쳐 IP주소 및 포트 번호를 얻어옵니다.
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query_pro);

		tcp::socket soc(io);

		asio::connect(soc, endpoint_iterator);
		while (true)
		{
			char buf[128];
			system::error_code error;
			// 버퍼를 이용해 서버로부터 데이터를 받아온다.
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