#ifndef ANTRIAN_H
#define ANTRIAN_H

#define MAX_ANTRIAN 50

typedef struct {
    int id_nasabah;
    char nama_nasabah[50];
    int nomor_antrian;
    char jenis_layanan[20];
    char waktu_kedatangan[50];
    char status[20];
} Nasabah;

typedef struct {
    Nasabah antrian[MAX_ANTRIAN];
    int front;
    int rear;
} AntrianBank;

void initAntrian(AntrianBank *queue);
int isEmpty(AntrianBank *queue);
int isFull(AntrianBank *queue);
void getCurrentTime(char *buffer);
void addQueue(AntrianBank *queue, Nasabah nasabah);
void delQueue(AntrianBank *queue);
void peek(AntrianBank *queue);
void peekAll(AntrianBank *queue);

#endif
