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