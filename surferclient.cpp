
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
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


int surferclient::ConvertToAsciiChar ( char* OutputBuffer, uint32_t OutputSize, const char* SourceBuffer, uint32_t SourceSizeInChar )
{
    uint32_t Looper;
    uint8_t  ThisChar;
    uint32_t SizeToCopy  = SourceSizeInChar;
    int   NewLen      = 0;

    if ( OutputSize < SourceSizeInChar ) {
        SizeToCopy = OutputSize;
    }
    for ( Looper    = 0; Looper < SizeToCopy; Looper ++ ) {
        ThisChar   = SourceBuffer[Looper];
        OutputBuffer[Looper] = ThisChar;
    }
    OutputBuffer[Looper] = 0;
    NewLen               = Looper;
    return NewLen;
}

int surferclient::BuildStringPacket ( char* ThisPacket, std::wstring& ParmString, uint16_t PacketSize )
{
    uint8_t    XorParity = 0;
    uint16_t    SizeofThisPacket = PacketSize;
    char    ASCIIBuffer [256];
    int     CharToAdd = 0;

    std::memset ( ASCIIBuffer, 0, sizeof ( ASCIIBuffer ) );
    CharToAdd = ConvertToAsciiChar ( ASCIIBuffer, sizeof ( ASCIIBuffer ), reinterpret_cast<const char*> ( ParmString.c_str() ), boost::lexical_cast<uint32_t> ( ParmString.size() ) );

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

    typedef unsigned long DWORD_PTR;
#define        MaxPDAString 16
#define        MaxSIMString 32
#define LOWORD(l)           ((uint16_t)((DWORD_PTR)(l) & 0xffff))
#define HIWORD(l)           ((uint16_t)((DWORD_PTR)(l) >> 16))
#define LOBYTE(w)           ((uint8_t)((DWORD_PTR)(w) & 0xff))
#define HIBYTE(w)           ((uint8_t)((DWORD_PTR)(w) >> 8))


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

    std::wstring PDAUserID ( L"VZEM" );
    std::wstring PDAUserPsw ( L"Terminator" );
    std::wstring PDASerialNo ( L"P314-000-000-000" );
    std::wstring PDABrandName ( L"INetPad" );
    std::wstring PDAModelName ( L"Emulator" );
    std::wstring PDAEncryptKey ( L"" );
    std::wstring PDAIMEIKey    ;
    std::wstring PDAIMSIKey    ;
    std::wstring PDACCIDKey    ;
    std::wstring PDASimTelKey  ;
    std::wstring PDARoamingKey  ;
    std::wstring PDALangKey  ;

    UserID[0]          = 'U';
    UserID[1]          = ' ';
    SizeofUserID       = BuildStringPacket ( UserID, PDAUserID, 2 );



    Password[0]        = 'P';
    Password[1]        = ' ';
    SizeofPassword     = BuildStringPacket ( Password, PDAUserPsw, 2 );


    SerialNo[0]        = 'S';
    SerialNo[1]        = ' ';
    SizeofSerialNo     = BuildStringPacket ( SerialNo, PDASerialNo, 2 );

    BrandName[0]       = 'B';
    BrandName[1]       = ' ';
    SizeofBrandName    = BuildStringPacket ( BrandName, PDABrandName, 2 );

    ModelName[0]       = 'M';
    ModelName[1]       = ' ';
    SizeofModelName    = BuildStringPacket ( ModelName, PDAModelName, 2 );

    EncryptKey[0]      = 'K';
    EncryptKey[1]      = ' ';
    SizeofEncryptKey   = BuildStringPacket ( EncryptKey, PDAEncryptKey, 2 );

    IMEIKey[0]         = 'N';
    IMEIKey[1]         = ' ';
    SizeofIMEIKey      = BuildStringPacket ( IMEIKey, PDAIMEIKey, 2 );

    IMSIKey[0]         = 'n';
    IMSIKey[1]         = ' ';
    SizeofIMSIKey      = BuildStringPacket ( IMSIKey, PDAIMSIKey, 2 );

    CCIDKey[0]         = 'c';
    CCIDKey[1]         = ' ';
    SizeofCCIDKey      = BuildStringPacket ( CCIDKey, PDACCIDKey, 2 );

    SimTelKey[0]       = 'T';
    SimTelKey[1]       = ' ';
    SizeofSimTelKey    = BuildStringPacket ( SimTelKey, PDASimTelKey, 2 );

    RoamingKey[0]       = 'R';
    RoamingKey[1]       = ' ';
    SizeofRoamingKey    = BuildStringPacket ( RoamingKey, PDARoamingKey, 2 );

    LangKey[0]       = 'L';
    LangKey[1]       = ' ';
    SizeofLangKey    = BuildStringPacket ( LangKey, PDALangKey, 2 );

    SizeofSIMKeys      = ( SizeofIMEIKey + SizeofIMSIKey + SizeofCCIDKey + SizeofSimTelKey + SizeofRoamingKey + SizeofLangKey );

    uint8_t CommandCode = 0xE0;
    bool UseParity = true;
    bool EnableUnpackAndDraw = true;
    bool EnableStatusBar = false;
    uint16_t FirmwareVersion = 0x0700;
    char ActionMode = 'S';

    InitInfo.Command                    = CommandCode;
    InitInfo.SubCommand                 = 'I';
    InitInfo.MajorLSB                   = HIBYTE ( FirmwareVersion );
    InitInfo.MinorMSB                   = LOBYTE ( FirmwareVersion );
    InitInfo.Action                     = ActionMode;
    InitInfo.Len                        =  sizeof ( PadCapsInfo )
                                           +  sizeof ( PadFeaturesInfo )
                                           +  SizeofUserID
                                           +  SizeofPassword
                                           +  SizeofSerialNo
                                           +  SizeofBrandName
                                           +  SizeofModelName
                                           +  SizeofEncryptKey
                                           +  SizeofSIMKeys;
    uint16_t CacheMemorySize = 4;
    uint8_t MemChunkSize = 4;
    PDALINKSINFO   LinksInfo;
    std::memset ( &LinksInfo, 0, sizeof ( LinksInfo ) );
    PDASettings  PadSettings;
    std::memset ( &PadSettings, 0, sizeof ( PadSettings ) );
    bool UseCacheMemory = true;
    bool UnicodeSupport = true;

    if ( UseCacheMemory ) {
        InitInfo.Len                    +=  sizeof ( CacheInfo );
        CacheInfo.Command                = 'D';
        CacheInfo.Len                    =  sizeof ( CacheInfo );
        CacheInfo.CacheSize              =  CacheMemorySize;
        CacheInfo.ChunkSize              =  MemChunkSize;
        CacheInfo.MaxPageSize            =  LinksInfo.MaxPageSize;
        CacheInfo.CacheID                =  LinksInfo.CacheID;
        CacheInfo.Terminator             =  0;

    }
    
    if ( UnicodeSupport )
    {
        InitInfo.Len                    +=  sizeof ( PadLangIdInfo );
        PadLangIdInfo.BlockType          =  'L';
        PadLangIdInfo.BlockLen           =  sizeof ( PadLangIdInfo );
        PadLangIdInfo.LangID             =  PadSettings.LangID;
        PadLangIdInfo.ConversionType     =  0;
        PadLangIdInfo.Terminator         =  0;
    }



    return true;
}
