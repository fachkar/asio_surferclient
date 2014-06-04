#ifndef SURFER_CLIENT_HPP
#define SURFER_CLIENT_HPP

#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include "baglanti.hpp"

class surferclient
    : private boost::noncopyable
{
public:
    explicit surferclient ( const std::string& a3nwan, const std::string& madkhal, std::size_t a3adad_alkhitan );

    /// Run the surferclient's io_service loop.
    void run();
    void ballesh();
    void handle_stop();
    bool sendAnInit();
    int ConvertToAsciiChar ( char* OutputBuffer, uint32_t OutputSize, const char* SourceBuffer, uint32_t SourceSizeInChar );
    int BuildStringPacket ( char* ThisPacket, std::wstring & ParmString, uint16_t PacketSize );

    std::size_t a3adad_alkhitan_;

    boost::shared_ptr< boost::asio::io_service > sp_mukhdm_io_;
    boost::shared_ptr< boost::asio::io_service::work > sp_shaggil_;
    boost::shared_ptr< boost::asio::signal_set > sp_ishrat_alnizam_;
    boost::shared_ptr<baglanti> sp_baglanti_;
    std::string a3nwan_;
    std::string madkhal_;
};

#endif // SURFER_CLIENT_HPP
