#include "headers.h"
extern int firstcd ;
void blue(char *str)
{
    printf("\e[34m");
    printf("%s", str);
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

    // getlogin_r(userName, 200);

    while (1)
    {
        getcwd(workdirshell, sizeof(workdirshell));
        char *temphomedir = workdirshell;

        // printf("THE CWD IS %s\n", homedir);
        // printf("THE WORKDIRSHELL IS %s\n", workdirshell);

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

        // printf("THE WORKDIRSHELL NOW LATESt IS %s\n", workdirshell);

        // printf("%d\n",flag);

        if (flag)
        {
            orange("<");
            orange(userName);
            orange("@");
            orange(host);
            blue(":");
            blue("~");
            blue(temphomedir);
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
            blue(">");
            printf(" ");
        }

        ssize_t getbuff = 0;
        char *command = (char *)malloc((sizeof(char *) * 200));
        int len;
        printf("\033[1;30m");

        len = getline(&command, &getbuff, stdin);

        printf("\033[1;30m");

        // printf("%d", strlen(command));
        // return 0;

        if (strlen(command) == 1)
        {
            continue;
        }

        char *copycmd = (char *)malloc((sizeof(char *) * 200));

        strcpy(copycmd, command);

        int flagchk = 1;

        for (int i = 0; i < strlen(copycmd) - 1; i++)
        {
            if (copycmd[i] != ' ')
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
            // printf("%s\n",command);
            execute(command);
        }
    }
    return 0;
}