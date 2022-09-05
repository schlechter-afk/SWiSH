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

void checkChild()
{
    int st;
    int *status;
    pid_t a;
    status = &st;

    a = waitpid(-1, status, WNOHANG);
    if (a > 0)
    {
        for (int i = 0; i < 50; i++)
        {
            if (arrbg[i] == a)
            {
                arrbg[i] = -1;
                fprintf(stderr, "%s with pid %d exited normally\n", strbg[i], a);
                break;
            }
        }
        // fprintf(stderr, "pid %d exicted Normally\n", a);
    }
}

int bgPid[100] = {1};
char *bgCommand[100];

void addBg(int pid, char *command)
{
    if (!pid)
        return;

    int pos = 99;

    while (!bgPid[pos])
        pos--;

    pos++;

    bgPid[pos] = pid;
    bgCommand[pos] = malloc(strlen(command) + 1);
    strcpy(bgCommand[pos], command);
}

void removeBg(int pid)
{
    if (!pid)
        return;

    for (int i = 1; i < 100; i++)
    {
        if (bgPid[i] == pid)
        {
            bgPid[i] = 0;
            free(bgCommand[i]);
            break;
        }
    }
}

void bgHandler()
{
    int status;
    int pid = waitpid(-1, &status, WNOHANG);

    if (pid > 0)
    {
        int pos = 0;
        while (bgPid[pos] != pid)
            pos++;

        if (WIFSTOPPED(status))
            return;

        fprintf(stderr, "%s with PID %d exited %s\n", bgCommand[pos], bgPid[pos],
                WIFEXITED(status) ? "normally" : "abnormally");

        bgPid[pos] = 0;
        free(bgCommand[pos]);
    }
}

int main()
{
    // checkChild();
    signal(SIGCHLD, bgHandler);
    fft = 0;
    int cdcalls = 0;
    char *userName;
    char host[300];
    for (int i = 1; i < 50; i++)
    {
        arrbg[i] = -1;
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
        checkChild();
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
            orange("<");
            orange(userName);
            orange("@");
            orange(host);
            blue(":");
            blue("~");
            blue(temphomedir);
            if (fft > 1)
            {
                blue(" ");
                blue("took");
                blue(" ");
                blueint(fft);
                blue(" ");
                blue("seconds");
            }
            blue(">");
            printf(" ");
        }
        else
        {
            orange("<");
            orange(userName);
            orange("@");
            orange(host);
            blue(":");
            blue(temphomedir);
            if (fft > 1)
            {
                blue(" ");
                blue("took");
                blue(" ");
                blueint(fft);
                blue(" ");
                blue("seconds");
            }
            blue(">");
            printf(" ");
            fft = 0;
        }

        ssize_t getbuff = 0;
        char *command = (char *)malloc((sizeof(char) * 200));
        int len;
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

        printf("\033[1;30m");

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
            execute(command);
        }
    }
    return 0;
}