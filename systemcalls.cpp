#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

int main() {
    int fd=open("example.txt", O_CREAT | O_WRONLY, 0644);
    if(fd==-1) {
        perror("Failed to open file");
        return 1;
    }
    const char* message = "Hello, hi";
    write(fd, message, strlen(message));
    close(fd);
    std::cout<<"File written successfully";

    fd=open("example.txt", O_RDONLY);
    if(fd==-1) {
        perror("File could not be opened for reading.");
        return 1;
    }

    char buffer[128];

    ssize_t byteRead=read(fd, buffer, sizeof(buffer)-1);
    if(byteRead>0) {
        buffer[byteRead]='\0';
        std::cout<<"file contents: "<<buffer<<std::endl;
    }
    close(fd);

    pid_t pid=fork();
    if(pid==-1) {
        perror("Fork failed");
        return 1;
    }
    else if(pid==0) {
        std::cout<<"Child process: PID="<<getpid()<<std::endl;
        exit(0);
    }
    else {
        std::cout<<"Parent process: PID="<<getpid()<<", child PID = "<<pid<<std::endl;
    }

    return 0;
}