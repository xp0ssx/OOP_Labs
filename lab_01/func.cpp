#include <bits/stdc++.h>

int func(int devider, int bound) {
    while (bound > 0) {
        if (bound % devider == 0) {
            return bound;
        }
        bound--;
    }
    return -1;
}