#ifndef SURFERCLIENT_STRUCTS_HPP
# define SURFERCLIENT_STRUCTS_HPP

# include <stdint.h>

# ifndef UID_INFO_CHAR_LEN
# define UID_INFO_CHAR_LEN   24
# endif

typedef struct _FILETIME {
    uint32_t dwLowDateTime;
    uint32_t dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

typedef struct {
    uint8_t  First;
    uint8_t  Last;
    uint8_t  LinkTbl  [256];
    uint8_t  MemIndex [256];
    uint16_t PagesPerCache;
    uint16_t MaxPageSize;
    FILETIME CacheID;

} PDALINKSINFO, * PPDALINKSINFO;

typedef struct _SYSTEMTIME {
    uint16_t wYear;
    uint16_t wMonth;
    uint16_t wDayOfWeek;
    uint16_t wDay;
    uint16_t wHour;
    uint16_t wMinute;
    uint16_t wSecond;
    uint16_t wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

typedef struct {
    uint8_t  Command;
    uint8_t  Len;

    uint8_t  Features[8];

    uint8_t  Terminator;

} PADFEATUREINFO, * PPADFEATUREINFO;

typedef struct {

    uint8_t BlockType;
    uint8_t BlockLen;

    union {
        uint16_t LangID;
        struct {
            uint8_t  LangIDLSB;
            uint8_t  LangIDMSB;
        };
    };
    union {
        uint16_t KeyboardID;
        struct {
            uint8_t  KeyboardIDLSB;
            uint8_t  KeyboardIDMSB;
        };
    };
    union {
        uint16_t ConversionType;
        struct {
            uint8_t  ConversionTypeLSB;
            uint8_t  ConversionTypeMSB;
        };
    };
    uint16_t  Reserved1;

    uint8_t  Terminator;

} LANGIDINFO, * PLANGIDINFO;

typedef struct {

    uint8_t BlockID;

    uint8_t BlockLen;

    uint8_t  UID [UID_INFO_CHAR_LEN + 1];

    uint8_t  Terminator;

} PAGEIDINFO, * PPAGEIDINFO;

typedef struct {
    uint8_t  Command;                                       // MUST BE 'C'
    uint8_t  Len;                                           // MUST BE  11 THE SIZE OF THIS STRUCTURE

    uint8_t  ColorBitDeep;                                  // BIT 0 - 2 MONO, 2BIT, 4BIT, 8BIT  BIT=PALETTE CHANGE SUPPORT

    uint8_t  ScreenWidth;                                   // MULTIPLE OF 32 PIXELS EX. 10 =  320
    uint8_t  ScreenHeight;                                  // MULTIPLE OF 32 PIXELS EX.  5 =  160
    uint8_t  VScreenWidth;                                  // MULTIPLE OF 32 PIXELS EX. 20 =  640
    uint8_t  VScreenHeight;                                 // MULTIPLE OF 32 PIXELS Ex. 32 = 1024  40 = 1280  255 = 8160

    uint8_t  IntegrationLevel;
    uint8_t  CompressMethodSupported;
    uint8_t  LineSpeedSupported;

    uint8_t  Terminator;                                    // MUST BE 0

} PADCAPSINFO, * PPADCAPSINFO;

typedef struct {
    uint8_t  Command;
    uint8_t  SubCommand;

    union {
        uint16_t Version;
        struct {
            uint8_t  MajorLSB;
            uint8_t  MinorMSB;
        };
    };
    uint8_t Action;
    union {
        uint16_t  Len;
        struct {
            uint8_t  LenLSB;
            uint8_t  LenMSB;
        };
    };
    uint8_t Terminator;

} INITINFO, * PINITINFO;


typedef struct {

    uint8_t     Command;
    uint8_t     Len;

    uint8_t     Action;                                     // 'U' - UPDATE OR 'R' - RESET
    union {
        uint16_t  CacheSize;
        struct {
            uint8_t  CacheSizeLSB;
            uint8_t  CacheSizeMSB;
        };
    };
    union {
        uint16_t  MaxPageSize;
        struct {
            uint8_t  MaxPageSizeLSB;
            uint8_t  MaxPageSizeMSB;
        };
    };


    uint8_t     ChunkSize;
    FILETIME    CacheID;
    uint8_t     Terminator;

} CACHEINFO, * PCACHEINFO;

typedef struct {
    long All;
    bool Raw,
         Text,
         Frame,
         Fill,
         Scroll,
         Beacon,
         Task,
         TimeStamp,
         Status,
         Errors;

    bool ProcessChannel,
         EnableSendBeacon,
         SendInitOnStart,
         ClearScreenOnStart;

    int      HostStatus;
    int      HostTimeOut;

    bool     HardwareFlow;
    bool     EnableRTS,
             EnableDTR,
             UseCarrier,
             DirectConnect;

    bool     EnablePenMove,
             EnablePenUp,
             EnablePenClicks;

    bool     EnableScreenPos;

    uint8_t     Features [8];

    uint32_t    ImageCapsRequested;

    uint32_t    LangID;

    bool     EnableTransparency;

} PDASettings, * PPDASettings;


# endif
