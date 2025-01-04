#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "antrian.h"

void initAntrian(AntrianBank *queue) {
    queue->front = -1;
    queue->rear = -1;
}

int isEmpty(AntrianBank *queue) {
    return queue->front == -1;
}

int isFull(AntrianBank *queue) {
    return (queue->rear + 1) % MAX_ANTRIAN == queue->front;
}

void getCurrentTime(char *buffer) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, 50, "%Y-%m-%d %H:%M:%S", t);
}

void addQueue(AntrianBank *queue, Nasabah nasabah) {
    if (isFull(queue)) {
        printf("\n[ERROR] Antrian penuh. Tidak dapat menambahkan nasabah baru.\n");
        return;
    }

    if (isEmpty(queue)) {
        queue->front = 0;
    }

    queue->rear = (queue->rear + 1) % MAX_ANTRIAN;
    queue->antrian[queue->rear] = nasabah;
    printf("\n[INFO] Nasabah '%s' berhasil ditambahkan ke antrian.\n", nasabah.nama_nasabah);
}

void delQueue(AntrianBank *queue) {
    if (isEmpty(queue)) {
        printf("\n[ERROR] Antrian kosong. Tidak ada nasabah untuk dihapus.\n");
        return;
    }

    Nasabah nasabah = queue->antrian[queue->front];
    strcpy(nasabah.status, "Selesai");
    printf("\n[INFO] Nasabah '%s' telah selesai dilayani dan dihapus dari antrian.\n", nasabah.nama_nasabah);

    if (queue->front == queue->rear) {
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % MAX_ANTRIAN;
    }
}

void peek(AntrianBank *queue) {
    if (isEmpty(queue)) {
        printf("\n[ERROR] Antrian kosong. Tidak ada nasabah untuk dilihat.\n");
        return;
    }

    Nasabah nasabah = queue->antrian[queue->front];
    printf("\n[INFO] Nasabah berikutnya:\n");
    printf("ID: %d | Nama: %s | Nomor Antrian: %d | Layanan: %s | Waktu: %s | Status: %s\n",
           nasabah.id_nasabah, nasabah.nama_nasabah, nasabah.nomor_antrian,
           nasabah.jenis_layanan, nasabah.waktu_kedatangan, nasabah.status);
}

void peekAll(AntrianBank *queue) {
    if (isEmpty(queue)) {
        printf("\n[ERROR] Antrian kosong. Tidak ada nasabah untuk ditampilkan.\n");
        return;
    }

    printf("\n=== Daftar Semua Nasabah dalam Antrian ===\n");
    printf("No. | ID  | Nama Nasabah         | Layanan          | Waktu             | Status\n");
    printf("-------------------------------------------------------------------------\n");
    for (int i = queue->front; ; i = (i + 1) % MAX_ANTRIAN) {
        Nasabah nasabah = queue->antrian[i];
        printf("%-3d | %-3d | %-20s | %-15s | %-17s | %-10s\n",
               i + 1, nasabah.id_nasabah, nasabah.nama_nasabah,
               nasabah.jenis_layanan, nasabah.waktu_kedatangan, nasabah.status);
        if (i == queue->rear) break;
    }
}
