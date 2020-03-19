#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#if 0
#include <Winsock2.h>
#include <ws2tcpip.h>
#pragma comment (lib, "Ws2_32.lib")
#endif 

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "MQTTClient.h"
#ifdef __cplusplus
}
#endif

#include "AdvCC.h"
#include "SensorSources.h"

#define DEFAULT_BUFLEN 1'000'000
char gRecvbuf[DEFAULT_BUFLEN] = { 0 };
int Recvbuflen = DEFAULT_BUFLEN;
BlockQHandler gBQ = NULL;

SERVER_RECV_CALLBACK gHandleReceivedMessage = NULL;

class Message_Pointer {
public:
	Message_Pointer(char *topic, char* message, int len) {
		mTopic = _strdup(topic);
		message[len] = 0;
		mMessage = _strdup(message);
		mlen = len;
	}

	~Message_Pointer() {
		if (mTopic != NULL) {
			free(mTopic);
		}
		if (mMessage != NULL) {
			free(mMessage);
		}
	}

	char* mTopic = NULL;
	char* mMessage = NULL;
	int mlen = 0;
};



#if 0
int StartRequestLoop(SERVER_RECV_CALLBACK HandleReceivedMessage, void* callbackPara) {

	WSADATA wsaData;
	int iResult;
	int iSendResult;

	struct addrinfo* conninfo = NULL;
	struct addrinfo hints;



	struct sockaddr_in server_in;
	int sock;
	char buf[32];
	int n;

	SOCKET ServerSocket = INVALID_SOCKET;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo("127.0.0.1", "15038", &hints, &conninfo);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}


	// Create a SOCKET for connecting to server
	ServerSocket = socket(conninfo->ai_family, conninfo->ai_socktype,
		conninfo->ai_protocol);
	if (ServerSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	// Connect to server.
	iResult = connect(ServerSocket, conninfo->ai_addr, (int)conninfo->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ServerSocket);
		ServerSocket = INVALID_SOCKET;
		return 1;
	}

	while (true)
	{
		// Receive
		//if (server->stopServer) break;
		iResult = recv(ServerSocket, recvbuf, recvbuflen, 0);

		if (iResult > 0)
		{
			while (recvbuf[iResult - 1] != '\0') {
				iResult += recv(ServerSocket, recvbuf + iResult, recvbuflen - iResult, 0);
			}
			printf("Bytes received: %d\n", iResult);
			HandleReceivedMessage(recvbuf, iResult, callbackPara);
		}
		else if (iResult == 0)
		{
			printf("Connection closing...\n");
			break;
		}
		else
		{
			int err = WSAGetLastError();

			// WSAEWOULDBLOCK is normal for non-blocking socket.
			if (err != WSAEWOULDBLOCK)
			{
				printf("recv failed with error: %d\n", err);
				closesocket(ServerSocket);
				WSACleanup();
				return 1;
			}
		}
	}

	// shutdown the connection since we're done
	iResult = shutdown(ServerSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ServerSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ServerSocket);
	WSACleanup();
	free(recvbuf);

	return 0;
}
#endif

void delivered(void* context, MQTTClient_deliveryToken dt)
{
	printf("Message with token value %d delivery confirmed\n", dt);
}

int msgarrvd(void* context, char* topicName, int topicLen, MQTTClient_message* message)
{
	int i;
	Message_Pointer *m = new Message_Pointer(topicName, (char *)message->payload, message->payloadlen);
	//printf("Message arrived\n");
	//printf("     topic: %s\n", topicName);
	//printf("     message: %s\n", message->payload);
	BlockQ_Add(gBQ, (void *)&m, sizeof(Message_Pointer*));
	MQTTClient_freeMessage(&message);
	MQTTClient_free(topicName);
	return 1;
}
void connlost(void* context, char* cause)
{
	printf("\nConnection lost\n");
	printf("     cause: %s\n", cause);
}

typedef struct {
	SERVER_RECV_CALLBACK HandleReceivedMessage;
	void* callbackPara;
} sneakPara;


static void *SneakLoop(void* args) {
	sneakPara* para = (sneakPara*)args;
	SERVER_RECV_CALLBACK HandleReceivedMessage = para->HandleReceivedMessage;
	void* callbackPara = para->callbackPara;
	delete para;

	MQTTClient client;
	MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
	int rc;
	int ch;

	gHandleReceivedMessage = HandleReceivedMessage;
	BlockQ_Init(&gBQ, 30);

	MQTTClient_create(&client, "localhost", "AzurePnPClient", MQTTCLIENT_PERSISTENCE_NONE, NULL);
	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;
	MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);
	if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
	{
		printf("Failed to connect, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}

	MQTTClient_subscribe(client, "#", 0);

	Message_Pointer* m;
	do
	{
		BlockQ_Get(gBQ, (void*)& m);
		//printf("topic = %s\n",m->mTopic);
		//printf("message[%d]= %s\n", m->mlen, m->mMessage);
		HandleReceivedMessage(m->mMessage, m->mlen, callbackPara);
		delete m;
		//Sleep(1000);
	} while (true);

	MQTTClient_disconnect(client, 10000);
	MQTTClient_destroy(&client);
	return (void *)rc;
}

int mqttStarted = 0;
void StartMqttSneakLoop(SERVER_RECV_CALLBACK HandleReceivedMessage, void* callbackPara) {
	if (mqttStarted == 0) {
		pthread_t threadHandler;
		sneakPara *para = new sneakPara;
		para->HandleReceivedMessage = HandleReceivedMessage;
		para->callbackPara = callbackPara;
		pthread_create(&threadHandler, NULL, SneakLoop, para);
	}
	mqttStarted = 1;
}


void Parse_RMS(const char *content, long long *interval, double *gap, double data[25]) {
	printf("content = %s\n", content);
	sscanf(content, "%lld,%lg;%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg,%lg", interval, gap
		, &data[0], &data[1], &data[2], &data[3], &data[4], &data[5], &data[6], &data[7]
		, &data[8], &data[9], &data[10], &data[11], &data[12], &data[13], &data[14], &data[15]
		, &data[16], &data[17], &data[18], &data[19], &data[20], &data[21], &data[22], &data[23]
		, &data[24]);

	printf("content = %lld,%.15lg;%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg,%.15lg\n", *interval, *gap
		, data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]
		, data[8], data[9], data[10], data[11], data[12], data[13], data[14], data[15]
		, data[16], data[17], data[18], data[19], data[20], data[21], data[22], data[23]
		, data[24]);
}


