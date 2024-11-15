#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TepTin {
    char ten[50];          // Tên tệp tin
    int kichThuoc;         // Kích thước tệp tin (MB)
    char thoiGianTao[20];  // Thời gian tạo tệp tin
    struct TepTin* tiepTheo;
} TepTin;

typedef struct ThuMuc {
    TepTin* dau;
} ThuMuc;

// Khởi tạo thư mục
void khoiTaoThuMuc(ThuMuc* thuMuc) {
    thuMuc->dau = NULL;
}

// Thêm tệp tin vào thư mục theo thời gian
void themTep(ThuMuc* thuMuc, char* ten, int kichThuoc, char* thoiGianTao) {
    TepTin* tepMoi = (TepTin*)malloc(sizeof(TepTin));
    strcpy(tepMoi->ten, ten);
    tepMoi->kichThuoc = kichThuoc;
    strcpy(tepMoi->thoiGianTao, thoiGianTao);
    tepMoi->tiepTheo = NULL;

    if (thuMuc->dau == NULL || strcmp(thuMuc->dau->thoiGianTao, thoiGianTao) > 0) {
        tepMoi->tiepTheo = thuMuc->dau;
        thuMuc->dau = tepMoi;
    } else {
        TepTin* hienTai = thuMuc->dau;
        while (hienTai->tiepTheo != NULL && strcmp(hienTai->tiepTheo->thoiGianTao, thoiGianTao) <= 0) {
            hienTai = hienTai->tiepTheo;
        }
        tepMoi->tiepTheo = hienTai->tiepTheo;
        hienTai->tiepTheo = tepMoi;
    }
}

// Tính tổng kích thước tệp tin trong thư mục
int tinhTongKichThuoc(ThuMuc* thuMuc) {
    int tongKichThuoc = 0;
    TepTin* hienTai = thuMuc->dau;
    while (hienTai != NULL) {
        tongKichThuoc += hienTai->kichThuoc;
        hienTai = hienTai->tiepTheo;
    }
    return tongKichThuoc;
}

// Loại bỏ tệp tin nhỏ nhất nếu dung lượng vượt quá giới hạn USB
void toiUuChoUSB(ThuMuc* thuMuc, int kichThuocUSB) {
    int tongKichThuoc = tinhTongKichThuoc(thuMuc);
    while (tongKichThuoc > kichThuocUSB * 1024) {
        TepTin* tepNhoNhat = thuMuc->dau;
        TepTin* truocTepNhoNhat = NULL;
        TepTin* hienTai = thuMuc->dau;
        TepTin* truoc = NULL;

        while (hienTai != NULL) {
            if (hienTai->kichThuoc < tepNhoNhat->kichThuoc) {
                tepNhoNhat = hienTai;
                truocTepNhoNhat = truoc;
            }
            truoc = hienTai;
            hienTai = hienTai->tiepTheo;
        }

        if (truocTepNhoNhat != NULL) {
            truocTepNhoNhat->tiepTheo = tepNhoNhat->tiepTheo;
        } else {
            thuMuc->dau = tepNhoNhat->tiepTheo;
        }
        tongKichThuoc -= tepNhoNhat->kichThuoc;
        free(tepNhoNhat);
    }
}
