#include "stdafx.h"
#include "gtest/gtest.h"

#include <WS2tcpip.h>

/*
    TestedMethod: InetPton()
    Description: VS2010及以后版本，可以使用InetPton()来把字符串格式的IP地址转成数字。
*/
TEST(WinSockTest, InetPton)
{
    TCHAR ipString[] = _T("192.168.0.1");

    in_addr ipAddress;
    InetPton(AF_INET, ipString, &ipAddress);
    DWORD ipNumber = ipAddress.s_addr;

    EXPECT_EQ(16820416, ipNumber);
}

/*
    TestedMethod: InetNtop()
    Description: VS2010及以后版本，可以使用InetNtop()来把数字的IP地址转成字符串格式。

*/
TEST(WinSockTest, InetNtop)
{
    DWORD ipNumber = 16820416;

    in_addr ipAddress;
    ipAddress.s_addr = ipNumber;
    TCHAR ipString[INET_ADDRSTRLEN] = {0};
    InetNtop(AF_INET, &ipAddress, ipString, INET_ADDRSTRLEN);

    EXPECT_STREQ(_T("192.168.0.1"), ipString);
}
