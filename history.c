#include "headers.h"

char *arr[200];
int var;

void add_command_to_history(char *command)
{
    char buffer[500];
    char *path = malloc(sizeof(char) * 200);
    strcpy(path, homedir);
    strcat(path, "/history.txt");
    FILE *fp = fopen(path, "r+");
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    int count = 0;

    while ((read = getline(&line, &length, fp)) != -1)
    {
        arr[count] = strdup(line);
        count++;
    }
    fclose(fp);

    var = count;

    if (var > 0)
    {
        if (strcmp(arr[count - 1], command) == 0)
        {
            return;
        }
    }
    if (var < 20)
    {
        arr[var++] = strdup(command);
    }
    else
    {
        free(arr[0]);
        for (int i = 0; i < 19; i++)
        {
            arr[i] = arr[i + 1];
        }
        arr[19] = strdup(command);
    }

    FILE *fpw = fopen(path, "w+");

    for (int i = 0; i < var; i++)
    {
        fprintf(fpw, "%s", arr[i]);
    }

    fclose(fpw);
}

void display_history()
{
    char *path = malloc(sizeof(char) * 200);
    strcpy(path, homedir);
    strcat(path, "/history.txt");
    FILE *fp = fopen(path, "r");
    char *line = NULL;
    size_t length = 0;
    ssize_t read;
    int count = 0;
    char *arrtemp[21];
    while ((read = getline(&line, &length, fp)) != -1)
    {
        arrtemp[count] = strdup(line);
        count++;
    }
    if (count > 10)
    {
        for (int i = count - 10; i < count; i++)
        {
            printf("%s", arrtemp[i]);
        }
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            printf("%s", arrtemp[i]);
        }
    }
    fclose(fp);
}