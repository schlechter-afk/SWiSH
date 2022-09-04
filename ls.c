#include "headers.h"
#include <stdlib.h>
#include <locale.h>
#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

int default_filter(const struct dirent *ent)
{
    return (ent->d_name[0] != '.');
}

int default_filter2(const struct dirent *ent)
{
    return 1;
}

void lscmd(char *argumentList[50], int len)
{
    // printf("%s\n", argumentList[1]);

    setlocale(LC_ALL, "");
    if (len == 1 || strcmp(argumentList[1], ".") == 0)
    {
        struct dirent **list = NULL;
        int count;
        char *currdirft = (char *)malloc(sizeof(char) * 100);
        getcwd(currdirft, 1000);

        count = scandir(currdirft, &list, default_filter, alphasort);

        if (count == -1)
        {
            printf("ls: cannot access the given input: No such file or directory");
            return;
        }

        for (int i = 0; i < count; i++)
        {
            printf("%s\n", list[i]->d_name);
        }
    }
    else
    {
        if (strcmp(argumentList[1], "-a") == 0)
        {
            if (strcmp(argumentList[2], "-l") == 0)
            {
                // printf("mai yaha aagaya\n");
                struct dirent **list = NULL;
                char *currdirft = (char *)malloc(sizeof(char) * 100);
                getcwd(currdirft, 1000);

                int count = scandir(currdirft, &list, default_filter2, alphasort);

                if (count == -1)
                {
                    printf("ls: cannot access the given input: No such file or directory");
                    return;
                }

                long long int total = 0;
                struct stat stats;

                for (int i = 0; i < count; i++)
                {
                    if (stat(list[i]->d_name, &stats) == 0)
                        total += stats.st_blocks;
                }

                printf("total %lld\n", total / 2);

                for (int i = 0; i < count; i++)
                {
                    if (stat(list[i]->d_name, &stats) == 0)
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

                        printf("%ld ", stats.st_nlink);                   // Number of hard links
                        printf("%s ", (getpwuid(stats.st_uid))->pw_name); // owner name
                        printf("%s ", (getgrgid(stats.st_gid))->gr_name); // group name

                        printf("%ld ", stats.st_size); // Total size, in bytes
                        char last_mod_time[16];
                        strftime(last_mod_time, 14, "%h %d %H:%M", localtime(&stats.st_mtime)); // Time of last modification
                        printf("%s ", last_mod_time);

                        printf("%s\n", list[i]->d_name);
                    } // end of if
                }     // end of for
                for (int i = 0; i < len; i++)
                {
                    argumentList[i][0] = '\0';
                }
                return;
            } // end of big if
            else
            {
                // printf("aya yaha pe finally\n");
                struct dirent **list = NULL;
                int count;
                char *currdirft = (char *)malloc(sizeof(char) * 100);
                getcwd(currdirft, 1000);

                count = scandir(currdirft, &list, default_filter2, alphasort);

                if (count == -1)
                {
                    printf("ls: cannot access the given input: No such file or directory");
                    return;
                }

                for (int i = 0; i < count; i++)
                {
                    printf("%s\n", list[i]->d_name);
                }
                for (int i = 0; i < len; i++)
                {
                    argumentList[i][0] = '\0';
                }
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

            // printf("trimmed is %s\n", trimmed);

            strcpy(currdirft, trimmed);
            count = scandir(currdirft, &list, default_filter, alphasort);

            if (count == -1)
            {
                printf("ls: cannot access the given input: No such file or directory");
                return;
            }

            for (int i = 0; i < count; i++)
            {
                printf("%s\n", list[i]->d_name);
            }
            for (int i = 0; i < len; i++)
            {
                argumentList[i][0] = '\0';
            }
            return;
        }
        else if (argumentList[1][0] == '~')
        {
            struct dirent **list = NULL;
            int count;

            char *chktilda = (char *)malloc(sizeof(char *) * 200);
            strcpy(chktilda, homedir);
            strcat(chktilda, argumentList[1] + 1);
            // printf("%s\n",chktilda);

            count = scandir(chktilda, &list, default_filter, alphasort);

            if (count == -1)
            {
                printf("ls: cannot access the given input: No such file or directory");
                return;
            }

            for (int i = 0; i < count; i++)
            {
                printf("%s\n", list[i]->d_name);
            }
            for (int i = 0; i < len; i++)
            {
                argumentList[i][0] = '\0';
            }
            return;
        }
        else if ((strcmp(argumentList[1], "-l") == 0))
        {
            struct dirent **list = NULL;
            char *currdirft = (char *)malloc(sizeof(char) * 100);
            getcwd(currdirft, 1000);

            int count = scandir(currdirft, &list, default_filter, alphasort);

            if (count == -1)
            {
                printf("ls: cannot access the given input: No such file or directory");
                return;
            }

            long long int total = 0;
            struct stat stats;

            for (int i = 0; i < count; i++)
            {
                if (stat(list[i]->d_name, &stats) == 0)
                    total += stats.st_blocks;
            }

            printf("total %lld\n", total / 2);

            for (int i = 0; i < count; i++)
            {
                if (stat(list[i]->d_name, &stats) == 0)
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

                    printf("%ld ", stats.st_nlink);                   // Number of hard links
                    printf("%s ", (getpwuid(stats.st_uid))->pw_name); // owner name
                    printf("%s ", (getgrgid(stats.st_gid))->gr_name); // group name

                    printf("%ld ", stats.st_size); // Total size, in bytes
                    char last_mod_time[16];
                    strftime(last_mod_time, 14, "%h %d %H:%M", localtime(&stats.st_mtime)); // Time of last modification
                    printf("%s ", last_mod_time);

                    printf("%s\n", list[i]->d_name);
                }
            }
            for (int i = 0; i < len; i++)
            {
                argumentList[i][0] = '\0';
            }
            return;
        }
        else if ((strcmp(argumentList[1], "-al") == 0) || ((strcmp(argumentList[1], "-la") == 0)))
        {
            struct dirent **list = NULL;
            char *currdirft = (char *)malloc(sizeof(char) * 100);
            getcwd(currdirft, 1000);

            int count = scandir(currdirft, &list, default_filter2, alphasort);

            if (count == -1)
            {
                printf("ls: cannot access the given input: No such file or directory");
                return;
            }

            long long int total = 0;
            struct stat stats;

            for (int i = 0; i < count; i++)
            {
                if (stat(list[i]->d_name, &stats) == 0)
                    total += stats.st_blocks;
            }

            printf("total %lld\n", total / 2);

            for (int i = 0; i < count; i++)
            {
                if (stat(list[i]->d_name, &stats) == 0)
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

                    printf("%ld ", stats.st_nlink);                   // Number of hard links
                    printf("%s ", (getpwuid(stats.st_uid))->pw_name); // owner name
                    printf("%s ", (getgrgid(stats.st_gid))->gr_name); // group name

                    printf("%ld ", stats.st_size); // Total size, in bytes
                    char last_mod_time[16];
                    strftime(last_mod_time, 14, "%h %d %H:%M", localtime(&stats.st_mtime)); // Time of last modification
                    printf("%s ", last_mod_time);

                    printf("%s\n", list[i]->d_name);
                }
            }
            for (int i = 0; i < len; i++)
            {
                argumentList[i][0] = '\0';
            }
            return;
        }
        else
        {
            if (!access(argumentList[1], F_OK))
            {
                struct dirent **list = NULL;
                int count;
                count = scandir(argumentList[1], &list, default_filter, alphasort);

                if (count == -1)
                {
                    printf("%s\n", argumentList[1]);
                    return;
                }
                else
                {
                    for (int i = 0; i < count; i++)
                    {
                        printf("%s\n", list[i]->d_name);
                    }
                }
                return;
            }
            else
            {
                printf("ls: cannot access '%s': No such file or directory\n",argumentList[1]);
                return;
            }
        }
    }
    return;
}
