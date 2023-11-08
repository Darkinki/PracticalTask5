#ifndef PRACTICALTASK5_SHA1BACKG_H
#define PRACTICALTASK5_SHA1BACKG_H

#include <stdint.h>

#define ROTL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

void sha1(uint8_t *message, uint32_t len, uint32_t *hash) {
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;

    uint32_t w[80];
    uint32_t a, b, c, d, e, f, k, temp;

    uint32_t i, j;
    uint32_t l = len / 64 + 1;
    uint32_t last = len % 64;
    if (last >= 56) l++;
    for (i = 0; i < l; i++) {
        for (j = 0; j < 16; j++) {
            if (i != l - 1 || j != last / 4)
                w[j] = ((uint32_t)message[i * 64 + j * 4 + 0] << 24) |
                       ((uint32_t)message[i * 64 + j * 4 + 1] << 16) |
                       ((uint32_t)message[i * 64 + j * 4 + 2] << 8) |
                       ((uint32_t)message[i * 64 + j * 4 + 3] << 0);
            else if (j * 4 < last)
                w[j] = ((uint32_t)message[i * 64 + j * 4 + 0] << 24) |
                       ((uint32_t)message[i * 64 + j * 4 + 1] << 16) |
                       ((uint32_t)message[i * 64 + j * 4 + 2] << 8) |
                       ((j * 4 + 3 < last ? message[i * 64 + j * 4 + 3] : 0x80) << 0);
            else if (j * 4 == last)
                w[j] = 0x80000000;
            else if (i * 64 + j * 4 < len / 8 * 64 + 56)
                w[j] = 0;
            else if (i * 64 + j * 4 == len / 8 * 64 + 56)
                w[j] = (len & 0x0FFFFFFF) << 3 | (len & 0xF0000000) >> 29;
            else
                w[j] = len >> 29;
        }
        for (j = 16; j < 80; j++) {
            w[j] = ROTL(w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16], 1);
        }

        a = h0;
        b = h1;
        c = h2;
        d = h3;
        e = h4;

        for (j = 0; j < 80; j++) {
            if (j < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (j < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (j < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            temp = ROTL(a, 5) + f + e + k + w[j];
            e = d;
            d = c;
            c = ROTL(b, 30);
            b = a;
            a = temp;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
    }

    hash[0] = h0;
    hash[1] = h1;
    hash[2] = h2;
    hash[3] = h3;
    hash[4] = h4;
}

#endif //PRACTICALTASK5_SHA1BACKG_H
