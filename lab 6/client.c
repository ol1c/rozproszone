#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char* argv[])
{
	SOCKET s;
	struct sockaddr_in sa;
	WSADATA wsas;
	WORD wersja;
	wersja = MAKEWORD(2, 0);
	WSAStartup(wersja, &wsas); // za³daowanie biblioteki Winsock 2.0
	s = socket(AF_INET, SOCK_STREAM, 0); // tworzenie gniazdka internetowego, strumieniowego
	memset((void*)(&sa), 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(10000); // nr portu, po którym chcemy siê komunikowaæ
	//sa.sin_addr.s_addr = inet_addr(argv[1]); // adres serwaera
	inet_pton(AF_INET, "127.0.0.1", &(sa.sin_addr)); // adres serwaera (local host)

	int result;
	result = connect(s, (struct sockaddr FAR*) & sa, sizeof(sa)); // próba po³¹czenia z serwerem
	if (result == SOCKET_ERROR)
	{
		printf("\nBlad polaczenia!");
		return 1;
	}
	printf("CLIENT CONNECTED\n");

	int dlug;
	char buf[80];
	for (;;)
	{
		fgets(buf, 80, stdin);
		dlug = strlen(buf); buf[dlug - 1] = '\0';
		send(s, buf, dlug, 0); // przes³anie buffora do serwera
		if (strcmp(buf, "KONIEC") == 0) break; // wpisanie "KONIEC" do buffora zakañcza po³¹czenie tym samym ca³y program
	}
	closesocket(s); // zamkniêcie gniazdka
	WSACleanup(); // zamkniecie biblioteki Winsock
	return 0;
}