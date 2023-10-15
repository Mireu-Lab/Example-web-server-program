#include <iostream>
#include <string>
using namespace std;

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <fstream>

int sockfd;
int connfd;
int port = 80; // Server Output Port
string filePath = "templates/index.html"; // Index.html 파일 상대 Path

void socketBuild(
	// Output Port 
	int port = 8080) {

	// TCP 소켓 생성
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		cerr << "socket() failed" << endl;
		return ;
	}

	// 소켓 바인딩
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		cerr << "bind() failed" << endl;
		return ;
	}

	// listen()
	if (listen(sockfd, 5) == -1) {
		cerr << "listen() failed" << endl;
		return ;
	}
}

void TXRX_Listen(void) {
	// 요청 수신
	struct sockaddr_in client_addr;
	socklen_t client_addr_len = sizeof(client_addr);
	connfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
	if (connfd == -1){
		cerr << "accept() failed" << endl;
		return ;
	}

	// 요청 처리
	char buf[1024];
	int nread = read(connfd, buf, sizeof(buf));
	if (nread == -1) {
		cerr << "read() failed" << endl;
		return ;
	}
}

string htmlFileRead(string filePath = "templates/index.html") {
	ifstream file(filePath); // index.html 파일을 읽기 모드로 열기
	string line = string((istreambuf_iterator<char>(file)), istreambuf_iterator<char>()); // 파일의 내용을 한 줄로 읽기

	file.close(); // 파일을 닫기

	return "HTTP/1.1 200 OK\nContent-Type: text/html\n\n" + line;
}

int main(void) {
	socketBuild(port);

	printf("web access link: 0.0.0.0:%d\n", port);
	printf("web access link: 127.0.0.1:%d\n", port);

	for (;;) {
		TXRX_Listen();
		cout << "The other party viewed it" << endl;

		// 응답 전송
		string response = htmlFileRead();
		ssize_t nwrite = write(connfd, response.c_str(), response.length());
		if (nwrite == -1) {
			cerr << "write() failed" << endl;
			return -1;
		}

	
		// 연결 종료
		close(connfd);
	}

	return 0;
}