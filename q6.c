#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PAGE_SIZE 4096
#define PAGE_MASK 0xFFFFF000

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <virtual_address>\n", argv[0]);
        return 1;
    }

    uint32_t virtual_address = (uint32_t) atoi(argv[1]);

    uint32_t page_number = virtual_address >> 12;
    uint32_t offset = virtual_address & 0xFFF;

    printf("The address %u contains: \n", virtual_address);
    printf("page number = %u\n", page_number);
    printf("offset = %u\n", offset);
}