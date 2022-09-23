#include "headers.h"
#include "globals.h"

void piping(char *strcomm)
{
    char **words = (char **)malloc(1000);
    char *word;
    word = (char *)malloc(1000);
    word = strtok(strcomm, "|");
    int idx;
    for (idx = 0; word; idx++)
    {
        words[idx] = word;
        word = strtok(NULL, "|");
    }
    words[idx] = NULL;
    int pipearr[2];
    int store = 0;

    for (int k = 0; k < idx; ++k)
    {
        pipe(pipearr);
        pid_t pid = fork();
        if (pid == 0)
        {
            dup2(store, 0);
            if (k != idx - 1)
            {
                dup2(pipearr[1], 1);
            }
            close(pipearr[0]);
            int stdins = dup(0);
            int stdouts = dup(1);
            execute(words[k]);
            dup2(stdins, 0);
            dup2(stdouts, 1);
            exit(0);
        }
        wait(NULL);
        close(pipearr[1]);
        store = pipearr[0];
    }
    free(word);
    free(words);
}