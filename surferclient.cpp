
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

#include "surferclient.hpp"
#include "surferclient_structs.hpp"

surferclient::surferclient ( const std::string& a3nwan, const std::string& madkhal, std::size_t a3adad_alkhitan )
    : sp_mukhdm_io_ ( new boost::asio::io_service )
    , sp_shaggil_ ( new boost::asio::io_service::work ( *sp_mukhdm_io_ ) )
    , sp_ishrat_alnizam_ ( new boost::asio::signal_set ( *sp_mukhdm_io_ ) )
    , a3nwan_ ( a3nwan )
    , madkhal_ ( madkhal )
    , a3adad_alkhitan_ ( a3adad_alkhitan )
{
    sp_ishrat_alnizam_->add ( SIGINT );
    sp_ishrat_alnizam_->add ( SIGTERM );
    sp_ishrat_alnizam_->add ( SIGQUIT );
    sp_ishrat_alnizam_->async_wait ( boost::bind ( &surferclient::handle_stop, this ) );
    sp_baglanti_.reset ( new baglanti ( sp_mukhdm_io_, a3nwan_, madkhal_ ) );
}

void surferclient::run()
{
    // Create a pool of threads to run all of the io_services.
    boost::thread_group t_shillit_shagileh;

    for ( std::size_t i = 0; i < a3adad_alkhitan_; ++i ) {
        t_shillit_shagileh.create_thread ( boost::bind ( &boost::asio::io_service::run, sp_mukhdm_io_ ) );
    }

    ballesh();

    t_shillit_shagileh.join_all();
}

void surferclient::ballesh()
{

    sp_baglanti_->bashla();
}

void surferclient::handle_stop()
{
    sp_shaggil_.reset();
    sp_mukhdm_io_->stop();
}


int BuildStringPacket ( char* ThisPacket, std::wstring & ParmString, uint16_t PacketSize )
{
    uint8_t    XorParity = 0;
    uint16_t    SizeofThisPacket = PacketSize;
    char    ASCIIBuffer [256];
    int     CharToAdd = 0;

    std::memset ( ASCIIBuffer, 0, sizeof ( ASCIIBuffer ) );

    return SizeofThisPacket;
}

bool surferclient::sendAnInit()
{
    INITINFO       InitInfo;
    CACHEINFO      CacheInfo;
    LANGIDINFO     PadLangIdInfo;
    PADCAPSINFO    PadCapsInfo;
    PADFEATUREINFO PadFeaturesInfo;
    PAGEIDINFO     PageIdInfo;

    uint8_t           SizeofUserID     = 0,  SizeofPassword  = 0, SizeofSerialNo   = 0;
    uint8_t           SizeofBrandName  = 0,  SizeofModelName = 0;
    uint8_t           SizeofEncryptKey = 0;

    uint8_t           SizeofIMEIKey    = 0,  SizeofIMSIKey   = 0, SizeofCCIDKey    = 0, SizeofSimTelKey  = 0, SizeofRoamingKey = 0, SizeofLangKey = 0;
    uint8_t           SizeofSIMKeys    = 0;

    char           SerialNo      [32];
    char           BrandName     [32];
    char           ModelName     [32];
    char           EncryptKey    [32];
    char           UserID        [32];
    char           Password      [32];

    char           IMEIKey       [48];
    char           IMSIKey       [48];
    char           CCIDKey       [48];
    char           SimTelKey     [48];
    char           RoamingKey    [256];
    char           LangKey       [48];

#define        MaxPDAString 16
#define        MaxSIMString 32


    std::memset ( SerialNo, 0, sizeof ( SerialNo ) );
    std::memset ( BrandName, 0, sizeof ( BrandName ) );
    std::memset ( ModelName, 0, sizeof ( ModelName ) );
    std::memset ( EncryptKey, 0, sizeof ( EncryptKey ) );
    std::memset ( UserID, 0, sizeof ( UserID ) );
    std::memset ( Password, 0, sizeof ( Password ) );

    std::memset ( &InitInfo, 0, sizeof ( InitInfo ) );
    std::memset ( &CacheInfo, 0, sizeof ( CacheInfo ) );
    std::memset ( &PadCapsInfo, 0, sizeof ( PadCapsInfo ) );
    std::memset ( &PadLangIdInfo, 0, sizeof ( PadLangIdInfo ) );
    std::memset ( &PadFeaturesInfo, 0, sizeof ( PadFeaturesInfo ) );
    std::memset ( &PageIdInfo, 0, sizeof ( PageIdInfo ) );

    std::wstring PDAUserID(L"VZEM");
    


    return true;
}
