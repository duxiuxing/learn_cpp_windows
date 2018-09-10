#include "stdafx.h"
#include "gtest/gtest.h"

#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

/*
    TestedMethod: 
    Description: 
    Output:
*/
TEST(WinSockTest, IpAddressStringToNumber) {
	TCHAR ip_string[] = _T("192.168.0.1");

	//uint32_t ip_number1 = inet_addr(ip_string);

	in_addr addr;
	uint32_t ip_number = InetPton(AF_INET, ip_string, &addr);
}

/*
TestedMethod:
Description:
Output:
*/
TEST(WinSockTest, IpAddressNumberToString) {
	TCHAR ip_string[INET_ADDRSTRLEN] = {0};
	in_addr addr;
	addr.s_addr = 3245398923;
	LPCTSTR ret = InetNtop(AF_INET, &addr, ip_string, INET_ADDRSTRLEN);
}
