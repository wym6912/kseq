#include "kseq.h"
#include <stdio.h>

#if (defined(__linux__) || defined(__APPLE__))
#include <unistd.h>
#else
#include <io.h>
#include <process.h>
#endif

KSEQ_INIT(int, read)

char *filename = "1.fasta";

int main(int argc, char *argv[])
{
    fprintf(stderr, "Reading sequences from file %s ... ", filename);
    FILE* f_pointer = fopen(filename, "r");
    if (f_pointer == NULL) { fprintf(stderr, "Error: file %s cannot open. Program will exit\n", filename); exit(1); }
    kseq_t* file_t = kseq_init(fileno(f_pointer));
    while (kseq_read(file_t) >= 0)
    {
        fprintf(stdout, "%s\n", file_t -> seq.s);
    }
    kseq_destroy(file_t);
    return 0;
}
