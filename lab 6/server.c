#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")


int main()
{
	WSADATA wsas;
	int result;
	WORD wersja;
	wersja = MAKEWORD(2, 0);
	result =  WSAStartup(wersja, &wsas); // za³daowanie biblioteki Winsock 2.0
	if (result)
	{
		printf("Winsock error\n");
		return;
	}
	SOCKET s;
	struct sockaddr_in sa;
	s = socket(AF_INET, SOCK_STREAM, 0); // tworzenie gniazdka internetowego, strumieniowego
	memset((void*)(&sa), 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000); // nr portu, na którym serwer ma nas³uchiwaæ
	sa.sin_addr.s_addr =  htonl(INADDR_ANY); // INADDR_ANY pozwala serwerowi na nas³uchiwanie aktywnoœci we wszystkich interfejsach sieciowych
	result = bind(s, (struct sockaddr FAR*) & sa, sizeof(sa)); // próba dowi¹zania
	if (result == SOCKET_ERROR)
	{
		printf("\nBlad dowi¹zania!");
		return 0;
	}

	result = listen(s, 5); // utworzenie kolejki nadchodz¹cych po³¹czeñ 
	printf("SERVER STARTED");
	SOCKET si;
	struct sockaddr_in sc;
	int lenc;
	for (;;)
	{
		lenc = sizeof(sc);
		si = accept(s, (struct sockaddr FAR*) & sc, &lenc); // deskryptor gniazdka po³¹czenie pierwszej pozycji z kolejki listen
		char buf[80];
		char ipstr[16];
		inet_ntop(AF_INET, &(sc.sin_addr), ipstr, sizeof(ipstr)); // zczytanie adresu ip kilenta
		while (recv(si, buf, 80, 0) > 0)
		{
			if (strcmp(buf, "KONIEC") == 0) // "KONIEC" oznacza koniec obs³ugi po³¹cznia
			{
				printf("\nSERVER CLOSED");
				closesocket(si);
				WSACleanup();
				return 0;
			}
			printf("\n%s: %s", ipstr, buf);
		}
	}
	return 0;
}