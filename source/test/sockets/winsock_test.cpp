#include "stdafx.h"
#include "gtest/gtest.h"

#include <WS2tcpip.h>

/*
    TestedMethod: InetPton() / inet_addr()
    Description:
        - VS2010以后，可以使用InetPton()来把字符串格式的IP地址转成数字
        - VS2005可以使用inet_addr()来进行转换
*/
#if _MSC_VER >= 1600

TEST(WinSockTest, InetPton) {
    TCHAR ipString[] = _T("192.168.0.1");

    in_addr ipAddress;
    InetPton(AF_INET, ipString, &ipAddress);
    DWORD ipNumber = ipAddress.s_addr;

    EXPECT_EQ(16820416, ipNumber);
}

#else // VS2005

TEST(WinSockTest, inet_addr) {
    char ipString[] = "192.168.0.1";

    DWORD ipNumber = inet_addr(ipString);

    EXPECT_EQ(16820416, ipNumber);
}

#endif

/*
    TestedMethod: InetNtop() / inet_ntoa()
    Description:
        - VS2010以后，可以使用InetNtop()来把数字的IP地址转成字符串格式
        - VS2005可以使用inet_ntoa()来进行转换
*/
#if _MSC_VER >= 1600

TEST(WinSockTest, InetNtop) {
    DWORD ipNumber = 16820416;

    in_addr ipAddress;
    ipAddress.s_addr = ipNumber;
    TCHAR ipString[INET_ADDRSTRLEN] = {0};
    InetNtop(AF_INET, &ipAddress, ipString, INET_ADDRSTRLEN);

    EXPECT_STREQ(_T("192.168.0.1"), ipString);
}

#else // VS2005

TEST(WinSockTest, inet_ntoa) {
    DWORD ipNumber = 16820416;

    std::string ipString(inet_ntoa(ipAddress));

    EXPECT_STREQ("192.168.0.1", ipString);
}

/*
    TestedMethod: inet_ntoa()
    Description: inet_ntoa()返回值的有效性问题
        - inet_ntoa()每次返回的char*都指向同一段内存空间；
        - 应该用std::string或者CString这样的封装类来缓存inet_ntoa()的返回值。
*/
TEST(WinSockTest, inet_ntoa_return_value) {
    char* ipString1 = NULL;
    char* ipString2 = NULL;

    std::string ipString11;
    std::string ipString22;

    {
        DWORD ipNumber = 16820416; // 192.168.0.1
        in_addr ipAddress;
        ipAddress.s_addr = ipNumber;
        ipString1 = inet_ntoa(ipAddress);
        ipString11 = inet_ntoa(ipAddress);
        EXPECT_STREQ("192.168.0.1", ipString1);
        EXPECT_STREQ("192.168.0.1", ipString11.c_str());
    }

    {
        DWORD ipNumber = 33597632; // 192.168.0.2
        in_addr ipAddress;
        ipAddress.s_addr = ipNumber;
        ipString2 = inet_ntoa(ipAddress);
        ipString22 = inet_ntoa(ipAddress);
        EXPECT_STREQ("192.168.0.2", ipString2);
        EXPECT_STREQ("192.168.0.2", ipString22.c_str());
    }

    EXPECT_STRNE(ipString11.c_str(), ipString22.c_str());

    // inet_ntoa()的返回值总是指向一段固定的内存空间
    // 所以在进行ipString2转换的时候，ipString1指向的字符串内容也发生了变化
    EXPECT_STREQ(ipString1, ipString2);
    EXPECT_EQ(ipString1, ipString2);
}

#endif
