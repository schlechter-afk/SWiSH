#include "headers.h"

extern int firstcd;
void blue(char *str)
{
    printf("\e[34m");
    printf("%s", str);
    printf("\e[97m");
}

void black(char *str)
{
    printf("\e[30m");
    printf("%s", str);
    printf("\e[97m");
}

void blueint(int str)
{
    printf("\e[34m");
    printf("%d", str);
    printf("\e[97m");
}

void red(char *str)
{
    printf("\e[31m");
    printf("%s", str);
    printf("\e[97m");
}

void orange(char *str)
{
    printf("\e[33m");
    printf("%s", str);
    printf("\e[97m");
}

void termcheck()
{
    int status;
    int pid = waitpid(-1, &status, WNOHANG);

    if (pid > 0)
    {
        int pos = 0;
        while (arrbg[pos] != pid)
        {
            pos++;
        }
        if (WIFSTOPPED(status))
        {
            return;
        }
        else
        {
            if (WIFEXITED(status))
            {
                fprintf(stderr, "%s with PID %d exited normally\n", strbg[pos], arrbg[pos]);
            }
            else
            {
                fprintf(stderr, "%s with PID %d exited abnormally\n", strbg[pos], arrbg[pos]);
            }
            arrbg[pos] = -1;
            free(strbg[pos]);
            return;
        }
    }
    else
    {
        return;
    }
}

// int fgRunning = 1;

// void controlhandle()
// {
// }

int main()
{
    stdinptr = dup(0);
    stdoutptr = dup(1);
    fft = 0;
    int cdcalls = 0;
    char *userName;
    char host[300];
    for (int i = 1; i < 50; i++)
    {
        arrbg[i] = -1;
        cpyarrbg[i] = -1;
    }
    for (int i = 0; i < 50; i++)
    {
        assoc[i] = i;
    }

    printf("\e[1;1H\e[2J");
    red("Welcome to SWiSHell !\n\n");

    char workdirshell[300];
    getcwd(homedir, sizeof(homedir));
    gethostname(host, sizeof(host));
    strcpy(prevdir, homedir);

    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    userName = pw->pw_name;

    while (1)
    {
        dup2(stdoutptr, 1);
        dup2(stdinptr, 0);

        // signal(SIGTSTP, SIG_IGN);
        // signal(SIGINT, SIG_IGN);

        signal(SIGTSTP, SIG_IGN);
        signal(SIGINT, SIG_IGN);
        signal(SIGCHLD, termcheck);

        // signal(SIGTSTP, controlhandle);
        getcwd(workdirshell, sizeof(workdirshell));
        char *temphomedir = workdirshell;
        if (strcmp(workdirshell, homedir) == 0)
        {
            temphomedir = "~";
        }
        int flag = 0;
        if (strlen(homedir) < strlen(workdirshell))
        {
            bool truth = true;
            for (int i = 0; i < strlen(homedir); i++)
            {
                if (workdirshell[i] != homedir[i])
                {
                    truth = false;
                    break;
                }
            }
            if (truth)
            {
                char *nextstr;
                nextstr = (char *)malloc(sizeof(char *) * 200);
                for (int i = strlen(homedir); i <= strlen(workdirshell); i++)
                {
                    nextstr[i - strlen(homedir)] = workdirshell[i];
                }
                flag = 1;
                temphomedir = nextstr;
            }
        }

        if (flag)
        {
            printf("\r");
            orange("<");
            orange(userName);
            orange("@");
            orange(host);
            blue(":");
            blue("~");
            blue(temphomedir);
            if (timetaken >= 1)
            {
                blue(" ");
                blue("took");
                blue(" ");
                blueint(timetaken);
                blue(" ");
                blue("seconds");
            }
            blue(">");
            printf(" ");
        }
        else
        {
            printf("\r");
            orange("<");
            orange(userName);
            orange("@");
            orange(host);
            blue(":");
            blue(temphomedir);
            if (timetaken >= 1)
            {
                blue(" ");
                blue("took");
                blue(" ");
                blueint(timetaken);
                blue(" ");
                blue("seconds");
            }
            blue(">");
            printf(" ");
            timetaken = 0;
        }

        ssize_t getbuff = 0;
        char *command = (char *)malloc((sizeof(char) * 200));
        int len;
        dup2(stdoutptr, 1);
        dup2(stdinptr, 0);
        printf("\033[1;30m");

        len = getline(&command, &getbuff, stdin);

        char *historycmmd = (char *)malloc((sizeof(char) * 200));
        strcpy(historycmmd, command);
        int flagtab = 0;
        if (historycmmd[0] == '\t' || historycmmd[0] == ' ' || historycmmd[0] == '\n')
        {
            flagtab = 1;
        }
        if (!flagtab)
        {
            add_command_to_history(command);
        }

        // printf("\033[1;30m");

        if (strlen(command) == 1)
        {
            continue;
        }

        char *copycmd = (char *)malloc((sizeof(char *) * 200));

        strcpy(copycmd, command);

        int flagchk = 1;

        for (int i = 0; i < strlen(copycmd) - 1; i++)
        {
            if (copycmd[i] != ' ' && copycmd[i] != '\t')
            {
                flagchk = 0;
            }
        }

        if (flagchk)
        {
            continue;
        }
        else
        {
            int flag = 0;
            for (int i = 0; i < strlen(command); i++)
            {
                if (command[i] == '|')
                {
                    flag = 1;
                }
            }
            if (flag)
            {
                piping(command);
            }
            else
            {
                execute(command);
            }
        }
    }
    return 0;
}