#include "json_body.hpp"
#include <boost/json/src.hpp>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/optional/optional_io.hpp>
#include <iostream>
#include <boost/program_options.hpp>
#include <iterator>
using namespace std;
namespace po = boost::program_options;


namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

int main(int argc, char ** argv)
{
	SetConsoleOutputCP(CP_UTF8);
	// Our test endpoint for testing the json
	string regionName=u8"合肥";
	string 	month=u8"2024-02";
	if(argc>1) month=argv[1];

    const auto host = "192.168.104.47";
    const auto target = "/common/easy/sm_aircond_energy/list";

    // The io_context is required for all I/O
    net::io_context ioc;

    // These objects perform our I/O
    tcp::resolver resolver(ioc);
    beast::tcp_stream stream(ioc);

    // Look up the domain name
    auto const results = resolver.resolve(host, "8080");

    // Make the connection on the IP address we get from a lookup
    stream.connect(results);

    // Set up an HTTP POST request message
    http::request<json_body> req{http::verb::post, target, 11};
    req.set(http::field::host, host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req.set(http::field::content_type, "application/json");
    //req.set(http::field::accept, "application/json, text/plain, */*");
    req.body() = {{"totalMonth",month},{"regionName",regionName},{"pageNum","1"},{"pageSize","10"}};
//    req.body()="{totalMonth: 2024-03,regionName:合肥,pageNum: 1,pageSize: 10}";
    req.prepare_payload();
    // Send the HTTP request to the remote host
    http::write(stream, req);
    
    // This buffer is used for reading and must be persisted
    beast::flat_buffer buffer;

    // Get the response
    http::response<json_body> res;

    // Receive the HTTP response
    http::read(stream, buffer, res);

    // Write the message to standard out

    std::cout << "res.body.size"<<res.payload_size()<< std::endl;
    std::cout << res.body() << std::endl;

    // Gracefully close the socket
    beast::error_code ec;
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);


    return 0;
}
