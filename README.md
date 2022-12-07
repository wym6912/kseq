# kseq
Functionality: a generic stream buffer & FASTA/FASTQ file parser

This kseq is download from https://github.com/mengyao/Complete-Striped-Smith-Waterman-Library/blob/master/src/kseq.h.

## gz mode usage

This content is from http://attractivechaos.github.io/klib/#Kseq%3A%20stream%20buffer%20and%20FASTA%2FQ%20parser.

### Synopsis
* Functionality: generic stream buffer & FASTA/FASTQ file parser
* Library source code: [kseq.h](https://github.com/attractivechaos/klib/blob/master/kseq.h)
* Dependencies: none; [zlib](http://www.zlib.net) recommended, but not required
* Related articles: [A generic stream buffer](https://attractivechaos.wordpress.com/2008/10/11/a-generic-buffered-stream-wrapper/), [What does zlib-1.2.5 bring to us?](https://attractivechaos.wordpress.com/2010/05/20/what-does-zlib-1-2-5-bring-to-us/) and [How To Efficiently Parse A Huge Fastq File?](https://www.biostars.org/p/10353/)
### Examples
#### Example 1: parse FASTA/Q file, optionally compressed with zlib
```c
// to compile: gcc this_prog.c -lz
#include <zlib.h>
#include <stdio.h>
#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

int main(int argc, char *argv[])
{
  gzFile fp;
  kseq_t *seq;
  int l;
  if (argc == 1) {
    fprintf(stderr, "Usage: %s <in.fasta>\n", argv[0]);
    return 1;
  }
  fp = gzopen(argv[1], "r");
  seq = kseq_init(fp);
  while ((l = kseq_read(seq)) >= 0) {
    printf("name: %s\n", seq->name.s);
    if (seq->comment.l) printf("comment: %s\n", seq->comment.s);
    printf("seq: %s\n", seq->seq.s);
    if (seq->qual.l) printf("qual: %s\n", seq->qual.s);
  }
  printf("return value: %d\n", l);
  kseq_destroy(seq);
  gzclose(fp);
  return 0;
}
```
#### Example 2: read a text file line-by-line
```c
#include <zlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "kseq.h"
KSTREAM_INIT(gzFile, gzread, 16384)
 
int main(int argc, char *argv[])
{
    gzFile fp;
    kstream_t *ks;
    kstring_t str = {0,0,0};
    if (argc == 1) {
        fprintf(stderr, "Usage: %s <in.txt>\n", argv[0]);
        return 1;
    }
    fp = gzopen(argv[1], "r");
    ks = ks_init(fp);
    while (ks_getuntil(ks, '\n', &str, 0) >= 0)
        printf("%s\n", str.s);
    ks_destroy(ks);
    gzclose(fp);
    free(str.s);
    return 0;
}
```

## Common file usage

See `fileread.c` for using kseq.h.

I made a simple solution for `fileread.c` in Visual Studio 2022, called `kseq.sln`.
