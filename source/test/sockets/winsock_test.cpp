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
    TCHAR ip_string[] = _T("192.168.0.1");

    in_addr ip_address;
    InetPton(AF_INET, ip_string, &ip_address);
    DWORD ip_number = ip_address.s_addr;

    EXPECT_EQ(16820416, ip_number);
}

#else // VS2005

TEST(WinSockTest, inet_addr) {
    char ip_string[] = "192.168.0.1";

    DWORD ip_number = inet_addr(ip_string);

    EXPECT_EQ(16820416, ip_number);
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
    DWORD ip_number = 16820416;

    in_addr ip_address;
    ip_address.s_addr = ip_number;
    TCHAR ip_string[INET_ADDRSTRLEN] = {0};
    InetNtop(AF_INET, &ip_address, ip_string, INET_ADDRSTRLEN);

    EXPECT_STREQ(_T("192.168.0.1"), ip_string);
}

#else // VS2005

TEST(WinSockTest, inet_ntoa) {
    DWORD ip_number = 16820416;

    std::string ip_string(inet_ntoa(ip_address));

    EXPECT_STREQ("192.168.0.1", ip_string);
}

/*
    TestedMethod: inet_ntoa()
    Description: inet_ntoa()返回值的有效性问题
        - inet_ntoa()每次返回的char*都指向同一段内存空间；
        - 应该用std::string或者CString这样的封装类来缓存inet_ntoa()的返回值。
*/
TEST(WinSockTest, inet_ntoa_return_value) {
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
    // 所以在进行ip_string2转换的时候，ip_string1指向的字符串内容也发生了变化
    EXPECT_STREQ(ip_string1, ip_string2);
    EXPECT_EQ(ip_string1, ip_string2);
}

#endif
