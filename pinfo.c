#include "headers.h"

char *extract(char *workdirshell)
{
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

    char *toreturn = (char *)malloc(sizeof(char) * 200);

    if (flag)
    {
        strcpy(toreturn, "~");
        strcat(toreturn, temphomedir);
    }
    else
    {
        strcpy(toreturn, temphomedir);
    }
    return toreturn;
}

void pinfocmd(char *argumentList[250], int len)
{
    int cnt = 0;
    int pid;
    char *statpathbuff = (char *)malloc(sizeof(char) * 2000);
    char *execpathbuff = (char *)malloc(sizeof(char) * 2000);
    if (len > 2)
    {
        printf("Invalid Command\n");
        return;
    }
    else if (len == 2)
    {
        pid = atoi(argumentList[1]);
    }
    else
    {
        pid = getpid();
    }

    char *statpath = (char *)malloc(sizeof(char) * 200);
    char *temppath = (char *)malloc(sizeof(char) * 200);

    sprintf(temppath, "/proc/%d/", pid);
    strcpy(statpath, temppath);

    char *execpath = (char *)malloc(sizeof(char) * 200);
    strcpy(execpath, statpath);
    strcat(statpath, "/stat");
    strcat(execpath, "/exe");
    readlink(execpath, execpathbuff, 2000);
    int fd = open(statpath, O_RDONLY);
    ssize_t countvar = read(fd, statpathbuff, 2000);

    if (fd < 0)
    {
        printf("No such process with given pid\n");
        return;
    }
    else
    {
        char *ptr = (char *)malloc(sizeof(char) * 2000);
        char *statpinfo[2000];
        ptr = strtok(statpathbuff, " \t\n");
        while (ptr != NULL)
        {
            statpinfo[cnt++] = ptr;
            ptr = strtok(NULL, " \t\n");
        }
        printf("pid : %s\n", statpinfo[0]);
        if (strcmp(statpinfo[0], statpinfo[7]) == 0)
        {
            printf("Process Status : %s+\n", statpinfo[2]);
        }
        else
        {
            printf("Process Status : %s\n", statpinfo[2]);
        }
        printf("Memory : %s {Virtual Memory} \n", statpinfo[22]);
        printf("Executable Path : %s\n", extract(execpathbuff));
        free(ptr);
    }
    free(statpath);
    free(execpath);
    return;
}