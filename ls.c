#include "headers.h"
#include <stdlib.h>
#include <locale.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

char *global;

void printstat(struct dirent **list, int count)
{
    long long int total = 0;
    struct stat stats;
    char *curr = (char *)malloc(sizeof(char) * 250);

    for (int i = 0; i < count; i++)
    {
        strcpy(curr, global);
        strcat(curr, "/");
        strcat(curr, list[i]->d_name);
        int ret = stat(curr, &stats);
        if (ret != -1)
        {
            total += stats.st_blocks;
        }
    }

    printf("total %lld\n", total / 2);

    for (int i = 0; i < count; i++)
    {
        strcpy(curr, global);
        strcat(curr, "/");
        strcat(curr, list[i]->d_name);
        stat(curr, &stats);
        if (S_ISDIR(stats.st_mode))
            printf("d");
        else
            printf("-");

        if (stats.st_mode & S_IRUSR)
            printf("r");
        else
            printf("-");

        if (stats.st_mode & S_IWUSR)
            printf("w");
        else
            printf("-");

        if (stats.st_mode & S_IXUSR)
            printf("x");
        else
            printf("-");

        if (stats.st_mode & S_IRGRP)
            printf("r");
        else
            printf("-");

        if (stats.st_mode & S_IWGRP)
            printf("w");
        else
            printf("-");

        if (stats.st_mode & S_IXGRP)
            printf("x");
        else
            printf("-");

        if (stats.st_mode & S_IROTH)
            printf("r");
        else
            printf("-");

        if (stats.st_mode & S_IWOTH)
            printf("w");
        else
            printf("-");

        if (stats.st_mode & S_IXOTH)
            printf("x");
        else
            printf("-");
        printf(" %ld ", stats.st_nlink);                  // Number of hard links
        printf("%s ", (getpwuid(stats.st_uid))->pw_name); // owner name
        printf("%s ", (getgrgid(stats.st_gid))->gr_name); // group name

        printf("%ld ", stats.st_size); // Total size, in bytes
        char last_mod_time[16];
        strftime(last_mod_time, 14, "%h %d %H:%M", localtime(&stats.st_mtime)); // Time of last modification
        printf("%s ", last_mod_time);
        if (S_ISDIR(stats.st_mode)) // Blue for directory
        {
            printf("\e[34m%s\e[30m", list[i]->d_name);
            printf("\n");
        }
        else if (stats.st_mode & S_IXUSR) // Greenish for executables
        {
            printf("\e[0;33m%s\e[30m", list[i]->d_name);
            printf("\n");
        }
        else if (strstr(list[i]->d_name, ".zip") || strstr(list[i]->d_name, "gz") || strstr(list[i]->d_name, "xz")) // Red for archive files
        {
            printf("\e[0;31m%s\e[30m", list[i]->d_name);
            printf("\n");
        }
        else if (strstr(list[i]->d_name, ".jpg") || strstr(list[i]->d_name, ".jpeg") || strstr(list[i]->d_name, ".png")) // Magenta for image files
        {
            printf("\e[0;35m%s\e[30m", list[i]->d_name);
            printf("\n");
        }
        else
        {
            printf("%s\n", list[i]->d_name);
        }
    }
}

void printstatfile(char *list, char *name)
{
    struct stat stats;
    if (stat(list, &stats) == 0)
    {
        if (S_ISDIR(stats.st_mode))
            printf("d");
        else
            printf("-");

        if (stats.st_mode & S_IRUSR)
            printf("r");
        else
            printf("-");

        if (stats.st_mode & S_IWUSR)
            printf("w");
        else
            printf("-");

        if (stats.st_mode & S_IXUSR)
            printf("x");
        else
            printf("-");

        if (stats.st_mode & S_IRGRP)
            printf("r");
        else
            printf("-");

        if (stats.st_mode & S_IWGRP)
            printf("w");
        else
            printf("-");

        if (stats.st_mode & S_IXGRP)
            printf("x");
        else
            printf("-");

        if (stats.st_mode & S_IROTH)
            printf("r");
        else
            printf("-");

        if (stats.st_mode & S_IWOTH)
            printf("w");
        else
            printf("-");

        if (stats.st_mode & S_IXOTH)
            printf("x");
        else
            printf("-");
        printf(" ");
        printf("%ld ", stats.st_nlink);                   // Number of hard links
        printf("%s ", (getpwuid(stats.st_uid))->pw_name); // owner name
        printf("%s ", (getgrgid(stats.st_gid))->gr_name); // group name

        printf("%ld ", stats.st_size); // Total size, in bytes
        char last_mod_time[16];
        strftime(last_mod_time, 14, "%h %d %H:%M", localtime(&stats.st_mtime)); // Time of last modification
        printf("%s ", last_mod_time);

        printf("%s\n", name);
    }
}

