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
    setlocale(LC_ALL, "");
    if (len == 1 || strcmp(argumentList[1], ".") == 0)
    {
        int arg;
        struct dirent **list = NULL;
        int i, count;
        char *currdirft = (char *)malloc(sizeof(char) * 100);
        getcwd(currdirft, 1000);

        count = scandir(currdirft, &list, default_filter, alphasort);

        if (count == -1)
        {
            printf("ls: cannot access the given input: No such file or directory");
            return;
        }

        for (i = 0; i < count; i++)
        {
            printf("%s\n", list[i]->d_name);
        }
    }
    else
    {
        if ((strcmp(argumentList[1], "-a") == 0) || (strcmp(argumentList[1], "--all") == 0))
        {
            int arg;
            struct dirent **list = NULL;
            int i, count;
            char *currdirft = (char *)malloc(sizeof(char) * 100);
            getcwd(currdirft, 1000);

            count = scandir(currdirft, &list, default_filter2, alphasort);

            if (count == -1)
            {
                printf("ls: cannot access the given input: No such file or directory");
                return;
            }

            for (i = 0; i < count; i++)
            {
                printf("%s\n", list[i]->d_name);
            }
        }
        else if ((strcmp(argumentList[1], "..") == 0))
        {
            int arg;
            struct dirent **list = NULL;
            int i, count;
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

            for (i = 0; i < count; i++)
            {
                printf("%s\n", list[i]->d_name);
            }
        }
        else if (argumentList[1][0] == '~')
        {
            int arg;
            struct dirent **list = NULL;
            int i, count;

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

            for (i = 0; i < count; i++)
            {
                printf("%s\n", list[i]->d_name);
            }
        }
        else if ((strcmp(argumentList[1], "-l") == 0))
        {
            
        }
    }
    return;
}