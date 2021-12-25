//
// Created by ZZY on 2021/12/23.
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
#include<sys/socket.h>
#include<sys/un.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <cerrno>
#include<unistd.h>
#include<iostream>
#include<thread>
#include<map>
#include "../../Utils/strings.h"
//using namespace std;


constexpr int CMD_BUFFER_SIZE = 1024;
char SERVER_SOCK_NAME[] = "server.sock";

std::map<int, void*> shmMap;

void end(const std::string &reason) {
    std::cerr << reason<<std::endl;
    exit(1);
}

void dispatchCommand(std::string command, int sendFd);

void runServer(int connectionFd, int bufferSize);

int createSharedMemoryFrom(void* area, int size);


int main(int argc, char **argv) {
//    int listenFd, connectionFd;
    if (argc != 2)
        end("Usage: <client-sock-name>");
    auto clientName = argv[1];
    char *name = SERVER_SOCK_NAME;
//
//    struct sockaddr_un listenUn, clientUn;
//    socklen_t clientUnSize;
////    if (strlen(name) > sizeof(listenUn.sun_path)) end("Domain Name too long");
//
//    listenFd = socket(AF_UNIX, SOCK_STREAM, 0);
//    if (listenFd < 0) {
//        end("Failed to get file descriptor");
//    }
//    memset(&listenUn, 0, sizeof(listenUn));
//    listenUn.sun_family = AF_UNIX;
//    strcpy(listenUn.sun_path, name);
//    socklen_t size = offsetof(struct sockaddr_un, sun_path) + strlen(name);
//    unlink(name);
//
//    if (bind(listenFd, (struct sockaddr *) &listenUn, size) < 0) end("Command File Descriptor Bind Failed");
//
//    if (listen(listenFd, 20) < 0) end(std::string("Listen on port") + "Failed");
//
//    std::cout<<"Ready"<<std::endl;
//    while (true) {
//        clientUnSize = sizeof(clientUn);
//        if (connectionFd = accept(listenFd, (struct sockaddr *) &clientUn, &clientUnSize) < 0){
//            std::cerr<<"Establish connection failed"<<std::endl;
//            continue;
//        }
//        std::cout<<"Accepted new connection"<<std::endl;
////        std::thread serverThread(runServer,&connectionFd, CMD_BUFFER_SIZE);
//        runServer(&connectionFd, CMD_BUFFER_SIZE);
////        serverThread.join();
//    }
//    close(listenFd);
    struct sockaddr_un serverUn, clientUn;
    socklen_t serverUnLen;
    int listenFd, connectionFd, size;
    char buf[CMD_BUFFER_SIZE];
    int i, n;

    if ((listenFd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        end("Socket Error");
    }

    memset(&serverUn, 0, sizeof(serverUn));
    serverUn.sun_family = AF_UNIX;
    strcpy(serverUn.sun_path, name);
    size = offsetof(struct sockaddr_un, sun_path) + strlen(serverUn.sun_path);
    unlink(name);
    if (bind(listenFd, (struct sockaddr *)&serverUn, size) < 0) end("Bind FD Error");
    printf("UNIX domain socket bound\n");

    if (listen(listenFd, 20) < 0) end("Listen Error");
    std::cout<<"Accepting connections ..."<<std::endl;

    while(1) {
        serverUnLen = sizeof(clientUn);
        if ((connectionFd = accept(listenFd, (struct sockaddr *)&clientUn, &serverUnLen)) < 0){
            perror("accept error");
            continue;
        }
        runServer(connectionFd, 1024);
//        std::thread serverThread(runServer, connectionFd, 1024);
    }
    close(listenFd);
}

void runServer(int connectionFd, int bufferSize){
    char* buffer = new char[bufferSize];
    int recvCount;
    while(1){
        recvCount = read(connectionFd, buffer, bufferSize);
//        std::cout<<"I'm in"<<std::endl;
        if (recvCount < 0){
            std::cerr<<"Receive Error"<<std::endl;
            break;
        }
        if (recvCount == 0){
            std::cerr<<"EOF"<<std::endl;
            break;
        }
        std::cout<<"["<<std::this_thread::get_id()<<"] Received Msg: "<<buffer<<std::endl;
        dispatchCommand(std::string(buffer), connectionFd);
    }
    delete[] buffer;
    close(connectionFd);
}

void dispatchCommand(std::string command, int sendFd){
    if(startsWith(command, "resp")){
        auto response = command.substr(strlen("resp"));
        std::cout<<"Server received response: "<<response<<std::endl;
        if(startsWith(response, "get_int_array_shared")){
            //Shared Memory now is safe to delete, command format: get_int_array_shared <id>
        }
    } else if(startsWith(command, "req")) {
        std::string resp = std::string("resp");
        auto request = command.substr(strlen("req"));
        std::cout<<"Server received request: "<<request<<std::endl;
        if(startsWith(request, "ping")){
            resp = resp + "ping"+"Greetings from server";
            write(sendFd ,resp.c_str(), resp.size());
            return;
        } else if(startsWith(request, "get_int_array_shared")){
            int arraySize = std::stoi(request.substr(strlen("get_int_array_socket")));
            int* array = new int[arraySize];
            array[0] = 114514;
            int id = createSharedMemoryFrom(array, arraySize* sizeof(int));
            resp = resp + "get_int_array_shared"  + std::to_string(id) + ";" + std::to_string(arraySize);
            write(sendFd, resp.c_str(), resp.size());
        }
        else {
            resp = resp + "Unsupported Request";
        }
        write(sendFd, resp.c_str(), resp.size());
    } else {
        std::string resp = "Protocol Error";
        write(sendFd, resp.c_str(), resp.size());
    }
}

int createSharedMemoryFrom(void *area, int size) {
    int randomId = rand() % 114514;
    int shmSize = size + 1024;
    int shmId = shmget(randomId, shmSize, 0666 | IPC_CREAT);
    if (shmId == -1) end("shmget failed");

    void* shmAddr = shmat(shmId, nullptr, 0);
    if(shmAddr == (void*) -1) end("shmat failed");

    memset(shmAddr, 0, shmSize);
    memcpy(shmAddr, area, size);

    if(shmdt(shmAddr) == -1) end("shmdt failed");

    std::cout<<"Shared Memory created"<<std::endl;
    shmMap.insert(std::make_pair(randomId, shmAddr));
    return randomId;
}



#pragma clang diagnostic pop