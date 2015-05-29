
#include <ctime>

#define AES_CIPHER_LENGTH 128
#define AES_KEY_LENGTH 128

typedef unsigned char BYTE;// there might be carry bit
typedef unsigned int WORD;
#define BYTE_SHIFT 2 // note that this value is not related to BYTE_LENGTH, but the actual type of byte
#define BYTE_LENGTH 8
#define WORD_LENGTH 32
#define AES_CIPHER_SIZE (AES_CIPHER_LENGTH/BYTE_LENGTH)
#define AES_KEY_SIZE (AES_KEY_LENGTH/BYTE_LENGTH)

#define AES_SBOX_NUM_ENTRY 256
#define AES_SBOX_EDGE_NUM_SHIFT 4
#define AES_SBOX_EDGE_NUM_ENTRY (1<<AES_SBOX_EDGE_NUM_SHIFT)

#define AES_KEY_128_NUM_ROUND 11
#define AES_KEY_192_NUM_ROUND 11
#define AES_KEY_256_NUM_ROUND 11

const BYTE AES_SBox[AES_SBOX_NUM_ENTRY] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,//0
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,//1
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,//2
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,//3
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,//4
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,//5
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,//6
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,//7
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,//8
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,//9
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,//A
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,//B
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,//C
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,//D
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,//E
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16 //F
};
//inline BYTE AES_ByteSub(BYTE A) {
//    return AES_SBox[AES_SBOX_INDEX(A)];
//}

void AES_Print_Text(BYTE AES_Text[AES_CIPHER_SIZE], const char *AES_Text_Name) {
    printf("AES %s Matrix = \n", AES_Text_Name);
    printf("\t%02x %02x %02x %02x\n", AES_Text[0], AES_Text[4], AES_Text[8],  AES_Text[12]);
    printf("\t%02x %02x %02x %02x\n", AES_Text[1], AES_Text[5], AES_Text[9],  AES_Text[13]);
    printf("\t%02x %02x %02x %02x\n", AES_Text[2], AES_Text[6], AES_Text[10], AES_Text[14]);
    printf("\t%02x %02x %02x %02x\n", AES_Text[3], AES_Text[7], AES_Text[11], AES_Text[15]);
}

#define AES_ByteSub(b) AES_SBox[(b)]

void AES_SubBytes(BYTE AES_Text[AES_CIPHER_SIZE], BYTE (*AES_Text_Sub)[AES_CIPHER_SIZE]) {
    (*AES_Text_Sub)[ 0] = AES_ByteSub(AES_Text[ 0]);
    (*AES_Text_Sub)[ 1] = AES_ByteSub(AES_Text[ 1]);
    (*AES_Text_Sub)[ 2] = AES_ByteSub(AES_Text[ 2]);
    (*AES_Text_Sub)[ 3] = AES_ByteSub(AES_Text[ 3]);
    (*AES_Text_Sub)[ 4] = AES_ByteSub(AES_Text[ 4]);
    (*AES_Text_Sub)[ 5] = AES_ByteSub(AES_Text[ 5]);
    (*AES_Text_Sub)[ 6] = AES_ByteSub(AES_Text[ 6]);
    (*AES_Text_Sub)[ 7] = AES_ByteSub(AES_Text[ 7]);
    (*AES_Text_Sub)[ 8] = AES_ByteSub(AES_Text[ 8]);
    (*AES_Text_Sub)[ 9] = AES_ByteSub(AES_Text[ 9]);
    (*AES_Text_Sub)[10] = AES_ByteSub(AES_Text[10]);
    (*AES_Text_Sub)[11] = AES_ByteSub(AES_Text[11]);
    (*AES_Text_Sub)[12] = AES_ByteSub(AES_Text[12]);
    (*AES_Text_Sub)[13] = AES_ByteSub(AES_Text[13]);
    (*AES_Text_Sub)[14] = AES_ByteSub(AES_Text[14]);
    (*AES_Text_Sub)[15] = AES_ByteSub(AES_Text[15]);
}