void colorprint(char *glob, struct dirent **list, int count)
{
    struct stat stats;
    char *curr = (char *)malloc(sizeof(char) * 250);
    for (int i = 0; i < count; i++)
    {
        strcpy(curr, glob);
        strcat(curr, "/");
        strcat(curr, list[i]->d_name);
        stat(curr, &stats);
        if (S_ISDIR(stats.st_mode)) // Blue for directory
        {
            printf("\e[34m%s\e[30m", list[i]->d_name);
            printf("\n");
        }
        else if (stats.st_mode & S_IXUSR) // Greenish for executables
        {
            printf("\e[0;33m%s\e[30m", list[i]->d_name);
            printf("\n");
        }
        else if (strstr(list[i]->d_name, ".zip") || strstr(list[i]->d_name, "gz") || strstr(list[i]->d_name, "xz")) // Red for archive files
        {
            printf("\e[0;31m%s\e[30m", list[i]->d_name);
            printf("\n");
        }
        else if (strstr(list[i]->d_name, ".jpg") || strstr(list[i]->d_name, ".jpeg") || strstr(list[i]->d_name, ".png")) // Magenta for image files
        {
            printf("\e[0;35m%s\e[30m", list[i]->d_name);
            printf("\n");
        }
        else
        {
            printf("%s\n", list[i]->d_name);
        }
    }
}

int default_filter(const struct dirent *dir)
{
    return (dir->d_name[0] != '.');
}

int default_filter2(const struct dirent *dir)
{
    return 1;
}

