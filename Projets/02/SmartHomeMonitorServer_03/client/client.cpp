#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <crypt.h>
using namespace std;


typedef struct
{
    int type;
    int length;
    char data[1000];
} TLV;

enum TaskType
{
    TASK_TYPE_LOGIN_SECTION1 = 1,
    TASK_TYPE_LOGIN_SECTION1_RESP_OK,
    TASK_TYPE_LOGIN_SECTION1_RESP_ERROR, 
    TASK_TYPE_LOGIN_SECTION2,
    TASK_TYPE_LOGIN_SECTION2_RESP_OK,
    TASK_TYPE_LOGIN_SECTION2_RESP_ERROR,
};


// 连接服务器
void connectToServer(int &cfd, const char *ip, int port)
{
    // 创建套接字
    cfd = socket(AF_INET, SOCK_STREAM, 0);
    if (cfd == -1)
    {
        perror("socket");
        return;
    }

    // 设置服务器地址
    struct sockaddr_in serveraddr;
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr(ip);

    // 连接服务器
    int ret = connect(cfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (ret == -1)
    {
        perror("connect");
        return;
    }
    cout << "Connection established with server.\n";
}

// 发送数据
void sendData(int cfd, char *salt, string &username)
{
    
    string input;
    getline(cin, input);
    
    if (input == "q")
    {
        cout << "Exiting...\n";
        return;
    }

    TLV tlv;
    memset(&tlv, 0, sizeof(tlv));

    if (input == "1")
    {
        username.clear();
        cout << ">> Input username: ";
        
        getline(cin, username);
        tlv.type = 1;
        cout << "type=1, username=" + username << endl;
        strcpy(tlv.data, username.c_str());
        tlv.length = strlen(tlv.data);
    }
    else if (input == "4")
    {
        cout << ">> Input password: ";
        string password;
        getline(cin, password);
        char *encrypted = crypt(password.c_str(), salt);
        tlv.type = 4;
        cout << "type=4, username=" + username + ", encrypted=" + encrypted << endl;
        strcpy(tlv.data, (username + "$" + encrypted).c_str());
        tlv.length = strlen(tlv.data);
    }
    else if (input == "7")
    {
        cout << ">> Input message: ";
        string message;
        getline(cin, message);
        tlv.type = 7;
        cout << "type=7, message=" + message << endl;
        strcpy(tlv.data, message.c_str());
        tlv.length = strlen(tlv.data);
    }
    else
    {
        cout << "Invalid input. Try again.\n";
        return;
    }

    int ret = send(cfd, &tlv, 8 + tlv.length, 0);
    if (ret == -1)
    {
        perror("client send");
        return;
    }
    cout << "Sent " << ret << " bytes: " << tlv.data << endl;
}

// 接收数据
void receiveData(int cfd,char * salt)
{
    char buffer[1024];

    memset(buffer, 0, sizeof(buffer));
    int ret = recv(cfd, buffer, sizeof(buffer) - 1, 0);
    if (ret == -1)
    {
        perror("recv");
        return;
    }
    else if (ret == 0)
    {
        cout << "Server closed the connection.\n";
        close(cfd);
        return;
    }
    buffer[ret] = '\0'; // 确保字符串以'\0'结尾
    cout << "Received " << ret << " bytes: " << buffer << endl;
    TLV *tlv = reinterpret_cast<TLV *>(buffer);
    if(tlv->type == 2){
        memset(salt, 0, sizeof(salt));
        memcpy(salt, tlv->data, tlv->length);
    }
    cout << "Type: " << tlv->type << ", Length: " << tlv->length << ", Data: " << tlv->data << endl;
}

int main()
{
    int cfd;
    const char *serverIP = "192.168.42.128";
    int serverPort = 8100;
    
    connectToServer(cfd, serverIP, serverPort);
    
    string name;
    char salt[128] = {0};
    fd_set set;
    
    while (1)
    {
        
        FD_ZERO(&set);
        FD_SET(STDIN_FILENO, &set);
        FD_SET(cfd, &set);
        
        int ret = select(cfd + 1, &set, NULL, NULL, NULL);
        
        
        cout << ">> Input (1 to send username, 4 to send username and password, 7 to send a message, q to quit): " << endl;
        if (ret == -1)
        {
            perror("select");
            break;
        }

        if (FD_ISSET(cfd, &set))
        {
            receiveData(cfd, salt);
        }

        if (FD_ISSET(STDIN_FILENO, &set))
        {
            sendData(cfd, salt, name);
        }
    }

    close(cfd);
    return 0;
}
