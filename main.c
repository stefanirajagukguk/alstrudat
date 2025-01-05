#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "antrian.h"

void printMenu() {
    printf("\n=== Sistem Antrian Bank ===\n");
    printf("1. Tambah Nasabah\n");
    printf("2. Layani Nasabah\n");
    printf("3. Lihat Nasabah Berikutnya\n");
    printf("4. Lihat Semua Antrian\n");
    printf("5. Keluar\n");
    printf("Pilih menu (1-5): ");
}

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

int main() {
    AntrianBank queue;
    initAntrian(&queue);

    int pilihan;
    int id_counter = 1;

    do {
        printMenu();
        if (scanf("%d", &pilihan) != 1) {
            printf("\n[ERROR] Input tidak valid. Harap masukkan angka 1-5.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (pilihan == 1) {
            Nasabah nasabah;
            nasabah.id_nasabah = id_counter++;
            printf("Masukkan nama nasabah: ");
            fgets(nasabah.nama_nasabah, sizeof(nasabah.nama_nasabah), stdin);
            nasabah.nama_nasabah[strcspn(nasabah.nama_nasabah, "\n")] = 0; // Hapus newline

            printf("Masukkan jenis layanan (teller/customer service): ");
            fgets(nasabah.jenis_layanan, sizeof(nasabah.jenis_layanan), stdin);
            nasabah.jenis_layanan[strcspn(nasabah.jenis_layanan, "\n")] = 0; // Hapus newline

            nasabah.nomor_antrian = id_counter - 1;
            getCurrentTime(nasabah.waktu_kedatangan);
            strcpy(nasabah.status, "Menunggu");
            addQueue(&queue, nasabah);
        } else if (pilihan == 2) {
            delQueue(&queue);
        } else if (pilihan == 3) {
            peek(&queue);
        } else if (pilihan == 4) {
            peekAll(&queue);
        } else if (pilihan == 5) {
            printf("\n[INFO] Terima kasih telah menggunakan sistem antrian.\n");
        } else {
            printf("\n[ERROR] Pilihan tidak valid. Harap pilih angka 1-5.\n");
        }
    } while (pilihan != 5);

    return 0;
}
