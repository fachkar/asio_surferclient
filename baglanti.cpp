#include "baglanti.hpp"
#include <vector>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/lexical_cast.hpp>

baglanti::baglanti ( boost::shared_ptr<boost::asio::io_service>& sp_io_service, const std::string& a3nwan, const std::string& madkhal )
{
    boost::asio::ip::udp::resolver resolver ( *sp_io_service );
    boost::asio::ip::udp::resolver::query query ( boost::asio::ip::udp::v4(), a3nwan, madkhal );
    sp_uzak_bitishnoktasi_.reset ( new boost::asio::ip::udp::endpoint ( *resolver.resolve ( query ) ) );
    sp_priz.reset ( new boost::asio::ip::udp::socket ( *sp_io_service, boost::asio::ip::udp::endpoint ( boost::asio::ip::udp::v4(), boost::lexical_cast<short> ( madkhal ) ) ) );
    sp_priz->set_option ( boost::asio::ip::udp::socket::reuse_address ( true ) );
    sp_strand_.reset ( new boost::asio::io_service::strand ( *sp_io_service ) );
}

void baglanti::bashla()
{
    gelen_buffer_.assign(0);
    sp_priz->async_receive_from ( boost::asio::buffer ( gelen_buffer_ ), *sp_uzak_bitishnoktasi_,
                                  sp_strand_->wrap ( boost::bind ( &baglanti::handle_receive_from, this,
                                                                   boost::asio::placeholders::error,
                                                                   boost::asio::placeholders::bytes_transferred ) ) );
}

void baglanti::sendAMsg ( std::string& msgo )
{
    sp_priz->async_send_to ( boost::asio::buffer ( msgo ), *sp_uzak_bitishnoktasi_,
                             sp_strand_->wrap ( boost::bind ( &baglanti::handle_send_to, this,
                                                              boost::asio::placeholders::error,  boost::asio::placeholders::bytes_transferred ) ) );
}


void baglanti::handle_receive_from ( const boost::system::error_code& error, std::size_t bytes_transferred )
{
    gelen_buffer_.assign(0);
    sp_priz->async_receive_from ( boost::asio::buffer ( gelen_buffer_ ), *sp_uzak_bitishnoktasi_,
                                  sp_strand_->wrap ( boost::bind ( &baglanti::handle_receive_from, this,
                                                                   boost::asio::placeholders::error,
                                                                   boost::asio::placeholders::bytes_transferred ) ) );

    if ( !error  && bytes_transferred > 0 ) {
        std::cout << "received :" <<  gelen_buffer_.c_array() <<  std::endl;


    }
}


void baglanti::handle_send_to ( const boost::system::error_code& error, std::size_t bytes_sent )
{
    if ( !error && bytes_sent > 0 ) {
        std::cout <<  "sent: " <<  bytes_sent <<  std::endl;
    }
    gelen_buffer_.assign(0);
    sp_priz->async_receive_from ( boost::asio::buffer ( gelen_buffer_ ), *sp_uzak_bitishnoktasi_,
                                  sp_strand_->wrap ( boost::bind ( &baglanti::handle_receive_from, this,
                                                                   boost::asio::placeholders::error,
                                                                   boost::asio::placeholders::bytes_transferred ) ) );
}


