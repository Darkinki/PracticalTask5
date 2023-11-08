#include <stdio.h>
#include "sha1backg.h"

int main() {
    uint8_t message[] = "sha";
    uint32_t hash[5];
    sha1(message, sizeof(message) - 1, hash);
    printf("%x%x%x%x%x\n", hash[0], hash[1], hash[2], hash[3], hash[4]);  //виходи рандомні? в чому помилка?
    return 0;
}
