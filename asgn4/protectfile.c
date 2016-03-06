#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <inttypes.h>

typedef enum {NONE, DECRYPT, ENCRYPT} mode;

typedef struct arg_s
{
    char *filename;
    mode mode;
    uint64_t key; 
} arg_s;

void usage()
{
    fprintf (stderr, "Usage: protectfile (-d | -e) key file\n");
}

int parse_hex_str(char *str, arg_s *result)
{
    char *str_beg = str;
    if (strlen(str) != 16) return -1;
    while (*str)
    {
        if (!isxdigit(*str)) return -1;
        str++;
    }
    result->key = strtoll(str_beg, NULL, 16);
    return 0;
}

int parse_args(int argc, char **argv, arg_s *result)
{
    result->filename = NULL;
    result->mode = NONE;
    result->key = 0;

    int c;
    while ((c = getopt(argc, argv, "de")) != -1)
    {
        switch (c)
        {
            case 'd':
                result->mode = DECRYPT;
                break;
            case 'e':
                result->mode = ENCRYPT;
                break;
            case '?':
            default:
                return -1;
        }
    }
    if (result->mode == NONE) return -1;
    if (argc - optind != 2) return -1;
    if (parse_hex_str(argv[optind++], result)) return -1;
    result->filename = argv[optind++];
    return 0;
}

int main (int argc, char **argv)
{
    arg_s args;
    if (parse_args(argc, argv, &args)) 
    {
        usage();
        return 1;
    }
    printf ("%s ;", args.filename);
    printf ("%"PRIu64 "\n", args.key);
}
