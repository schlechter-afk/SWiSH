void printstat(struct dirent **list, int count)
{
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
    }
}