void AES_ShiftRow(BYTE AES_Text[AES_CIPHER_SIZE], BYTE (*AES_Text_Shift)[AES_CIPHER_SIZE]){
    (*AES_Text_Shift)[ 0] = AES_Text[ 0]; (*AES_Text_Shift)[ 4] = AES_Text[ 4]; (*AES_Text_Shift)[ 8] = AES_Text[ 8]; (*AES_Text_Shift)[12] = AES_Text[12];
    (*AES_Text_Shift)[ 1] = AES_Text[ 5]; (*AES_Text_Shift)[ 5] = AES_Text[ 9]; (*AES_Text_Shift)[ 9] = AES_Text[13]; (*AES_Text_Shift)[13] = AES_Text[ 1];
    (*AES_Text_Shift)[ 2] = AES_Text[10]; (*AES_Text_Shift)[ 6] = AES_Text[14]; (*AES_Text_Shift)[10] = AES_Text[ 2]; (*AES_Text_Shift)[14] = AES_Text[ 6];
    (*AES_Text_Shift)[ 3] = AES_Text[15]; (*AES_Text_Shift)[ 7] = AES_Text[ 3]; (*AES_Text_Shift)[11] = AES_Text[ 7]; (*AES_Text_Shift)[15] = AES_Text[11];
}

#define AES_Mod_Bit_8(bit) (((~bit)+1) & 0x1B)
#define AES_Mod_Bit_9(bit) (((~bit)+1) & 0x36)
#define AES_Mod(b) \
    AES_Mod_Bit_9(((b)&0x200)>>9) ^ \
    AES_Mod_Bit_8(((b)&0x100)>>8) ^ \
    ((b) & 0xFF)

#define AES_Mix_Row_1(b1, b2, b3, b4) (AES_Mod((b1)<<1) ^ AES_Mod((b2)<<1) ^ (b2) ^ (b3) ^ (b4))
#define AES_Mix_Row_2(b1, b2, b3, b4) (AES_Mod((b2)<<1) ^ AES_Mod((b3)<<1) ^ (b3) ^ (b1) ^ (b4))
#define AES_Mix_Row_3(b1, b2, b3, b4) (AES_Mod((b3)<<1) ^ AES_Mod((b4)<<1) ^ (b4) ^ (b1) ^ (b2))
#define AES_Mix_Row_4(b1, b2, b3, b4) (AES_Mod((b4)<<1) ^ AES_Mod((b1)<<1) ^ (b1) ^ (b2) ^ (b3))

void AES_MixColumn(BYTE AES_Text[AES_CIPHER_SIZE], BYTE (*AES_Text_Mix)[AES_CIPHER_SIZE]) {
    (*AES_Text_Mix)[ 0] = AES_Mix_Row_1(AES_Text[ 0], AES_Text[ 1], AES_Text[ 2], AES_Text[ 3]);
    (*AES_Text_Mix)[ 1] = AES_Mix_Row_2(AES_Text[ 0], AES_Text[ 1], AES_Text[ 2], AES_Text[ 3]);
    (*AES_Text_Mix)[ 2] = AES_Mix_Row_3(AES_Text[ 0], AES_Text[ 1], AES_Text[ 2], AES_Text[ 3]);
    (*AES_Text_Mix)[ 3] = AES_Mix_Row_4(AES_Text[ 0], AES_Text[ 1], AES_Text[ 2], AES_Text[ 3]);

    (*AES_Text_Mix)[ 4] = AES_Mix_Row_1(AES_Text[ 4], AES_Text[ 5], AES_Text[ 6], AES_Text[ 7]);
    (*AES_Text_Mix)[ 5] = AES_Mix_Row_2(AES_Text[ 4], AES_Text[ 5], AES_Text[ 6], AES_Text[ 7]);
    (*AES_Text_Mix)[ 6] = AES_Mix_Row_3(AES_Text[ 4], AES_Text[ 5], AES_Text[ 6], AES_Text[ 7]);
    (*AES_Text_Mix)[ 7] = AES_Mix_Row_4(AES_Text[ 4], AES_Text[ 5], AES_Text[ 6], AES_Text[ 7]);

    (*AES_Text_Mix)[ 8] = AES_Mix_Row_1(AES_Text[ 8], AES_Text[ 9], AES_Text[10], AES_Text[11]);
    (*AES_Text_Mix)[ 9] = AES_Mix_Row_2(AES_Text[ 8], AES_Text[ 9], AES_Text[10], AES_Text[11]);
    (*AES_Text_Mix)[10] = AES_Mix_Row_3(AES_Text[ 8], AES_Text[ 9], AES_Text[10], AES_Text[11]);
    (*AES_Text_Mix)[11] = AES_Mix_Row_4(AES_Text[ 8], AES_Text[ 9], AES_Text[10], AES_Text[11]);

    (*AES_Text_Mix)[12] = AES_Mix_Row_1(AES_Text[12], AES_Text[13], AES_Text[14], AES_Text[15]);
    (*AES_Text_Mix)[13] = AES_Mix_Row_2(AES_Text[12], AES_Text[13], AES_Text[14], AES_Text[15]);
    (*AES_Text_Mix)[14] = AES_Mix_Row_3(AES_Text[12], AES_Text[13], AES_Text[14], AES_Text[15]);
    (*AES_Text_Mix)[15] = AES_Mix_Row_4(AES_Text[12], AES_Text[13], AES_Text[14], AES_Text[15]);
}

