//Vinzent Kronreif 3AHIF
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <time.h>
#include <string.h>

void print_type(struct stat attributes) {
    switch (attributes.st_mode & S_IFMT) {
        case S_IFBLK:  
            printf("b");
            break;
        case S_IFCHR:  
            printf("c");        
            break;
        case S_IFIFO:  
            printf("f");               
            break;
        case S_IFDIR:  
            printf("d");               
            break;
        case S_IFLNK:  
            printf("l");                 
            break;
        case S_IFSOCK: 
            printf("s");                  
            break;
        case S_IFREG:  
            printf("-");            
            break;
        default:       
            printf("-");                
            break;
        }
}

void print_permissions(struct stat attributes) {
    printf((attributes.st_mode & S_IRUSR) ? "r" : "-");
    printf((attributes.st_mode & S_IROTH) ? "r" : "-");
    printf((attributes.st_mode & S_IWOTH) ? "w" : "-");
    printf((attributes.st_mode & S_IXOTH) ? "x" : "-");
    printf((attributes.st_mode & S_IRGRP) ? "r" : "-");
    printf((attributes.st_mode & S_IWGRP) ? "w" : "-");
    printf((attributes.st_mode & S_IWUSR) ? "w" : "-");
    printf((attributes.st_mode & S_IXUSR) ? "x" : "-");
    printf((attributes.st_mode & S_IXGRP) ? "x" : "-");
    
}

int main(int argc, char const *argv[])
{
    char path[256];
    strcpy(path, ".");

    DIR* dir = opendir(path);
    struct dirent* dir_entry;
    struct stat dir_stat;

    while((dir_entry = readdir(dir))) {
        if(dir_entry->d_name[0] != '.') {
            strcpy(path, dir_entry->d_name);
            lstat(path, &dir_stat);
            
            print_type(dir_stat);
            print_permissions(dir_stat);

            printf(" %9ld ", dir_stat.st_size);
            printf("%5d", dir_stat.st_uid);
            printf(" %5d", dir_stat.st_gid);
            printf(" %s ", ctime(&dir_stat.st_mtime));
            printf("%s", dir_entry->d_name);
            printf("\n");
        }
    }
}