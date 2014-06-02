#include "surferclient.hpp"
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

surferclient::surferclient ( const std::string& a3nwan, const std::string& madkhal, std::size_t a3adad_alkhitan )
    : sp_mukhdm_io_ ( new boost::asio::io_service )
    , sp_shaggil_ ( new boost::asio::io_service::work ( *sp_mukhdm_io_ ) )
    , sp_ishrat_alnizam_ ( new boost::asio::signal_set ( *sp_mukhdm_io_ ) )
    , a3nwan_(a3nwan)
    , madkhal_(madkhal)
    , a3adad_alkhitan_ ( a3adad_alkhitan )
{
    sp_ishrat_alnizam_->add ( SIGINT );
    sp_ishrat_alnizam_->add ( SIGTERM );
    sp_ishrat_alnizam_->add ( SIGQUIT );
    sp_ishrat_alnizam_->async_wait ( boost::bind ( &surferclient::handle_stop, this ) );
    
    ballesh();

}

void surferclient::run()
{
    // Create a pool of threads to run all of the io_services.
    boost::thread_group t_shillit_shagileh;

    for ( std::size_t i = 0; i < a3adad_alkhitan_; ++i ) {
            t_shillit_shagileh.create_thread ( boost::bind ( &boost::asio::io_service::run, sp_mukhdm_io_ ) );
        }

    t_shillit_shagileh.join_all();
}

void surferclient::ballesh()
{
    sp_baglanti_.reset(new baglanti(sp_mukhdm_io_, a3nwan_, madkhal_));
}

void surferclient::handle_stop()
{
    sp_shaggil_.reset();
    sp_mukhdm_io_->stop();
}
