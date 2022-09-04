#include "headers.h"

extern int firstcd;

void blue(char *str)
{
    printf("\e[34m");
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

int main()
{
    fft = 0;
    int cdcalls = 0;
    char *userName;
    char host[300];

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
        char *command = (char *)malloc((sizeof(char *) * 200));
        int len;
        printf("\033[1;30m");

        len = getline(&command, &getbuff, stdin);

        char *historycmmd = (char *)malloc((sizeof(char *) * 200));
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