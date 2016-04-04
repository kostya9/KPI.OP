#include <io.h>
#include <stdio.h>
#include <winsock2.h>
#include <ctype.h>
#include <limits.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define NO_FLAGS_SET 0
#define PORT 80
#define BUFFER_SIZE 2000
void get_secret(char * output, char * address, SOCKET * psocket)
{
    int receive_size;
    char buffer[BUFFER_SIZE];
    char request[200];
    sprintf(request, "GET %s HTTP/1.1\r\n\r\n", address);
    send(*psocket, request, strlen(request), 0);
    receive_size = recv(*psocket, buffer, BUFFER_SIZE, NO_FLAGS_SET);
    char * word_find = "secret=";
    char * secret = strstr(buffer, word_find);
    int position = 0;
    while(secret[0] != '=')
        secret++;
    secret++;
    while(isalpha(secret[position]))
    {
        output[position] = secret[position];
        position++;
    }
    output[position] = '\0';
}
int get_array(int * output, int size, char * address, SOCKET * psocket)
{
    int position = 0;
    int cur_num;
    int receive_size;
    int content_size;
    char buffer[BUFFER_SIZE];
    char * buffer_pos = buffer;
    char request[200];
    sprintf(request, "GET %s HTTP/1.1\r\n\r\n", address);
    send(*psocket, request, strlen(request), 0);
    receive_size = recv(*psocket, buffer, BUFFER_SIZE, NO_FLAGS_SET);
    buffer[receive_size] = '\0';
    char * word_find = "Content-Length:";
    buffer_pos = strstr(buffer, word_find);
    sscanf(buffer_pos, "Content-Length: %i", &content_size);
    while(buffer_pos[0] != '\n')
        buffer_pos++;
    buffer_pos+=3;
    char * token = strtok(buffer_pos, " ");
    while(token != NULL)
    {
        sscanf(token, "%i", &cur_num);
        output[position] = cur_num;
        position++;
        token = strtok(NULL, " ");
    }
    return position;
}
int sort(int arr[], int size)
{
    for(int sorted = 1; sorted < size; sorted++)
    {
        int cur = sorted;
        while(cur > 0 && arr[cur] < arr[cur - 1])
        {
            int temp = arr[cur];
            arr[cur] = arr[cur - 1];
            arr[cur - 1] = temp;
            cur--;
        }
    }
}
int post_array(char * output, char * address, int * arr, int size, SOCKET * psocket)
{
    int position = 0;
    int cur_num;
    int receive_size;
    char array_str[100] = "";
    for(int i = 0; i < size; i++)
    {
        char temp[10];
        itoa(arr[i], temp, 10);
        strcat(temp, " ");
        strcat(array_str, temp);
    }
    char result[200];
    sprintf(result, "result=%s", array_str);
    result[strlen(result) - 1] = '\0';
    char request[200];
    sprintf(request, "POST %s HTTP/1.1\r\n"
            "Content-length: %d\r\n\r\n"
            "%s", address, strlen(result), result);
    send(*psocket, request, strlen(request), 0);
    receive_size = recv(*psocket, output, BUFFER_SIZE, NO_FLAGS_SET);
    return receive_size;

}
int main(int argc , char *argv[])
{
    int receive_size;
    WSADATA wsa;
    SOCKET s;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    struct hostent *he;
    char * hostname = "pb-homework.appspot.com"; // web-site address
    char * var = "/var/3";
    char * cur_address[100];
    struct in_addr **addr_list;
    struct in_addr *addr;
    char ip[100];
    char buffer[BUFFER_SIZE];

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        return 1;

    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    if ( (he = gethostbyname( hostname ) ) == NULL)
    {
        printf("gethostbyname failed : %d" , WSAGetLastError());
        return 1;
    }
        //Cast the h_addr_list to in_addr , since h_addr_list also has the ip address in long format only
    addr_list = (struct in_addr **) he->h_addr_list;

    for(int i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        addr = addr_list[i];
    }

    memset(&recvSockAddr, 0, sizeof(recvSockAddr));
    recvSockAddr.sin_addr = *addr;
    recvSockAddr.sin_family = AF_INET;
    recvSockAddr.sin_port = htons( PORT );

    recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(recvSocket == INVALID_SOCKET)
	{
		printf("ERROR: socket unsuccessful\r\n");
		system("pause");
		return 0;
	}
    // Connect
    if(connect(recvSocket,(SOCKADDR*)&recvSockAddr,sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        printf("ERROR: socket could not connect\r\n");
        closesocket(recvSocket);
        WSACleanup();
        return 0;
    }

    strcpy(cur_address, hostname);
    strcat(cur_address, var);
    get_secret(buffer, cur_address, &recvSocket);
    printf("The secret is - %s\n", buffer);

    sprintf(cur_address, "%s?secret=%s", cur_address, buffer);
    int arr[100];
    int arr_size = get_array(arr, 100, cur_address, &recvSocket);
    puts("Received array : ");
    for(int i = 0; i < arr_size; i++)
        printf("%3i", arr[i]);

    puts("");
    sort(arr, arr_size);
    puts("Sorted array : ");
    for(int i = 0; i < arr_size; i++)
        printf("%3i", arr[i]);
    puts("");
    strcpy(cur_address, hostname);
    strcat(cur_address, var);
    receive_size = post_array(buffer, cur_address, arr, arr_size, &recvSocket);
    buffer[receive_size] = '\0';
    puts("\nI received: \n");
    puts(buffer);

    system("pause");
    closesocket(s);

    WSACleanup();

    return 0;
}
