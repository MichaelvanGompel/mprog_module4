/************************************************************************************
 * recover.c
 *
 * Michael van Gompel - mprog1
 *
 * recovers jpeg's from raw memory using first 4 bytes of jpeg as a flag
 * saves jpg's in outfiles
**************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// constants
#define BSIZE 512
#define TSIZE 7

int main(int argc, char *argv[])
{
    // check if there is one argument
    if (argc != 2)
    {
        return 1;
    }

    // open card file
    char *infile = argv[1];
    FILE *raw_file = fopen(infile, "r");
    // check if opening file was successful
    if (raw_file == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // create buffer with space for 512 bytes
    unsigned char buffer[BSIZE];
    // create pointers/variables for the output file
    char *output;
    FILE *outfile;
    char filename[TSIZE];
    // create file/jpeg counter
    int fcount = 0;
    // fill the buffer with first 512 bytes and keep reading until size < 512 (then fread returns 0)
    while (fread(&buffer, BSIZE, 1, raw_file) == 1)
    {
        // check if first 4 bytes signifies start of a jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // check if there is already a jpg found
            if (fcount > 0)
            {
                fclose(outfile);
            }

            // generate outputfile
            sprintf(filename, "%03i.jpg", fcount);
            outfile = fopen(filename, "w");
            // check if outfile is indeed created
            if (outfile == NULL)
            {
                printf("Could not open %s\n", filename);
                return 3;
            }
            // keep track of number jpeg's
            fcount++;
        }

        // open the outfile if start of jpeg's is found
        if (fcount > 0)
        {
            // write buffer in the outfile
            fwrite(buffer, BSIZE, 1, outfile);
        }
    }

    // close files
    fclose(raw_file);
    fclose(outfile);
    return 0;
}

