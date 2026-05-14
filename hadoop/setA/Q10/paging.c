#include <stdio.h>

int main() {

    unsigned int page_table[] = {3,1,4};

    unsigned int va[] = {0x1A3F, 0x2B10};

    int page_size = 4096; // 4KB

    for(int i = 0; i < 2; i++) {

        unsigned int page_no = va[i] / page_size;
        unsigned int offset = va[i] % page_size;

        unsigned int frame_no = page_table[page_no];

        unsigned int pa = (frame_no * page_size) + offset;

        printf("Virtual Address : 0x%X\n", va[i]);
        printf("Page Number     : %u\n", page_no);
        printf("Offset          : 0x%X\n", offset);
        printf("Physical Address: 0x%X\n\n", pa);
    }

    return 0;
}