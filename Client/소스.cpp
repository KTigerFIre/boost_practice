#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

int main()
{
	boost::asio::io_service io; // io service 객체 
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5)); // 일정시간 프로그램 슬립에 사용
	t.wait();

	std::cout << "Hello World!" << std::endl;
	return 0;
}