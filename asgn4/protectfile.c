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

#include "rijndael.h"

#define KEYBITS 128

typedef enum {NONE, DECRYPT, ENCRYPT} mode;

typedef struct arg_s
{
    char *filename;
    mode mode;
    int k0;
    int k1; 
} arg_s;

void usage()
{
    fprintf (stderr, "Usage: protectfile (-d | -e) key file\n");
}

int parse_hex_str(char *str, arg_s *result)
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
    return 0;
}

int parse_args(int argc, char **argv, arg_s *result)
{
    result->filename = NULL;
    result->mode = NONE;
    result->k0 = 0;
    result->k1 = 0;
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
    printf ("fname: %s ;\n", args.filename);
    
  unsigned long rk[RKLENGTH(KEYBITS)];  /* round key */
  unsigned char key[KEYLENGTH(KEYBITS)];/* cipher key */
  char  buf[100];
  int i, nbytes, nwritten , ctr;
  int totalbytes;
  int   k0, k1;
  int fileId = 0x1234;          /* fake (in this example) */
  int nrounds;              /* # of Rijndael rounds */
  char *password;           /* supplied (ASCII) password */
  int   fd;
  char *filename;
  char sticky[] = "1000";
  char stickyoff[] = "0644";
  int s; 
  unsigned char filedata[16];
  unsigned char ciphertext[16];
  unsigned char ctrvalue[16];




  bzero (key, sizeof (key));
  k0 = args.k0;
  k1 = args.k1;
  bcopy (&k0, &(key[0]), sizeof (k0));
  bcopy (&k1, &(key[sizeof(k0)]), sizeof (k1));
  filename = args.filename;

  /* Print the key, just in case */
  for (i = 0; i < sizeof (key); i++) {
    sprintf (buf+2*i, "%02x", key[sizeof(key)-i-1]);
  }
  fprintf (stderr, "KEY: %s\n", buf);

    struct stat sb;
    stat (filename, &sb);
    int mode = sb.st_mode;
    fileId = sb.st_ino;

    // Clear sticky bit
    mode &= ~I_ISTXT;
    chmod (filename, mode);

  /*
   * Initialize the Rijndael algorithm.  The round key is initialized by this
   * call from the values passed in key and KEYBITS.
   */
  nrounds = rijndaelSetupEncrypt(rk, key, KEYBITS);

  /*
   * Open the file.
   */
  fd = open(filename, O_RDWR);
  if (fd < 0)
  {
    fprintf(stderr, "Error opening file %s\n", argv[2]);
    return 1;
  }

  /* fileID goes into bytes 8-11 of the ctrvalue */
  bcopy (&fileId, &(ctrvalue[8]), sizeof (fileId));

  /* This loop reads 16 bytes from the file, XORs it with the encrypted
     CTR value, and then writes it back to the file at the same position.
     Note that CTR encryption is nice because the same algorithm does
     encryption and decryption.  In other words, if you run this program
     twice, it will first encrypt and then decrypt the file.
  */
  for (ctr = 0, totalbytes = 0; /* loop forever */; ctr++)
  {
    /* Read 16 bytes (128 bits, the blocksize) from the file */
    nbytes = read (fd, filedata, sizeof (filedata));
    if (nbytes <= 0) {
      break;
    }
    if (lseek (fd, totalbytes, SEEK_SET) < 0)
    {
      perror ("Unable to seek back over buffer");
      exit (-1);
    }

    /* Set up the CTR value to be encrypted */
    bcopy (&ctr, &(ctrvalue[0]), sizeof (ctr));

    /* Call the encryption routine to encrypt the CTR value */
    rijndaelEncrypt(rk, nrounds, ctrvalue, ciphertext);

    /* XOR the result into the file data */
    for (i = 0; i < nbytes; i++) {
      filedata[i] ^= ciphertext[i];
    }

    /* Write the result back to the file */
    nwritten = write(fd, filedata, nbytes);
    if (nwritten != nbytes)
    {
      fprintf (stderr,
           "%s: error writing the file (expected %d, got %d at ctr %d\n)",
           argv[0], nbytes, nwritten, ctr);
      break;
    }

    /* Increment the total bytes written */
    totalbytes += nbytes;
  }
  close (fd);
  // Set sticky bit
  if (args.mode == ENCRYPT)
  {
      mode |= I_ISTXT;
      chmod (filename, mode);
  }
  
}