void lscmd(char *argumentList[250], int len)
{
    setlocale(LC_ALL, "");
    if (len == 1 || strcmp(argumentList[1], ".") == 0)
    {
        struct dirent **list = NULL;
        int count;
        char *currdirft = (char *)malloc(sizeof(char) * 100);
        getcwd(currdirft, 1000);
        global = malloc(sizeof(char) * 250);
        strcpy(global, currdirft);

        count = scandir(currdirft, &list, default_filter, alphasort);

        if (count == -1)
        {
            printf("ls: cannot access the given input: No such file or directory");
            return;
        }
        printf("%s\n", global);
        colorprint(global, list, count);
    }
    else
    {
        if (argumentList[1][0] == '~')
        {
            struct dirent **list = NULL;
            int count;

            char *chktilda = (char *)malloc(sizeof(char *) * 200);
            strcpy(chktilda, homedir);
            strcat(chktilda, argumentList[1] + 1);

            if (access(chktilda, F_OK))
            {
                printf("No such file/directory\n");
                return;
            }

            global = malloc(sizeof(char) * 250);
            strcpy(global, chktilda);

            count = scandir(chktilda, &list, default_filter, alphasort);

            if (count == -1)
            {
                printf("ls: cannot access the given input: No such file or directory");
                return;
            }

            colorprint(global, list, count);
            free(global);
            return;
        }
        else if (strcmp(argumentList[1], "-a") == 0)
        {
            if (strcmp(argumentList[2], "-l") == 0 && len == 3)
            {
                struct dirent **list = NULL;
                char *currdirft = (char *)malloc(sizeof(char) * 100);
                getcwd(currdirft, 1000);
                global = malloc(sizeof(char) * 250);
                strcpy(global, currdirft);

                if (access(currdirft, F_OK))
                {
                    printf("No such file/directory\n");
                    return;
                }

                int count = scandir(currdirft, &list, default_filter2, alphasort);

                if (count == -1)
                {
                    printf("ls: cannot access the given input: No such file or directory");
                    return;
                }
                printstat(list, count);
                return;
            }
            else if (strcmp(argumentList[2], "-l") == 0 && len == 4)
            {
                struct dirent **list = NULL;
                char *currdirft = (char *)malloc(sizeof(char) * 100);
                if (argumentList[3][0] != '/' && argumentList[3][0] != '~')
                {
                    getcwd(currdirft, 1000);
                    strcat(currdirft, "/");
                    strcat(currdirft, argumentList[3]);
                }
                else if (argumentList[3][0] == '~')
                {
                    strcpy(currdirft, homedir);
                    strcat(currdirft, argumentList[3] + 1);
                }
                else
                {
                    strcpy(currdirft, argumentList[3]);
                }
                global = malloc(sizeof(char) * 250);
                strcpy(global, currdirft);

                if (access(currdirft, F_OK))
                {
                    printf("No such file/directory\n");
                    return;
                }
                else
                {
                    int count = scandir(currdirft, &list, default_filter2, alphasort);
                    if (count == -1)
                    {
                        printstatfile(currdirft, argumentList[3]);
                    }
                    else
                    {
                        printstat(list, count);
                    }
                    return;
                }
            }
            else if (len == 3)
            {
                struct dirent **list = NULL;
                char *currdirft = (char *)malloc(sizeof(char) * 100);
                if (argumentList[2][0] != '/' && argumentList[2][0] != '~')
                {
                    getcwd(currdirft, 1000);
                    strcat(currdirft, "/");
                    strcat(currdirft, argumentList[2]);
                }
                else if (argumentList[2][0] == '~')
                {
                    strcpy(currdirft, homedir);
                    strcat(currdirft, argumentList[2] + 1);
                }
                else
                {
                    strcpy(currdirft, argumentList[2]);
                }

                if (access(currdirft, F_OK))
                {
                    printf("No such file/directory\n");
                    return;
                }
                else
                {
                    global = malloc(sizeof(char) * 250);
                    strcpy(global, currdirft);
                    int count = scandir(currdirft, &list, default_filter2, alphasort);
                    if (count == -1)
                    {
                        printf("%s\n", argumentList[2]);
                    }
                    else
                    {
                        colorprint(global, list, count);
                        free(global);
                    }
                    return;
                }
            }
            else
            {
                struct dirent **list = NULL;
                int count;
                char *currdirft = (char *)malloc(sizeof(char) * 100);
                getcwd(currdirft, 1000);

                count = scandir(currdirft, &list, default_filter2, alphasort);
                if (access(currdirft, F_OK))
                {
                    printf("No such file/directory\n");
                    return;
                }

                if (count == -1)
                {
                    printf("ls: cannot access the given input: No such file or directory");
                    return;
                }

                global = malloc(sizeof(char) * 250);
                strcpy(global, currdirft);
                colorprint(global, list, count);
                free(global);
                return;
            }
        }
        else if ((strcmp(argumentList[1], "..") == 0))
        {
            struct dirent **list = NULL;
            int count;
            char *currdirft = (char *)malloc(sizeof(char) * 100);
            getcwd(currdirft, 1000);

            char *trimmed = (char *)malloc(sizeof(char) * 100);
            trimmed[0] = '\0';

            int lengthdir = strlen(currdirft);

            int idx;
            for (int i = lengthdir - 1; i >= 0; i--)
            {
                if (currdirft[i] == '/')
                {
                    idx = i;
                    break;
                }
            }
            for (int i = 0; i < idx; i++)
            {
                char ch = currdirft[i];
                strncat(trimmed, &ch, 1);
            }

            strcpy(currdirft, trimmed);
            if (access(currdirft, F_OK))
            {
                printf("No such file/directory\n");
                return;
            }

            count = scandir(currdirft, &list, default_filter, alphasort);

            if (count == -1)
            {
                printf("ls: cannot access the given input: No such file or directory");
                return;
            }
            global = malloc(sizeof(char) * 250);
            strcpy(global, currdirft);
            colorprint(global, list, count);
            free(global);
            return;
        }
        else if ((strcmp(argumentList[1], "-l") == 0) && len == 2)
        {
            struct dirent **list = NULL;
            char *currdirft = (char *)malloc(sizeof(char) * 100);
            getcwd(currdirft, 1000);

            global = malloc(sizeof(char) * 250);
            strcpy(global, currdirft);
            if (access(currdirft, F_OK))
            {
                printf("No such file/directory\n");
                return;
            }

            int count = scandir(currdirft, &list, default_filter, alphasort);

            if (count == -1)
            {
                printf("ls: cannot access the given input: No such file or directory");
                return;
            }
            printstat(list, count);
            free(global);
            return;
        }
        else if ((strcmp(argumentList[1], "-l") == 0) && len == 3)
        {
            struct dirent **list = NULL;
            char *currdirft = (char *)malloc(sizeof(char) * 100);
            if (argumentList[2][0] != '/' && argumentList[2][0] != '~')
            {
                getcwd(currdirft, 1000);
                strcat(currdirft, "/");
                strcat(currdirft, argumentList[2]);
            }
            else if (argumentList[2][0] == '~')
            {
                strcpy(currdirft, homedir);
                strcat(currdirft, argumentList[2] + 1);
            }
            else
            {
                strcpy(currdirft, argumentList[2]);
            }
            global = malloc(sizeof(char) * 250);
            strcpy(global, currdirft);
            if (access(currdirft, F_OK))
            {
                printf("No such file/directory\n");
                return;
            }

            int count = scandir(currdirft, &list, default_filter, alphasort);

            if (count == -1)
            {
                printstatfile(currdirft, currdirft);
                return;
            }
            printstat(list, count);
            free(global);
            return;
        }
        else if ((strcmp(argumentList[1], "-al") == 0) || ((strcmp(argumentList[1], "-la") == 0)))
        {
            struct dirent **list = NULL;
            char *currdirft = (char *)malloc(sizeof(char) * 100);
            getcwd(currdirft, 1000);
            if (access(currdirft, F_OK))
            {
                printf("No such file/directory\n");
                return;
            }

            int count = scandir(currdirft, &list, default_filter2, alphasort);
            global = malloc(sizeof(char) * 250);
            strcpy(global, currdirft);
            if (count == -1)
            {
                printf("ls: cannot access the given input: No such file or directory");
                return;
            }
            printstat(list, count);
            free(global);
            return;
        }
        else
        {
            if (!access(argumentList[1], F_OK))
            {
                struct dirent **list = NULL;
                int count;
                count = scandir(argumentList[1], &list, default_filter, alphasort);
                global = malloc(sizeof(char) * 250);
                strcpy(global, argumentList[1]);

                if (count == -1)
                {
                    printf("%s\n", argumentList[1]);
                    return;
                }
                else
                {
                    colorprint(global, list, count);
                    free(global);
                }
                return;
            }
            else
            {
                printf("ls: cannot access '%s': No such file or directory\n", argumentList[1]);
                return;
            }
        }
    }
    return;
}

