#ifndef BAGLANTI_HPP
#define BAGLANTI_HPP

#include <vector>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/circular_buffer.hpp>

class baglanti
    : private boost::noncopyable
{
    public:
        /// ctor a cnnction with the given io_service ptr
        explicit baglanti ( boost::shared_ptr<boost::asio::io_service>& sp_io_service, const std::string& a3nwan, const std::string& madkhal );

        /// Start the first asynchronous operation for this Obj
        void bashla();
        void sendAMsg ( std::string& msgo );
        /// hndle recv completion
        void handle_receive_from ( const boost::system::error_code& error, std::size_t bytes_transferred,  boost::shared_ptr<boost::array<char, 8192> > sp_ba );
        void handle_send_to ( const boost::system::error_code& error, std::size_t bytes_sent );
        /// sockt for the cnnction
        boost::shared_ptr<boost::asio::ip::udp::socket> sp_priz;
        boost::shared_ptr<boost::asio::ip::udp::endpoint> sp_uzak_bitishnoktasi_;
        boost::shared_ptr<boost::asio::io_service::strand> sp_strand_;
        /// bffer 4 incming data
        boost::shared_ptr<boost::array<char, 8192> > sp_gelen_buffer_;
        std::vector< boost::shared_ptr<boost::array<char, 8192> > > vctr_sp_gelen_buffer_;
};

# endif

