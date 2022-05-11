#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
	boost::asio::io_service io; // io service ��ü 
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5)); // �����ð� ���α׷� ������ ���
	t.wait();

	std::cout << "Hello World!" << std::endl;
	return 0;
}