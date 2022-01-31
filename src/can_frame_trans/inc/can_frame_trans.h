#ifndef CAN_FRAME_TRANS_H
#define CAN_FRAME_TRANS_H
#include "public_typedef.h"
#include <iostream>

struct CanFrameSt {
    UINT32 protType;// 协议类型
    UINT32 dstAddr;// 目的地址
    UINT32 srcAddr;// 源地址
    UINT32 Qr_Flag;// QR标志位
    UINT32 CmdCode;// 命令字高位
};

struct DataRange {
    UINT32 start;
    UINT32 end;
};

class CanFrameTrans {
public:
    CanFrameTrans();
    ~CanFrameTrans();
    VOID TransFrame(SINT32 argc, CHAR *argv[]);
private:
    VOID   InitStr(SINT32 argc, CHAR *argv[]);
    VOID   GetFrameSt(CanFrameSt &canFrameSt, std::string &str);
    VOID   PrintCanFrameSt(CanFrameSt camFrameSt);
    UINT32 String2U32(std::string &str, DataRange range);
    VOID GetSendBinStr();
    VOID PrintCanFrame(std::string str);

    std::string recvBinStr = "";
    std::string sendBinStr = std::string(32, '0');
    CanFrameSt recvFrameSt = {0};
    CanFrameSt sendFrameSt = {0};
};

#endif // CAN_FRAME_TRANS_H