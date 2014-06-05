#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include "surferclient.hpp"

void worker_func ( boost::shared_ptr<surferclient>& sp_sc )
{
    try {
        // Initialise the server.
        sp_sc->run();

    } catch ( std::exception& e ) {
        std::cerr << "exception: " << e.what() << "\n";
    }

}

int main ( int argc, char** argv )
{
    try {
        // Check command line arguments.
        if ( argc != 4 ) {
            std::cerr << "Usage: surferclient <address> <port> <threads>\n";
            return 1;
        }

        std::size_t num_threads = boost::lexical_cast<std::size_t> ( argv[3] );
        boost::shared_ptr<surferclient> sp_surfaceclient ( new surferclient ( argv[1], argv[2], num_threads ) );
        boost::thread t ( boost::bind ( &worker_func, sp_surfaceclient ) );

        std::string inputo;
        while ( sp_surfaceclient.use_count() > 0 ) {
            std::cout << "enter command:";
            std::cin >> inputo;
            std::string::size_type qst = inputo.find ( "exito" );
            if ( qst != std::string::npos ) {
                sp_surfaceclient->handle_stop();
                break;
            }else{
                sp_surfaceclient->sendAMsg(inputo);
            }

        }

        t.join();
    } catch ( std::exception& e ) {
        std::cerr << "exception: " << e.what() << "\n";
    }

}
