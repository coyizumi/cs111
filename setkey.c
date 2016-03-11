#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <inttypes.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//#include "rijndael.h"

typedef struct hexvalue
{
   unsigned int k0;
   unsigned int k1;
} hexvalue;


int parse_hex_str(char *str, hexvalue *result)
{
    char *str_beg = str;
    char buff[18];
    int i = 0;
    if (strlen(str) != 16) return -1;
    while (*str)
    {
        if (!isxdigit(*str)) return -1;
        buff[i++] = *str++;
        if (i == 8) buff[i++] = '\0';
    }
    buff[i] = '\0';
    result->k0 = strtol(buff, NULL, 16);
    result->k1 = strtol(buff+9, NULL, 16);
    printf ("K0: %d ; K1: %d\n", result->k0, result->k1);
    syscall(546,result->k0,result->k1);
    return 0;
}


int main(int argc, char **argv) {
   //Declaaring k0 and k1
   //Creates the struct to hold k0, and k1
   struct hexvalue hex;
   parse_hex_str(argv[optind++],&hex);
   return 0;
}

