#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

char *remove_whitespace(char *str)
{
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ' && str[i] != '\n')
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
    return str;
}

int main()
{
    while (1)
    {
        char input[100];
        printf("$ ");
        fgets(input, sizeof(input), stdin);

        char *buf = input;
        char *token;

        char *args[999];
        int i = 0;
        while ((token = strtok(buf, " ")) != NULL)
        {
            if (buf != NULL)
                buf = NULL;

            args[i++] = remove_whitespace(token);
        }

        int pid;
        if (strcmp(args[0], "exit") == 0)
        {
            exit(0);
        }
        else if (strcmp(args[0], "cd") == 0)
        {
            char *path = args[1];
			if (path == NULL) chdir(getenv("HOME"));
			else chdir(path);
        }
        else
        {
            if ((pid = fork()) == 0)
            {
                if (execvp(args[0], args) != 0)
                {
                    printf("%s not found\n", args[0]);
                    exit(1);
                }
                else
                {
                    exit(0);
                }
            }
            else
            {
                waitpid(pid, 0, 0);
            }
        }

		memset(args, 0, sizeof(args));
    }

    return 0;
}
