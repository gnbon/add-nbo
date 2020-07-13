#include <stdint.h> // for uint32_t
#include <stdio.h> // for fopen, fwrite, printf
#include <netinet/in.h> // for ntohl
#include <stdlib.h> //for malloc

int main(int argc, char *argv[]) {
    if (argc != 3) {
            printf("Usage: %s <file1> <file2>\n", argv[0]);
            return 0;
    }

    FILE* fp;
    uint32_t buf_nbo[2], buf_hbo[2], hbo_sum;
    int count, eof_check;

    for (int i=0; i < argc-1; i++) {
        fp = fopen(argv[i+1], "rb"); // open binary & failure check
        if (!fp) {
            fprintf(stderr, "file[%d] open error\n", i);
            exit(1);
        }
        count = fread(&buf_nbo[i], sizeof(uint32_t), 1, fp);
        if (count = fread(&buf_nbo[i], sizeof(uint32_t), 1, fp) != 0) { // cheak is only 4 bytes
            fprintf(stderr, "file[%d] read error\n", i);
            exit(1);

        }
        buf_hbo[i] = ntohl(buf_nbo[i]); // always convert to HBO
        fclose(fp);
    }

    hbo_sum = buf_hbo[0] + buf_hbo[1];

    printf("%d(0x%0x) + %d(0x%0x) = %d(0x%0x)\n",
            buf_hbo[0], buf_hbo[0],
            buf_hbo[1], buf_hbo[1],
            hbo_sum, hbo_sum);

    return 0;
}
