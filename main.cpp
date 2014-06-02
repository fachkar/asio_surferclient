#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include "surferclient.hpp"

void worker_func ( char** argv )
{
    try {
        // Initialise the server.
        std::size_t num_threads = boost::lexical_cast<std::size_t> ( argv[3] );
        surferclient sc ( argv[1], argv[2], num_threads );

        sc.run();

    } catch ( std::exception& e ) {
        std::cerr << "exception: " << e.what() << "\n";
    }

}

int main ( int argc, char** argv )
{
    try {
        // Check command line arguments.
        if ( argc != 5 ) {
            std::cerr << "Usage: surferclient <address> <port> <threads>\n";
            return 1;
        }

        boost::thread t ( boost::bind ( &worker_func, argv ) );
        t.join();
    } catch ( std::exception& e ) {
        std::cerr << "exception: " << e.what() << "\n";
    }

}