void inpls(char *argumentList[250], int len)
{
    int aflag = 0;
    int lflag = 0;
    int dotflag = 0;
    int dotdotflag = 0;
    int tildaflag = 0;
    int alflag = 0;
    char *arr[250];
    int cmds = 0;

    for (int i = 1; i < len; i++)
    {
        if (strcmp(argumentList[i], "-a") == 0)
        {
            aflag = 1;
        }
        else if (strcmp(argumentList[i], "-l") == 0)
        {
            lflag = 1;
        }
        else if (strcmp(argumentList[i], "~") == 0)
        {
            tildaflag = 1;
        }
        else if (strcmp(argumentList[i], "-al") == 0 || strcmp(argumentList[i], "-la") == 0)
        {
            aflag = 1;
            lflag = 1;
        }
        else
        {
            arr[cmds] = malloc(sizeof(char) * 50);
            arr[cmds] = argumentList[i];
            cmds++;
        }
    }
    if (cmds == 0)
    {
        char *arrcall[250];
        int len = 0;
        arrcall[0] = malloc(sizeof(char) * 250);
        arrcall[0] = "ls";
        if (aflag == 1 && lflag == 1)
        {
            arrcall[1] = malloc(sizeof(char) * 250);
            arrcall[1] = "-a";
            arrcall[2] = malloc(sizeof(char) * 250);
            arrcall[2] = "-l";
            len = 3;
        }
        else if (aflag == 1 && lflag == 0)
        {
            arrcall[1] = malloc(sizeof(char) * 250);
            arrcall[1] = "-a";
            len = 2;
        }
        else if (aflag == 0 && lflag == 1)
        {
            arrcall[1] = malloc(sizeof(char) * 250);
            arrcall[1] = "-l";
            len = 2;
        }
        else if (aflag == 0 && lflag == 0)
        {
            len = 1;
        }
        lscmd(arrcall, len);
    }
    for (int i = 0; i < cmds; i++)
    {
        char *arrcall[250];
        int len = 0;
        arrcall[0] = malloc(sizeof(char) * 250);
        arrcall[0] = "ls";

        if (aflag == 1 && lflag == 1)
        {
            arrcall[1] = malloc(sizeof(char) * 250);
            arrcall[1] = "-a";
            arrcall[2] = malloc(sizeof(char) * 250);
            arrcall[2] = "-l";
            arrcall[3] = malloc(sizeof(char) * 250);
            arrcall[3] = arr[i];
            len = 4;
        }
        else if (aflag == 1 && lflag == 0)
        {
            arrcall[1] = malloc(sizeof(char) * 250);
            arrcall[1] = "-a";
            arrcall[2] = malloc(sizeof(char) * 250);
            arrcall[2] = arr[i];
            len = 3;
        }
        else if (aflag == 0 && lflag == 1)
        {
            arrcall[1] = malloc(sizeof(char) * 250);
            arrcall[1] = "-l";
            arrcall[2] = malloc(sizeof(char) * 250);
            arrcall[2] = arr[i];
            len = 3;
        }
        else if (aflag == 0 && lflag == 0)
        {
            arrcall[1] = arr[i];
            len = 2;
        }
        lscmd(arrcall, len);
    }
}