
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <getopt.h>

#include "AES_Encrypt_Algorithm.h"

using namespace std;


int main(int argc, char *argv[]) {
    int c;
    int r;
    FILE *fp;
    BYTE AES_input_cipher[AES_CIPHER_SIZE];
    BYTE AES_input_key[AES_KEY_SIZE];
    char *file_name = NULL;
    while ((c = getopt(argc, argv, "f:")) >= 0) {
        switch (c) {
            case 'f': file_name = optarg; break;
            default: break;
        }
    }

    if (file_name == NULL) {
        fp = stdin;
    } else {
        fp = fopen(file_name, "rb");
        if (!fp) {
            fprintf(stderr, "can't open file %s\n", file_name);
            exit(1);
        }
    }

    AES_Test_ByteSub();
    /*
    while (true) {
        if ((r = fread(AES_input_cipher, 1, AES_CIPHER_SIZE, fp)) != AES_CIPHER_SIZE) {
            fprintf(stderr, "read %d bytes for cipher buffer\n", r);
            exit(1);
        }
        if ((r = fread(AES_input_key, 1, AES_KEY_SIZE, fp)) != AES_KEY_SIZE) {
            fprintf(stderr, "read %d bytes for key buffer\n", r);
            exit(1);
        }
    }
    */

    return 0;
}