void AES_AddRoundKey(BYTE AES_Text[AES_CIPHER_SIZE], BYTE AES_Key[AES_KEY_SIZE], BYTE (*AES_Text_Add)[AES_CIPHER_SIZE]) {
    (*AES_Text_Add)[ 0] = AES_Text[ 0] ^ AES_Key[ 0];
    (*AES_Text_Add)[ 1] = AES_Text[ 1] ^ AES_Key[ 1];
    (*AES_Text_Add)[ 2] = AES_Text[ 2] ^ AES_Key[ 2];
    (*AES_Text_Add)[ 3] = AES_Text[ 3] ^ AES_Key[ 3];
    (*AES_Text_Add)[ 4] = AES_Text[ 4] ^ AES_Key[ 4];
    (*AES_Text_Add)[ 5] = AES_Text[ 5] ^ AES_Key[ 5];
    (*AES_Text_Add)[ 6] = AES_Text[ 6] ^ AES_Key[ 6];
    (*AES_Text_Add)[ 7] = AES_Text[ 7] ^ AES_Key[ 7];
    (*AES_Text_Add)[ 8] = AES_Text[ 8] ^ AES_Key[ 8];
    (*AES_Text_Add)[ 9] = AES_Text[ 9] ^ AES_Key[ 9];
    (*AES_Text_Add)[10] = AES_Text[10] ^ AES_Key[10];
    (*AES_Text_Add)[11] = AES_Text[11] ^ AES_Key[11];
    (*AES_Text_Add)[12] = AES_Text[12] ^ AES_Key[12];
    (*AES_Text_Add)[13] = AES_Text[13] ^ AES_Key[13];
    (*AES_Text_Add)[14] = AES_Text[14] ^ AES_Key[14];
    (*AES_Text_Add)[15] = AES_Text[15] ^ AES_Key[15];
}

/*
void AES_Test_ByteSub() {
    for (int i = 0; i < AES_SBOX_EDGE_NUM_ENTRY; i++) {
        for (int j = 0; j < AES_SBOX_EDGE_NUM_ENTRY; j++) {
            BYTE b = j + (i<<4);
            BYTE index = AES_SBOX_INDEX(b);
            BYTE result = AES_ByteSub(b);
            printf("[%03d] %02x->%02x SBox %02x %s\n",
                    b, index, result, AES_SBox[b], (result==AES_SBox[b]) ? "OK" : "WRONG");
        }
    }
}
*/

// For key schedule
const BYTE RCon_128[AES_KEY_128_NUM_ROUND] = {
    0, // round 0, nothing to do, just padding
    0x01, 0x02, 0x04, 0x08,
    0x10, 0x20, 0x40, 0x80,
    0x1b, 0x36
};

// big endian
#define AES_WORD_BYTE_3(w) (((w)&0xFF000000)>>24)
#define AES_WORD_BYTE_2(w) (((w)&0x00FF0000)>>16)
#define AES_WORD_BYTE_1(w) (((w)&0x0000FF00)>>8)
#define AES_WORD_BYTE_0(w) (((w)&0x000000FF))

#define AES_BYTE_WORD(b3, b2, b1, b0) ((b3)<<24) + ((b2)<<16) + ((b1)<<8) + (b0)

inline void AES_Key_RotWord(WORD AES_Word_Src, WORD* AES_Word_Dst) {
    *AES_Word_Dst = ((AES_Word_Src&0xFF)<<24) + (AES_Word_Src>>8);
}
inline void AES_Key_SubWord(WORD AES_Word_Src, WORD* AES_Word_Dst) {
    *AES_Word_Dst =
        AES_BYTE_WORD(AES_ByteSub(AES_WORD_BYTE_3(AES_Word_Src)),
                      AES_ByteSub(AES_WORD_BYTE_2(AES_Word_Src)),
                      AES_ByteSub(AES_WORD_BYTE_1(AES_Word_Src)),
                      AES_ByteSub(AES_WORD_BYTE_0(AES_Word_Src)));
}

#define AES_BYTE_ARRAY_WORD(arr, i) (*((WORD*)((arr)+(i<<BYTE_SHIFT))))
#define AES_WORD_BYTE_ARRAY(arr, i, b) (*((WORD*)((arr)+(i<<BYTE_SHIFT))) = (b))

