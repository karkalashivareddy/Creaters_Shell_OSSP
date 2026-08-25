/*
 * Skill-02
 * Interactive Shell - Main Loop, Input Buffer, Keyboard Handling
 *
 * Student Name : Karkala Shiva Reddy
 * Roll Number  : 2520030105
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <signal.h>

#define MAX_INPUT 256
#define PROMPT "minishell> "

static struct termios orig_termios;
static volatile sig_atomic_t running = 1;

void restore_terminal(void)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void signal_handler(int sig)
{
    (void)sig;
    printf("\n");
    restore_terminal();
    printf("Goodbye.\n");
    exit(0);
}

int setup_terminal(void)
{
    struct termios raw;

    if (!isatty(STDIN_FILENO))
        return -1;

    if (tcgetattr(STDIN_FILENO, &orig_termios) < 0)
        return -1;

    raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) < 0)
        return -1;

    return 0;
}

void print_help(void)
{
    printf("Built-in commands:\n");
    printf("  help    - Show this help message\n");
    printf("  pwd     - Print current directory\n");
    printf("  echo    - Print text (echo <text>)\n");
    printf("  clear   - Clear the screen\n");
    printf("  exit    - Exit the shell\n");
    printf("  quit    - Exit the shell\n");
    printf("\nExternal commands are executed via fork()+exec().\n");
}

void run_external(char *args[])
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return;
    }

    if (pid == 0)
    {
        execvp(args[0], args);
        fprintf(stderr, "minishell: command not found: %s\n", args[0]);
        exit(1);
    }
    else
    {
        wait(NULL);
    }
}

int tokenize(char *input, char *args[])
{
    int argc = 0;
    char *token = strtok(input, " \t\n");

    while (token != NULL && argc < 63)
    {
        args[argc++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[argc] = NULL;
    return argc;
}

void process_command(char *input)
{
    char *args[64];
    int argc = tokenize(input, args);

    if (argc == 0)
        return;

    if (strcmp(args[0], "help") == 0)
    {
        print_help();
    }
    else if (strcmp(args[0], "pwd") == 0)
    {
        char cwd[512];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
            printf("%s\n", cwd);
        else
            perror("getcwd failed");
    }
    else if (strcmp(args[0], "echo") == 0)
    {
        for (int i = 1; i < argc; i++)
        {
            if (i > 1) printf(" ");
            printf("%s", args[i]);
        }
        printf("\n");
    }
    else if (strcmp(args[0], "clear") == 0)
    {
        printf("\033[2J\033[H");
    }
    else if (strcmp(args[0], "exit") == 0 || strcmp(args[0], "quit") == 0)
    {
        restore_terminal();
        printf("Goodbye.\n");
        exit(0);
    }
    else
    {
        run_external(args);
    }
}

int main(void)
{
    char buffer[MAX_INPUT];
    int pos = 0;
    int ch;

    if (setup_terminal() < 0)
    {
        fprintf(stderr, "Failed to setup terminal. Using line mode.\n");
        while (running)
        {
            printf(PROMPT);
            if (fgets(buffer, sizeof(buffer), stdin) == NULL)
                break;
            buffer[strcspn(buffer, "\n")] = '\0';
            if (strcmp(buffer, "exit") == 0 || strcmp(buffer, "quit") == 0)
            {
                printf("Goodbye.\n");
                break;
            }
            process_command(buffer);
        }
        return 0;
    }

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    printf("Mini Shell v1.0 (type 'help' for commands, 'exit' to quit)\n");
    printf(PROMPT);
    fflush(stdout);

    while (running)
    {
        ch = getchar();

        if (ch == '\n' || ch == '\r')
        {
            printf("\n");
            if (pos > 0)
            {
                buffer[pos] = '\0';
                process_command(buffer);
                pos = 0;
            }
            printf(PROMPT);
            fflush(stdout);
        }
        else if (ch == 127 || ch == 8)
        {
            if (pos > 0)
            {
                pos--;
                printf("\b \b");
                fflush(stdout);
            }
        }
        else if (ch == 4)
        {
            printf("\n");
            break;
        }
        else if (ch >= 32 && ch < 127)
        {
            if (pos < MAX_INPUT - 1)
            {
                buffer[pos++] = (char)ch;
                putchar(ch);
                fflush(stdout);
            }
        }
    }

    restore_terminal();
    printf("Goodbye.\n");
    return 0;
}
