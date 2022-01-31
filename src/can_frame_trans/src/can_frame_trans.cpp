#include "can_frame_trans.h"
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;

struct FrameStruct {
    DataRange protTypeRange;
    DataRange dstAddrRange;
    DataRange srcAddrRange;
    DataRange QR_FlagRange;
    DataRange CmdCodeRange;
};

const FrameStruct FRAME_ST = {
    {25,    31},    // protTypeRange
    {17,    24},    // dstAddrRange
    {9,     16},    // srcAddrRange
    {8,     8},     // QR_FlagRange
    {0,     5}      // CmdCodeRange
};

unordered_map<char, string> CHAR_TO_STR = {
    {'0', "0000"},
    {'1', "0001"},
    {'2', "0010"},
    {'3', "0011"},
    {'4', "0100"},
    {'5', "0101"},
    {'6', "0110"},
    {'7', "0111"},
    {'8', "1000"},
    {'9', "1001"},
    {'A', "1010"},
    {'B', "1011"},
    {'C', "1100"},
    {'D', "1101"},
    {'E', "1110"},
    {'F', "1111"},
};


CanFrameTrans::CanFrameTrans() {};
CanFrameTrans::~CanFrameTrans() {};

VOID CanFrameTrans::TransFrame(SINT32 argc, CHAR *argv[])
{
    InitStr(argc, argv);
    GetFrameSt(recvFrameSt, recvBinStr);
    cout << endl << "recv can frame" << endl << endl;
    PrintCanFrameSt(recvFrameSt);

    GetSendBinStr();
    cout << endl << "send can frame" << endl << endl;
    GetFrameSt(sendFrameSt, sendBinStr);
    PrintCanFrameSt(sendFrameSt);
    cout << endl;
    PrintCanFrame(sendBinStr);
}

VOID CanFrameTrans::InitStr(SINT32 argc, CHAR *argv[])
{
    for (SINT32 i = 1; i < argc; i++) {
        for (SINT32 j = 0; argv[i][j] != '\0'; j++) {
            CHAR c = argv[i][j];
            recvBinStr += CHAR_TO_STR[c];
        }
    }
    reverse(recvBinStr.begin(), recvBinStr.end());
    sendBinStr = recvBinStr;
}

VOID CanFrameTrans::GetFrameSt(CanFrameSt &canFrameSt, string &str)
{
    canFrameSt.protType = String2U32(str, FRAME_ST.protTypeRange);
    canFrameSt.Qr_Flag  = String2U32(str, FRAME_ST.QR_FlagRange);
    canFrameSt.srcAddr  = String2U32(str, FRAME_ST.srcAddrRange);
    canFrameSt.dstAddr  = String2U32(str, FRAME_ST.dstAddrRange);
    canFrameSt.CmdCode  = String2U32(str, FRAME_ST.CmdCodeRange);
}

VOID CanFrameTrans::PrintCanFrameSt(CanFrameSt camFrameSt)
{
    printf ("protType = 0x%lx\n", camFrameSt.protType);
    printf ("Qr_Flag  = 0x%lx\n", camFrameSt.Qr_Flag);
    printf ("dstAddr  = 0x%lx\n", camFrameSt.dstAddr);
    printf ("srcAddr  = 0x%lx\n", camFrameSt.srcAddr);
    printf ("CmdCode  = 0x%lx\n", camFrameSt.CmdCode);
}

UINT32 CanFrameTrans::String2U32(string &str, DataRange range)
{
    UINT32 ret = 0;
    UINT32 base = 1;
    for (UINT32 i = range.start; i <= range.end; i++) {
        ret = ret + base * (str[i] - '0');
        base *= 2;
    }
    return ret;
}

VOID CanFrameTrans::GetSendBinStr()
{
    sendBinStr = recvBinStr;
    UINT32 size = FRAME_ST.dstAddrRange.end - FRAME_ST.dstAddrRange.start + 1;
    for (UINT32 i = 0; i < size; i++) {
        sendBinStr[FRAME_ST.dstAddrRange.start + i] = recvBinStr[FRAME_ST.srcAddrRange.start + i];
        sendBinStr[FRAME_ST.srcAddrRange.start + i] = recvBinStr[FRAME_ST.dstAddrRange.start + i];
    }
    sendBinStr[FRAME_ST.QR_FlagRange.start] = '0';
}

VOID CanFrameTrans::PrintCanFrame(string str)
{
    cout << str << endl;
    vector<CHAR> tmpVec;
    for (UINT32 i = 0; i < 8; i++) {
        UINT32 base = 1;
        UINT32 cnt = 0;
        for (UINT32 j = 0; j < 4; j++) {
            UINT32 num = str[4 * i + j] - '0';
            cnt += num * base;
            base *= 2;
        }

        CHAR c = static_cast<CHAR>(cnt < 10 ? cnt + '0' : cnt - 10 + 'A');
        tmpVec.push_back(c);
    }

    while (!tmpVec.empty()) {
        printf("%c", tmpVec.back());
        tmpVec.pop_back();
        printf("%c ", tmpVec.back());
        tmpVec.pop_back();
    }
    cout << endl;
}