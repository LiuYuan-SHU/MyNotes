#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
	struct sockaddr_in addr1, addr2;
	char *str_ptr;
	char str_arr[20];

	addr1.sin_addr.s_addr = htonl(0x1020304);
	addr2.sin_addr.s_addr = htonl(0x1010101);

	str_ptr = inet_ntoa(addr1.sin_addr);
	strcpy(str_arr, str_ptr);
	printf("Dotted-Decimal notation1: %s \n", str_ptr);

	// 此处我们直接运行inet_ntoa，而不去更新str_ptr
	// 但是str_ptr指向的地址中的内容其实已经被更新了
	inet_ntoa(addr2.sin_addr);
	printf("Dotted-Decimal notation2: %s \n", str_ptr);
	printf("Dotted-Decimal notation3: %s \n", str_arr);

	return 0;
}
