﻿#include <stdio.h>

int hamming_distance(unsigned x, unsigned y) {
    int dist = 0;
    unsigned val = x ^ y;
//    printf("%d ", val);

    // Count the number of bits set
    while (val != 0) {
        // A bit is set, so increment the count and clear the bit
        dist++;
        val &= val - 1;
    }

    // Return the number of differing bits
    return dist;
}

int main() {
	int x = hamming_distance(6, 2);
	printf("%d ", x);	
}
