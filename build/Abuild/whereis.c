#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        fprintf(stderr, "The syntax of this command is: [filename]\n");
        return EXIT_FAILURE;
    }

    size_t file_name_len = strlen(argv[1]);
    if(file_name_len == 0)
    {
        fprintf(stderr, "[filename] must not be empty\n");
        return EXIT_FAILURE;
    }

    printf("%s:", argv[1]);

    const char* delims = ":";
    char* path_cpy = strdup(getenv("PATH"));
    char* path = strtok(path_cpy, delims);

    while(path != NULL)
    {
        size_t path_len = strlen(path) + file_name_len + 2;
        char* buf = (char*)calloc(path_len, sizeof(char));
        snprintf(buf, path_len, "%s/%s", path, argv[1]);

        if(access(buf, F_OK) == 0)
        {
            printf(" %s", buf);
        }

        path = strtok(NULL, delims);
        free(buf);
    }
    
    printf("\n");
    return EXIT_SUCCESS;
}