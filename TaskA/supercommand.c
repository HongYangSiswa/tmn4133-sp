#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Function prototypes
void file_operations();
void directory_operations();
void start_keylogger();
void stop_keylogger();

int main()
{

    int choice;

    while (1)
    {
        printf("=======================\n");
        printf("Supercommand Menu:\n");
        printf("1. File operations\n");
        printf("2. Directory operations\n");
        printf("3. Keylogger\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        printf("\n");

        switch (choice)
        {
        case 1:
            file_operations();
            break;
        case 2:
            directory_operations();
            break;
        case 3:
            start_keylogger();
            break;
        case 4:
            exit(0);
        default:
            printf("[-] Invalid choice. Please try again.\n");
        }

        printf("\n");
    }

    return 0;
}


void file_operations()
{
    int choice;
    char filename[256];
    int fd;
    char buffer[1024];
    ssize_t bytes;

    printf("\n");

    printf("File Operations Menu:\n");
    printf("1. Create/Open a new file\n");
    printf("2. Change the file permissions\n");
    printf("3. Read from a file\n");
    printf("4. Write to a file\n");
    printf("5. Remove or delete a file\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("\n");

    switch (choice)
    {
    case 1:
        printf("Enter the filename: ");
        scanf("%s", filename);

        // Check if the directory exists, if not create it
        char *dir = strdup(filename);
        char *last_slash = strrchr(dir, '/');
        if (last_slash != NULL)
        {
            *last_slash = '\0';
            struct stat st = {0};
            if (stat(dir, &st) == -1)
            {
                if (mkdir(dir, 0755) == -1)
                {
                    perror("[-] Error creating directory");
                    free(dir);
                    return;
                }
                else
                {
                    printf("[+] Directory %s created successfully.\n", dir);
                }
            }
        }
        free(dir);

        // Create/Open the file
        fd = open(filename, O_CREAT | O_RDWR, 0644);
        if (fd == -1)
        {
            perror("[-] Error opening/creating file");
        }
        else
        {
            printf("[+] File %s created/opened successfully.\n", filename);
            close(fd);
        }
        break;
    case 2:
        printf("Enter the filename: ");
        scanf("%s", filename);
        printf("Enter the new permissions (in octal): ");
        int permissions;
        scanf("%o", &permissions);

        // Validate the octal permission
        if (permissions < 0 || permissions > 0777)
        {
            perror("[-] Invalid permissions. Please enter a value between 000 and 777.\n");
        }
        if (chmod(filename, permissions) == -1)
        {
            perror("[-] Error changing file permissions");
        }
        else
        {
            printf("[+] Permissions of file %s changed successfully.\n", filename);
        }
        break;
    case 3:
        printf("Enter the filename: ");
        scanf("%s", filename);
        fd = open(filename, O_RDONLY);
        if (fd == -1)
        {
            perror("[-] Error opening file");
        }
        else
        {
            bytes = read(fd, buffer, sizeof(buffer) - 1);
            if (bytes == -1)
            {
                perror("[-] Error reading file");
            }
            else
            {
                buffer[bytes] = '\0';
                printf("File contents:\n%s\n", buffer);
            }
            close(fd);
        }
        break;
    case 4:
        printf("Enter the filename: ");
        scanf("%s", filename);
        fd = open(filename, O_WRONLY | O_APPEND);
        if (fd == -1)
        {
            perror("[-] Error opening file");
        }
        else
        {
            printf("Enter the text to write: ");
            scanf(" %[^\n]", buffer);
            bytes = write(fd, buffer, strlen(buffer));
            if (bytes == -1)
            {
                perror("[-] Error writing to file");
            }
            else
            {
                printf("[+] Text written to file successfully.\n");
            }
            close(fd);
        }
        break;
    case 5:
        printf("Enter the filename: ");
        scanf("%s", filename);
        if (remove(filename) == -1)
        {
            perror("[-] Error deleting file");
        }
        else
        {
            printf("[+] File %s deleted successfully.\n", filename);
        }
        break;
    default:
        printf("[-] Invalid choice. Please try again.\n");
    }
}