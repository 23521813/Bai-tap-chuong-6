#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Lớp cơ sở NhanVien
class NhanVien {
protected:
    string maNV;
    string hoTen;
    int tuoi;
    string soDienThoai;
    string email;
    float luongCoBan;
public:
    NhanVien(string maNV, string hoTen, int tuoi, string soDienThoai, string email, float luongCoBan)
        : maNV(maNV), hoTen(hoTen), tuoi(tuoi), soDienThoai(soDienThoai), email(email), luongCoBan(luongCoBan) {}
    virtual float tinhLuong() const = 0;
    virtual void xuatThongTin() const = 0;
    float getLuongCoBan() const {
        return luongCoBan;
    }
};

// Lớp LapTrinhVien kế thừa từ NhanVien
class LapTrinhVien : public NhanVien {
private:
    int SoGioLamThem;
public:
    LapTrinhVien(string maNV, string hoTen, int tuoi, string soDienThoai, string email, float luongCoBan, int SoGioLamThem)
        : NhanVien(maNV, hoTen, tuoi, soDienThoai, email, luongCoBan), SoGioLamThem(SoGioLamThem) {}
    float tinhLuong() const override {
        return luongCoBan + SoGioLamThem * 200000;
    }
    void xuatThongTin() const override {
        cout << "Lap Trinh Vien: " << hoTen << "\n Ma NV: " << maNV << "\n Luong: " << tinhLuong() << endl;
    }
};

// Lớp KiemChungVien kế thừa từ NhanVien
class KiemChungVien : public NhanVien {
private:
    int soLoiPhatHien;
public:
    KiemChungVien(string maNV, string hoTen, int tuoi, string soDienThoai, string email, float luongCoBan, int soLoiPhatHien)
        : NhanVien(maNV, hoTen, tuoi, soDienThoai, email, luongCoBan), soLoiPhatHien(soLoiPhatHien) {}
    float tinhLuong() const override {
        return luongCoBan + soLoiPhatHien * 50000;
    }
    void xuatThongTin() const override {
        cout << "Kiem Chung Vien: " << hoTen << "\n Ma NV: " << maNV << "\n Luong: " << tinhLuong() << endl;
    }
};

// Chương trình chính
int main() {
    vector<NhanVien*> danhSachNhanVien;
    int luaChon;
    float tongLuong = 0;
    int soLuongNV = 0;
    // Nhập danh sách nhân viên
    do {
        cout << "Nhap 1 de them Lap Trinh Vien, 2 de them Kiem Chung Vien, 0 de ket thuc: ";
        cin >> luaChon;
        if (luaChon == 1) {
            string maNV, hoTen, soDienThoai, email;
            int tuoi, SoGioLamThem;
            float luongCoBan;
            cout << "Nhap ma NV: "; cin >> maNV;
            cout << "Nhap ho ten: "; cin.ignore(); getline(cin, hoTen);
            cout << "Nhap tuoi: "; cin >> tuoi;
            cout << "Nhap so dien thoai: "; cin >> soDienThoai;
            cout << "Nhap email: "; cin >> email;
            cout << "Nhap luong co ban: "; cin >> luongCoBan;
            cout << "Nhap so gio lam them: "; cin >> SoGioLamThem;
            danhSachNhanVien.push_back(new LapTrinhVien(maNV, hoTen, tuoi, soDienThoai, email, luongCoBan, SoGioLamThem));
        } else if (luaChon == 2) {
            string maNV, hoTen, soDienThoai, email;
            int tuoi, soLoiPhatHien;
            float luongCoBan;
            cout << "Nhap ma NV: "; cin >> maNV;
            cout << "Nhap ho ten: "; cin.ignore(); getline(cin, hoTen);
            cout << "Nhap tuoi: "; cin >> tuoi;
            cout << "Nhap so dien thoai: "; cin >> soDienThoai;
            cout << "Nhap email: "; cin >> email;
            cout << "Nhap luong co ban: "; cin >> luongCoBan;
            cout << "Nhap so loi phat hien: "; cin >> soLoiPhatHien;
            danhSachNhanVien.push_back(new KiemChungVien(maNV, hoTen, tuoi, soDienThoai, email, luongCoBan, soLoiPhatHien));
        }
    } while (luaChon);
    // Tính tổng lương và số lượng nhân viên để tìm lương trung bình
    for (const auto& nv : danhSachNhanVien) {
        tongLuong += nv->tinhLuong();
        soLuongNV++;
    }
    float luongTrungBinh = tongLuong / soLuongNV;
    // Xuất danh sách nhân viên
    cout << "\nDanh sach nhan vien:\n";
    for (const auto& nv : danhSachNhanVien) {
        nv->xuatThongTin();
    }
    // Liệt kê nhân viên có lương thấp hơn lương trung bình
    cout << "\nNhan vien co luong thap hon luong trung binh (" << luongTrungBinh << "):\n";
    for (const auto& nv : danhSachNhanVien) {
        if (nv->tinhLuong() < luongTrungBinh) {
            nv->xuatThongTin();
        }
    }
    return 0;
}
