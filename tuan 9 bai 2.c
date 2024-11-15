#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tu {
    char vanBan[50]; 
    struct Tu* tiepTheo;
} Tu;

typedef struct Cau {
    Tu* dau;
} Cau;

// Khởi tạo câu
void khoiTaoCau(Cau* cau) {
    cau->dau = NULL;
}

// Thêm từ vào câu
void themTu(Cau* cau, char* vanBan) {
    Tu* tuMoi = (Tu*)malloc(sizeof(Tu));
    strcpy(tuMoi->vanBan, vanBan);
    tuMoi->tiepTheo = NULL;

    if (cau->dau == NULL) {
        cau->dau = tuMoi;
    } else {
        Tu* hienTai = cau->dau;
        while (hienTai->tiepTheo != NULL) {
            hienTai = hienTai->tiepTheo;
        }
        hienTai->tiepTheo = tuMoi;
    }
}

// Tìm từ xuất hiện nhiều nhất
char* timTuXuatHienNhieuNhat(Cau* cau) {
    Tu* hienTai = cau->dau;
    Tu* tuMax = NULL;
    int maxSoLan = 0;
    int dem[50] = {0};
    char* tuNhieuNhat = NULL;

    while (hienTai != NULL) {
        int soLan = 1;
        Tu* khac = cau->dau;
        while (khac != NULL) {
            if (strcmp(hienTai->vanBan, khac->vanBan) == 0) {
                soLan++;
            }
            khac = khac->tiepTheo;
        }

        if (soLan > maxSoLan) {
            maxSoLan = soLan;
            tuNhieuNhat = hienTai->vanBan;
        }
        hienTai = hienTai->tiepTheo;
    }
    return tuNhieuNhat;
}

// Loại bỏ từ láy
void loaiBoTuLay(Cau* cau) {
    Tu* hienTai = cau->dau;
    while (hienTai != NULL && hienTai->tiepTheo != NULL) {
        if (strcmp(hienTai->vanBan, hienTai->tiepTheo->vanBan) == 0) {
            Tu* tuBiXoa = hienTai->tiepTheo;
            hienTai->tiepTheo = hienTai->tiepTheo->tiepTheo;
            free(tuBiXoa);
        } else {
            hienTai = hienTai->tiepTheo;
        }
    }
}

// Đếm số từ khác nhau trong câu
int demSoTuKhacNhau(Cau* cau) {
    int soTu = 0;
    Tu* hienTai = cau->dau;
    while (hienTai != NULL) {
        int trungLap = 0;
        Tu* kiemTra = cau->dau;
        while (kiemTra != hienTai) {
            if (strcmp(hienTai->vanBan, kiemTra->vanBan) == 0) {
                trungLap = 1;
                break;
            }
            kiemTra = kiemTra->tiepTheo;
        }
        if (!trungLap) {
            soTu++;
        }
        hienTai = hienTai->tiepTheo;
    }
    return soTu;
}
