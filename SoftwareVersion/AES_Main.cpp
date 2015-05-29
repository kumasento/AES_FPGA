
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

    /*
    BYTE AES_Text[AES_CIPHER_SIZE] = {
        0x19, 0x3D, 0xE3, 0xBE,
        0xA0, 0xF4, 0xE2, 0x2B,
        0x9A, 0xC6, 0x8D, 0x2A,
        0xE9, 0xF8, 0x48, 0x08
    };
    BYTE AES_Round_Key[AES_KEY_SIZE] = {
        0xA0, 0xFA, 0xFE, 0x17,
        0x88, 0x54, 0x2C, 0xB1,
        0x23, 0xA3, 0x39, 0x39,
        0x2A, 0x6C, 0x76, 0x05
    };

    BYTE AES_Text_ByteSub[AES_CIPHER_SIZE];
    BYTE AES_Text_Shift[AES_CIPHER_SIZE];
    BYTE AES_Text_Mix[AES_CIPHER_SIZE];
    BYTE AES_Text_Add[AES_CIPHER_SIZE];

    printf("0x%02x\n", AES_Mix_Row_2(0xd4, 0xbf, 0x5d, 0x30));
    printf("0x%02x\n", AES_Mod(0x100));
    AES_Print_Text(AES_Text, "Text");
    AES_SubBytes(AES_Text, &AES_Text_ByteSub);
    AES_Print_Text(AES_Text_ByteSub, "ByteSub");
    AES_ShiftRow(AES_Text_ByteSub, &AES_Text_Shift);
    AES_Print_Text(AES_Text_Shift, "Shift");
    AES_MixColumn(AES_Text_Shift, &AES_Text_Mix);
    AES_Print_Text(AES_Text_Mix, "Mix");
    AES_AddRoundKey(AES_Text_Mix, AES_Round_Key, &AES_Text_Add);
    AES_Print_Text(AES_Text_Add, "Add Round");

    WORD word = 0x3c4fcf09; // big endian
    WORD RotWord;
    WORD SubWord;
    AES_Key_RotWord(word, &RotWord);
    printf("0x%08x -> 0x%08x\n", word, RotWord);
    AES_Key_SubWord(RotWord, &SubWord);
    printf("0x%08x -> 0x%08x\n", RotWord, SubWord);

    BYTE AES_Key[AES_KEY_SIZE] = {
        0x2B, 0x7E, 0x15, 0x16,
        0x28, 0xAE, 0xD2, 0xA6,
        0xAB, 0xF7, 0x15, 0x88,
        0x09, 0xCF, 0x4F, 0x3C
    };
    BYTE AES_Key_Sched[AES_KEY_SIZE];

    
    for (int i = 0; i < AES_KEY_128_NUM_ROUND; i++) {
        AES_Key_Schedule(AES_Key, &AES_Key_Sched, i+1);

        printf("Round %d\n", i+1);
        AES_Print_Text(AES_Key_Sched, "Scheduled Key");
        memcpy(AES_Key, AES_Key_Sched, sizeof(AES_Key));
    }
    */
    int iter = atoi(argv[1]);
    AES_Test_Bench(iter);
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
        AES_Print_Text()
    }
    */

    return 0;
}
