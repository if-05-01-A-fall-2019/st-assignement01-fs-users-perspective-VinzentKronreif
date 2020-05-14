//Vinzent Kronreif 3AHIF
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char buffer[256];
    
    if(argc != 3) {
        printf("cpf needs 2 arguments!");
        return -1;
    }

    int srcFile = open(argv[1], O_RDONLY);
    int destFile = open(argv[2], O_WRONLY | O_CREAT);

    int count = read(srcFile, buffer, 256);

    write(destFile, buffer, count);

    return 0;
}