inline void AES_Key_Schedule(BYTE AES_Key[AES_KEY_SIZE], BYTE (*AES_Key_Sched)[AES_KEY_SIZE], int rid) {
    WORD AES_Key_Word_3 = AES_BYTE_ARRAY_WORD(AES_Key, 3);
    WORD AES_Key_Word_2 = AES_BYTE_ARRAY_WORD(AES_Key, 2);
    WORD AES_Key_Word_1 = AES_BYTE_ARRAY_WORD(AES_Key, 1);
    WORD AES_Key_Word_0 = AES_BYTE_ARRAY_WORD(AES_Key, 0);

    WORD AES_Key_Word_Rot, AES_Key_Word_Sub;
    AES_Key_RotWord(AES_Key_Word_3, &AES_Key_Word_Rot);
    AES_Key_SubWord(AES_Key_Word_Rot, &AES_Key_Word_Sub);
    WORD AES_Key_Sched_Word_0 = AES_Key_Word_Sub ^ AES_Key_Word_0 ^ RCon_128[rid];
    WORD AES_Key_Sched_Word_1 = AES_Key_Word_1 ^ AES_Key_Sched_Word_0;
    WORD AES_Key_Sched_Word_2 = AES_Key_Word_2 ^ AES_Key_Sched_Word_1;
    WORD AES_Key_Sched_Word_3 = AES_Key_Word_3 ^ AES_Key_Sched_Word_2;

    //printf("0x%08x -> 0x%08x -> 0x%08x\n", AES_Key_Word_3, AES_Key_Word_Rot, AES_Key_Word_Sub);
    //printf("0x%08x -> 0x%08x -> 0x%08x -> 0x%08x\n", AES_Key_Word_0, AES_Key_Word_Sub, RCon_128[rid], AES_Key_Sched_Word_0);
    //printf("0x%08x\n", AES_Key_Sched_Word_1);
    //printf("0x%08x\n", AES_Key_Sched_Word_2);
    //printf("0x%08x\n", AES_Key_Sched_Word_3);

    AES_WORD_BYTE_ARRAY(*AES_Key_Sched, 0, AES_Key_Sched_Word_0);
    AES_WORD_BYTE_ARRAY(*AES_Key_Sched, 1, AES_Key_Sched_Word_1);
    AES_WORD_BYTE_ARRAY(*AES_Key_Sched, 2, AES_Key_Sched_Word_2);
    AES_WORD_BYTE_ARRAY(*AES_Key_Sched, 3, AES_Key_Sched_Word_3);
}

inline void AES_One_Round(BYTE AES_Cipher[AES_CIPHER_SIZE],
                          BYTE (*AES_Cipher_ByteSub)[AES_CIPHER_SIZE],
                          BYTE (*AES_Cipher_Shift)[AES_CIPHER_SIZE],
                          BYTE (*AES_Cipher_Mix)[AES_CIPHER_SIZE],
                          BYTE AES_Key[AES_KEY_SIZE],
                          BYTE (*AES_Key_Result)[AES_KEY_SIZE],
                          BYTE (*AES_Cipher_Result)[AES_CIPHER_SIZE],
                          int round_idx, bool end) {
    if (!end)
        AES_Key_Schedule(AES_Key, AES_Key_Result, round_idx+1);
    if (end) {
        AES_SubBytes(AES_Cipher, AES_Cipher_ByteSub);
        AES_ShiftRow(*AES_Cipher_ByteSub, AES_Cipher_Shift);
        if (end) {
            AES_AddRoundKey(*AES_Cipher_Shift, AES_Key, AES_Cipher_Result);
        } else {
            AES_MixColumn(*AES_Cipher_Shift, AES_Cipher_Mix);
            AES_AddRoundKey(*AES_Cipher_Mix, AES_Key, AES_Cipher_Result);
        }
    } else {
        AES_AddRoundKey(AES_Cipher, AES_Key, AES_Cipher_Result);
    }
}

