#include "baglanti.hpp"
#include <vector>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/logic/tribool.hpp>

baglanti::baglanti ( boost::shared_ptr<boost::asio::io_service>& sp_io_service, const std::string& a3nwan, const std::string& madkhal )
    : sp_gonderen_bitishnoktasi_ ( new boost::asio::ip::udp::endpoint )
{
    boost::asio::ip::udp::resolver resolver ( *sp_io_service );
    boost::asio::ip::udp::resolver::query query ( boost::asio::ip::udp::v4(), a3nwan, madkhal );
    sp_alici_bitishnoktasi_.reset ( new boost::asio::ip::udp::endpoint ( *resolver.resolve ( query ) ) );
    sp_priz.reset ( new boost::asio::ip::udp::socket ( *sp_io_service, *sp_alici_bitishnoktasi_ ) );
    sp_priz->set_option ( boost::asio::ip::udp::socket::reuse_address ( true ) );
    sp_strand_.reset ( new boost::asio::io_service::strand ( *sp_io_service ) );
}

void baglanti::bashla()
{
    sp_priz->async_receive_from ( boost::asio::buffer ( gelen_buffer_ ), *sp_gonderen_bitishnoktasi_,
                                  sp_strand_->wrap ( boost::bind ( &baglanti::handle_receive_from, this,
                                                                   boost::asio::placeholders::error,
                                                                   boost::asio::placeholders::bytes_transferred ) ) );
}

void baglanti::handle_receive_from ( const boost::system::error_code& error, std::size_t bytes_transferred )
{
    if ( !error  && bytes_transferred > 0 ) {
        boost::tribool result;


        if ( result ) {

        } else if ( !result ) {

        } else {
            sp_priz->async_receive_from ( boost::asio::buffer ( gelen_buffer_ ), *sp_gonderen_bitishnoktasi_,
                                          sp_strand_->wrap ( boost::bind ( &baglanti::handle_receive_from, this,
                                                                           boost::asio::placeholders::error,
                                                                           boost::asio::placeholders::bytes_transferred ) ) );
        }

    } else {
        sp_priz->async_receive_from ( boost::asio::buffer ( gelen_buffer_ ), *sp_gonderen_bitishnoktasi_,
                                      sp_strand_->wrap ( boost::bind ( &baglanti::handle_receive_from, this,
                                                                       boost::asio::placeholders::error,
                                                                       boost::asio::placeholders::bytes_transferred ) ) );
    }
}
