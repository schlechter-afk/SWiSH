#include "headers.h"
#include "globals.h"

extern int firstcd;

void die(const char *s)
{
    // perror(s);
    // exit(1);
}

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

struct termios orig_termios;

int default_filtermainka(const struct dirent *dir)
{
    return 1;
}

void disableRawMode()
{
    // printf("in disbale rawmode\n");
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios) == -1)
    {
        die("tcsetattr");
    }
}

void enableRawMode()
{
    if (tcgetattr(STDIN_FILENO, &orig_termios) == -1)
        die("tcgetattr");
    atexit(disableRawMode);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        die("tcsetattr");
}

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

    char *files[250];
    int filecnt = 0;

    char *inp = malloc(sizeof(char) * 100);
    char *inpstore = malloc(sizeof(char) * 250);
    char c;
    while (1)
    {
        // printf("lets start\n");
        setbuf(stdout, NULL);
        // printf("in mid\n");

        dup2(stdoutptr, 1);
        dup2(stdinptr, 0);

        enableRawMode();
        // printf("in groove\n");

        signal(SIGTSTP, SIG_IGN);
        signal(SIGINT, SIG_IGN);
        signal(SIGCHLD, termcheck);

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

        int len;
        // dup2(stdoutptr, 1);
        // dup2(stdinptr, 0);
        printf("\033[1;30m");

        memset(inp, '\0', 100);
        memset(inpstore, '\0', 100);
        int pt = 0;
        while (read(STDIN_FILENO, &c, 1) == 1)
        {
            char *strauto = malloc(sizeof(char) * 250);
            char *asliauto = malloc(sizeof(char) * 250);

            if (iscntrl(c))
            {
                if (c == 10)
                    break;
                else if (c == 27)
                {
                    char buf[3];
                    buf[2] = 0;
                    if (read(STDIN_FILENO, buf, 2) == 2)
                    { // length of escape code
                        printf("\rarrow key: %s", buf);
                    }
                }
                else if (c == 127)
                { // backspace
                    if (pt > 0)
                    {
                        if (inp[pt - 1] == 9)
                        {
                            for (int i = 0; i < 7; i++)
                            {
                                printf("\b");
                            }
                        }
                        inp[--pt] = '\0';
                        printf("\b \b");
                    }
                }
                else if (c == 9)
                { // TAB character

                    int idx = 0;
                    int len = 0;

                    for (int i = strlen(inp) - 1; i >= 0; i--)
                    {
                        if (inp[i] == ' ')
                        {
                            idx = i;
                            break;
                        }
                        else
                        {
                            strauto[len++] = inp[i];
                        }
                    }

                    for (int i = 0; i < len; i++)
                    {
                        asliauto[i] = strauto[len - i - 1];
                    }

                    strauto[len] = '\0';
                    asliauto[len] = '\0';

                    int tilflag = 0;
                    int normflag = 0;

                    char *tempcurrentdirectory = malloc(sizeof(char *) * 200);
                    getcwd(tempcurrentdirectory, 1000);

                    // if (asliauto[0] == '~')
                    // {
                    //     tilflag = 1;
                    //     char *chktilda = malloc(sizeof(char) * 250);

                    //     strcpy(chktilda, homedir);

                    //     strcat(chktilda, asliauto + 1);
                    //     int idx = 0;
                    //     for (int i = strlen(chktilda) - 1; i >= 0; i--)
                    //     {
                    //         if (chktilda[i] == '/')
                    //         {
                    //             idx = i;
                    //             break;
                    //         }
                    //     }
                    //     char *currfi = malloc(sizeof(char) * 250);
                    //     for (int i = 0; i <= idx; i++)
                    //     {
                    //         currfi[i] = chktilda[i];
                    //     }

                    //     chdir(currfi);
                    // }
                    // else
                    // {
                    //     normflag = 1;
                    //     char *chktilda = malloc(sizeof(char) * 250);
                    //     strcpy(chktilda, asliauto);
                    //     int idx = 0;
                    //     for (int i = strlen(chktilda) - 1; i >= 0; i--)
                    //     {
                    //         if (chktilda[i] == '/')
                    //         {
                    //             idx = i;
                    //             break;
                    //         }
                    //     }
                    //     char *currfi = malloc(sizeof(char) * 250);
                    //     for (int i = 0; i <= idx; i++)
                    //     {
                    //         currfi[i] = chktilda[i];
                    //     }

                    //     chdir(currfi);
                    // }

                    struct dirent **list = NULL;
                    int count;
                    char *currdirft = (char *)malloc(sizeof(char) * 100);
                    getcwd(currdirft, 1000);
                    char *global = malloc(sizeof(char) * 250);
                    strcpy(global, currdirft);

                    count = scandir(currdirft, &list, default_filtermainka, alphasort);

                    if (count == -1)
                    {
                        printf("ls: cannot access the given input: No such file or directory");
                        return 0;
                    }

                    int fileslol = 0;

                    for (int i = 0; i < count; i++)
                    {
                        int flag = 1;
                        for (int j = 0; j < strlen(asliauto); j++)
                        {
                            if (list[i]->d_name[j] != asliauto[j])
                            {
                                flag = 0;
                            }
                        }
                        if (flag)
                        {
                            files[fileslol] = malloc(sizeof(char) * 250);
                            strcpy(files[fileslol], list[i]->d_name);
                            fileslol++;
                        }
                    }

                    char *strfile = malloc(sizeof(char) * 250);
                    int index = 0;
                    char *strinchk = malloc(sizeof(char) * 250);
                    int minlen;
                    if (fileslol > 0)
                    {
                        minlen = 1000;
                        for (int i = 0; i < fileslol; i++)
                        {
                            if (strlen(files[i]) < minlen)
                            {
                                minlen = strlen(files[i]);
                            }
                        }
                    }
                    else
                    {
                        continue;
                    }

                    int strinchklen = 0;
                    for (int var = 0; var < minlen; var++)
                    {
                        int flag = 0;
                        for (int i = 0; i < fileslol - 1; i++)
                        {
                            if (files[i][var] != files[i + 1][var])
                            {
                                flag = 1;
                            }
                        }

                        if (!flag)
                        {
                            strinchk[strinchklen++] = files[0][var];
                        }
                        else
                        {
                            break;
                        }
                    }

                    strinchk[strinchklen] = '\0';
                    int appflag = 0;
                    char *tostrin = malloc(sizeof(char) * 250);
                    int tostrilen = 0;

                    // printf("\nasliauto is %s", asliauto);
                    // printf("strchk is %s", strinchk);

                    if (strlen(asliauto) < strlen(strinchk))
                    {
                        appflag = 1;
                        for (int i = strlen(asliauto); i <= strlen(strinchk) - 1; i++)
                        {
                            tostrin[tostrilen++] = strinchk[i];
                        }
                    }
                    tostrin[tostrilen] = '\0';

                    if (fileslol > 1)
                    {
                        printf("\n");
                        for (int i = 0; i < fileslol; i++)
                        {
                            if (strncmp(strinchk, files[i], strlen(strinchk)) == 0)
                            {
                                printf("%s", files[i]);
                                struct stat stats;
                                if (stat(files[i], &stats) == 0)
                                {
                                    if (S_ISDIR(stats.st_mode))
                                    {
                                        printf("/\n");
                                    }
                                    else
                                    {
                                        printf("\n");
                                    }
                                }
                            }
                        }
                        //
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

                        int len;

                        printf("\033[1;30m");
                        printf("%s", inp);
                        if (appflag)
                        {
                            printf("%s", tostrin);
                            strcat(inp, tostrin);
                            pt += tostrilen;
                            // strcpy(inpstore, inp);
                        }
                    }
                    else
                    {
                        char *checkfile = malloc(sizeof(char) * 100);
                        for (int i = strlen(asliauto); i < strlen(files[0]); i++)
                        {
                            printf("%c", files[0][i]);
                        }

                        strcat(inp, tostrin);
                        pt += tostrilen;
                        char *tofilecheck = malloc(sizeof(char) * 250);
                        strcpy(tofilecheck, asliauto);
                        strcat(tofilecheck, tostrin);
                        struct stat stats;
                        if (stat(tofilecheck, &stats) == 0)
                        {
                            if (S_ISDIR(stats.st_mode))
                            {
                                strcat(inp, "/");
                                printf("/");
                            }
                            else
                            {
                                strcat(inp, " ");
                                printf(" ");
                            }
                        }
                        // strcpy(inpstore, inp);
                    }
                    chdir(tempcurrentdirectory);
                }
                else if (c == 4)
                {
                    printf("\n");
                    exit(0);
                }
                else
                {
                    printf("%d\n", c);
                }
            }
            else
            {
                inpstore[pt] = c;
                inp[pt++] = c;
                printf("%c", c);
            }
        }
        if (inp == NULL)
            continue;
        disableRawMode();

        if (strcmp(inp, "") == 0)
        {
            printf("\n");
            continue;
        }
        printf("\n");
        
        mainfunc(inp);

        memset(inp, '\0', 200);
        // printf("inp is %s*\n", inp);
        // printf("successfully executed\n");
    }

    return 0;
}