void AES_Test_Bench(int iter) {
    BYTE AES_Cipher[AES_CIPHER_SIZE] = {
        0x32, 0x43, 0xF6, 0xA8,
        0x88, 0x5A, 0x30, 0x8D,
        0x31, 0x31, 0x98, 0xA2,
        0xE0, 0x37, 0x07, 0x34
    };
    BYTE AES_Cipher_ByteSub[AES_CIPHER_SIZE];
    BYTE AES_Cipher_Shift[AES_CIPHER_SIZE];
    BYTE AES_Cipher_Mix[AES_CIPHER_SIZE];
    BYTE AES_Cipher_Result[AES_KEY_128_NUM_ROUND][AES_CIPHER_SIZE];

    BYTE AES_Key[AES_KEY_SIZE] = {
        0x2B, 0x7E, 0x15, 0x16,
        0x28, 0xAE, 0xD2, 0xA6,
        0xAB, 0xF7, 0x15, 0x88,
        0x09, 0xCF, 0x4F, 0x3C
    };
    BYTE AES_Key_Result[AES_KEY_128_NUM_ROUND][AES_KEY_SIZE];

    time_t start, end;
    start = clock();
    for (int t = 0; t < iter; t ++) {
        AES_One_Round(AES_Cipher,            &AES_Cipher_ByteSub, &AES_Cipher_Shift, &AES_Cipher_Mix, AES_Key,            &AES_Key_Result[ 0], &AES_Cipher_Result[ 0],  0, 0);
        AES_One_Round(AES_Cipher_Result[ 0], &AES_Cipher_ByteSub, &AES_Cipher_Shift, &AES_Cipher_Mix, AES_Key_Result[ 0], &AES_Key_Result[ 1], &AES_Cipher_Result[ 1],  1, 0);
        AES_One_Round(AES_Cipher_Result[ 1], &AES_Cipher_ByteSub, &AES_Cipher_Shift, &AES_Cipher_Mix, AES_Key_Result[ 1], &AES_Key_Result[ 2], &AES_Cipher_Result[ 2],  2, 0);
        AES_One_Round(AES_Cipher_Result[ 2], &AES_Cipher_ByteSub, &AES_Cipher_Shift, &AES_Cipher_Mix, AES_Key_Result[ 2], &AES_Key_Result[ 3], &AES_Cipher_Result[ 3],  3, 0);
        AES_One_Round(AES_Cipher_Result[ 3], &AES_Cipher_ByteSub, &AES_Cipher_Shift, &AES_Cipher_Mix, AES_Key_Result[ 3], &AES_Key_Result[ 4], &AES_Cipher_Result[ 4],  4, 0);
        AES_One_Round(AES_Cipher_Result[ 4], &AES_Cipher_ByteSub, &AES_Cipher_Shift, &AES_Cipher_Mix, AES_Key_Result[ 4], &AES_Key_Result[ 5], &AES_Cipher_Result[ 5],  5, 0);
        AES_One_Round(AES_Cipher_Result[ 5], &AES_Cipher_ByteSub, &AES_Cipher_Shift, &AES_Cipher_Mix, AES_Key_Result[ 5], &AES_Key_Result[ 6], &AES_Cipher_Result[ 6],  6, 0);
        AES_One_Round(AES_Cipher_Result[ 6], &AES_Cipher_ByteSub, &AES_Cipher_Shift, &AES_Cipher_Mix, AES_Key_Result[ 6], &AES_Key_Result[ 7], &AES_Cipher_Result[ 7],  7, 0);
        AES_One_Round(AES_Cipher_Result[ 7], &AES_Cipher_ByteSub, &AES_Cipher_Shift, &AES_Cipher_Mix, AES_Key_Result[ 7], &AES_Key_Result[ 8], &AES_Cipher_Result[ 8],  8, 0);
        AES_One_Round(AES_Cipher_Result[ 8], &AES_Cipher_ByteSub, &AES_Cipher_Shift, &AES_Cipher_Mix, AES_Key_Result[ 8], &AES_Key_Result[ 9], &AES_Cipher_Result[ 9],  9, 0);
        AES_One_Round(AES_Cipher_Result[ 9], &AES_Cipher_ByteSub, &AES_Cipher_Shift, &AES_Cipher_Mix, AES_Key_Result[ 9], &AES_Key_Result[10], &AES_Cipher_Result[10], 10, 1);
        //AES_One_Round(AES_Cipher, &AES_Cipher_ByteSub, &AES_Cipher_Shift, &AES_Cipher_Mix, AES_Key_Result[10], &AES_Key_Result[11], &AES_Cipher_Result[11], 11, 1);
    }
    end = clock();
    double duration = (double)(end-start)/CLOCKS_PER_SEC;
    double bandwidth = (double)(iter * AES_KEY_LENGTH)/duration;
    printf("Time: %.6lfs Bandwidth: %6.6lfb/s %6.6lfB/s %6.6lfMB/s %6.6lfGB/s\n",
        duration, bandwidth, bandwidth/8, bandwidth/(8*1024*1024), bandwidth/((double)8*1024*1024*1024));

    AES_Print_Text(AES_Key_Result[9], "Key Result");
    AES_Print_Text(AES_Cipher_Result[10], "Cipher Result");
}

