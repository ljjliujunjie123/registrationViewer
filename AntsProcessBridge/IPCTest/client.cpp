//
// Created by ZZY on 2021/12/23.
//
#include <string>
#include<sys/socket.h>
#include<sys/un.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include <cerrno>
#include<vector>
#include<unistd.h>
#include<iostream>
#include <thread>
#include "../../Utils/strings.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
constexpr char CLIENT_SOCK_NAME[] = "client.sock";

void end(const std::string& reason){
    std::cerr<<reason<<std::endl;
    exit(1);
}

void dispatchCommand(std::string command, int sendFd);

void* openSharedMemory(int key, size_t size);

void handleIntArraySharedMemory(int key, int size);

void split(const std::string &s, std::vector<std::string> &tokens, const std::string &delimiters);

void runClient(int* fd, int bufferSize){
    std::unique_ptr<char> buffer(new char[bufferSize]);
    while(true){
        int recvCount = read(*fd, buffer.get(), bufferSize);
        if (recvCount < 0){
            std::cerr<<"Client: Receive Resp Error"<<std::endl;
            break;
        }
        if (recvCount == 0){
            std::cerr<<"EOF"<<std::endl;
            break;
        }
        std::cout<<"["<<std::this_thread::get_id()<<"] Received Command: "<<buffer<<std::endl;
    }
}

int main(int argc, char** argv){
    signal(SIGPIPE, SIG_IGN);
    if(argc != 2)
        end("Usage: <server-sock-name>");
    auto serverName = argv[1];
    char* name = const_cast<char *>(CLIENT_SOCK_NAME);

    struct sockaddr_un clientUn, serverUn;
    int clientFd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(clientFd < 0 ) {
        end("Client FD failed to get");
    }
    memset(&clientUn, 0, sizeof(clientUn));
    clientUn.sun_family = AF_UNIX;
    strcpy(clientUn.sun_path, name);
    socklen_t size = offsetof(struct sockaddr_un, sun_path) + strlen(clientUn.sun_path);
    unlink(name);
    if(bind(clientFd, (struct sockaddr*) &clientUn, size) < 0) end("Client Socket Bind failed");

    memset(&serverUn, 0, sizeof(serverUn));
    serverUn.sun_family = AF_UNIX;
    strcpy(serverUn.sun_path, serverName);
    size = offsetof(struct sockaddr_un, sun_path) + strlen(clientUn.sun_path);
    if (connect(clientFd, (struct sockaddr*) &serverUn, size) < 0) end("Server Socket Connect failed");
    std::thread clientThread(runClient,&clientFd, 1024);
    std::string command1 = "reqping";
    write(clientFd, command1.c_str(), command1.size());
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::string command2 = "reqget_int_array_shared114514";
    write(clientFd, command2.c_str(), command2.size());
    clientThread.join();
    close(clientFd);
}

void dispatchCommand(std::string command, int sendFd){
    if(startsWith(command, "resp")){
        auto response = command.substr(strlen("resp"));
        std::cout<<"Client received response: "<<response<<std::endl;
        if(startsWith(response, "ping")){
            std::cout<<"Client get PING from server: "<<response.substr(strlen("ping"))<<std::endl;
        } else if (startsWith(response, "get_int_array_shared")){
            auto argStr = response.substr(strlen("get_int_array_shared"));
            std::vector<std::string> args;
            split(argStr, args, ";");
            handleIntArraySharedMemory(std::stoi(args[0]), std::stoi(args[1]));
        }
    }
}

void handleIntArraySharedMemory(int key, int size){
    std::cout<<"handleIntArraySharedMemory"<<key<<" "<<size<<std::endl;
    int* array = (int* )openSharedMemory(key, size * sizeof(int));
    std::cout<<"Got Int Array of size "<<size<<", first element "<<array[0]<<std::endl;
}

void* openSharedMemory(int key, size_t size){
    int shmId = shmget(key, size+256, 0666 | IPC_CREAT);
    if (shmId == -1) end("shmget failed");

    void* shmAddr = shmat(shmId, nullptr, 0);
    if(shmAddr == (void*) -1) end("shmat failed");

    void* target = new char[size+512];
    memset(target, 0, size+512);

    memcpy(target, shmAddr, size + 256);

    if(shmdt(shmAddr) == -1) end("shmdt failed");

    if(shmctl(shmId, IPC_RMID, 0) == -1) end("shmctl delete failed");

    return target;
}

void split(const std::string &s, std::vector<std::string> &tokens, const std::string &delimiters = " ") {
    std::string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    std::string::size_type pos = s.find_first_of(delimiters, lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos) {
        tokens.push_back(s.substr(lastPos, pos - lastPos));
    }
}

#pragma clang diagnostic pop