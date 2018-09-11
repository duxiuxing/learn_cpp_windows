#include "stdafx.h"
#include "gtest/gtest.h"

#include <WS2tcpip.h>

/*
    TestedMethod:
    Description:
    Output:
*/
TEST(WinSockTest, IpAddressStringToNumber) {
    DWORD ip_expect = 16820416;
    DWORD ip_number = 0;

#if _MSC_VER >= 1600
    TCHAR ip_string[] = _T("192.168.0.1");

    in_addr ip_address;
    InetPton(AF_INET, ip_string, &ip_address);
    ip_number = ip_address.s_addr;
#else // VS2005
    char ip_string[] = "192.168.0.1";
    ip_number = inet_addr(ip_string);
#endif

    EXPECT_EQ(ip_expect, ip_number);
}

/*
    TestedMethod:
    Description:
    Output:
*/
TEST(WinSockTest, IpAddressNumberToString) {
    DWORD ip_number = 16820416;
    in_addr ip_address;
    ip_address.s_addr = ip_number;

#if _MSC_VER >= 1600
    TCHAR ip_string[INET_ADDRSTRLEN] = {0};
    InetNtop(AF_INET, &ip_address, ip_string, INET_ADDRSTRLEN);
#else // VS2005
    CString ip_string(inet_ntoa(ip_address));
#endif

    EXPECT_STREQ(_T("192.168.0.1"), ip_string);
}

/*
    TestedMethod:
    Description:
    Output:
*/
#if _MSC_VER == 1400 // VS2005
TEST(WinSockTest, inet_ntoa) {
    char* ip_string1 = NULL;
    char* ip_string2 = NULL;

    std::string ip_string11;
    std::string ip_string22;

    {
        DWORD ip_number = 16820416; // 192.168.0.1
        in_addr ip_address;
        ip_address.s_addr = ip_number;
        ip_string1 = inet_ntoa(ip_address);
        ip_string11 = inet_ntoa(ip_address);
        EXPECT_STREQ("192.168.0.1", ip_string1);
        EXPECT_STREQ("192.168.0.1", ip_string11.c_str());
    }

    {
        DWORD ip_number = 33597632; // 192.168.0.2
        in_addr ip_address;
        ip_address.s_addr = ip_number;
        ip_string2 = inet_ntoa(ip_address);
        ip_string22 = inet_ntoa(ip_address);
        EXPECT_STREQ("192.168.0.2", ip_string2);
        EXPECT_STREQ("192.168.0.2", ip_string22.c_str());
    }

    EXPECT_STRNE(ip_string11.c_str(), ip_string22.c_str());

    // inet_ntoa()的返回值总是指向一段固定的内存空间
    EXPECT_STREQ(ip_string1, ip_string2);
    EXPECT_EQ(ip_string1, ip_string2);
}
#endif
