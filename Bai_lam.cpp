#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Lớp cơ sở NhanVien
class NhanVien {
protected:
    string Manhanvien;
    string Hoten;
    int Tuoi;
    string Sodienthoai;
    string Email;
    float Luongcoban;
public:
    NhanVien(string Manhanvien, string Hoten, int Tuoi, string Sodienthoai, string Email, float Luongcoban)
        : Manhanvien(Manhanvien), Hoten(Hoten), Tuoi(Tuoi), Sodienthoai(Sodienthoai), Email(Email), Luongcoban(Luongcoban) {}
    virtual float tinhLuong() const = 0;
    virtual void xuatThongTin() const = 0;
    float getLuongcoban() const {
        return Luongcoban;
    }
};

// Lớp LapTrinhVien kế thừa từ NhanVien
class LapTrinhVien : public NhanVien {
private:
    int Sogiolamthem;
public:
    LapTrinhVien(string Manhanvien, string Hoten, int Tuoi, string Sodienthoai, string Email, float Luongcoban, int Sogiolamthem)
        : NhanVien(Manhanvien, Hoten, Tuoi, Sodienthoai, Email, Luongcoban), Sogiolamthem(Sogiolamthem) {}
    float tinhLuong() const override {
        return Luongcoban + Sogiolamthem * 200000;
    }
    void xuatThongTin() const override {
        cout << "Lap Trinh Vien: " << Hoten << "\n Ma NV: " << Manhanvien << "\n Luong: " << tinhLuong() << endl;
    }
};

// Lớp KiemChungVien kế thừa từ NhanVien
class KiemChungVien : public NhanVien {
private:
    int Soloiphathien;
public:
    KiemChungVien(string Manhanvien, string Hoten, int Tuoi, string Sodienthoai, string Email, float Luongcoban, int Soloiphathien)
        : NhanVien(Manhanvien, Hoten, Tuoi, Sodienthoai, Email, Luongcoban), Soloiphathien(Soloiphathien) {}
    float tinhLuong() const override {
        return Luongcoban + Soloiphathien * 50000;
    }
    void xuatThongTin() const override {
        cout << "Kiem Chung Vien: " << Hoten << "\n Ma NV: " << Manhanvien << "\n Luong: " << tinhLuong() << endl;
    }
};

// Chương trình chính
int main() {
    vector<NhanVien*> ds;
    int luaChon;
    float tongLuong = 0;
    int soLuongNV = 0;
    // Nhập danh sách nhân viên
    do {
        cout << "Nhap 1 de them Lap Trinh Vien, 2 de them Kiem Chung Vien, 0 de ket thuc: ";
        cin >> luaChon;
        if (luaChon == 1) {
            string Manhanvien, Hoten, Sodienthoai, Email;
            int Tuoi, Sogiolamthem;
            float Luongcoban;
            cout << "Nhap ma NV: "; cin >> Manhanvien;
            cout << "Nhap ho ten: "; cin.ignore(); getline(cin, Hoten);
            cout << "Nhap Tuoi: "; cin >> Tuoi;
            cout << "Nhap so dien thoai: "; cin >> Sodienthoai;
            cout << "Nhap Email: "; cin >> Email;
            cout << "Nhap luong co ban: "; cin >> Luongcoban;
            cout << "Nhap so gio lam them: "; cin >> Sogiolamthem;
            ds.push_back(new LapTrinhVien(Manhanvien, Hoten, Tuoi, Sodienthoai, Email, Luongcoban, Sogiolamthem));
        } else if (luaChon == 2) {
            string Manhanvien, Hoten, Sodienthoai, Email;
            int Tuoi, Soloiphathien;
            float Luongcoban;
            cout << "Nhap ma NV: "; cin >> Manhanvien;
            cout << "Nhap ho ten: "; cin.ignore(); getline(cin, Hoten);
            cout << "Nhap Tuoi: "; cin >> Tuoi;
            cout << "Nhap so dien thoai: "; cin >> Sodienthoai;
            cout << "Nhap Email: "; cin >> Email;
            cout << "Nhap luong co ban: "; cin >> Luongcoban;
            cout << "Nhap so loi phat hien: "; cin >> Soloiphathien;
            ds.push_back(new KiemChungVien(Manhanvien, Hoten, Tuoi, Sodienthoai, Email, Luongcoban, Soloiphathien));
        }
    } while (luaChon);
    // Tính tổng lương và số lượng nhân viên để tìm lương trung bình
    for (const auto& nv : ds) {
        tongLuong += nv->tinhLuong();
        soLuongNV++;
    }
    float luongTrungBinh = tongLuong / soLuongNV;
    // Xuất danh sách nhân viên
    cout << "\nDanh sach nhan vien:\n";
    for (const auto& nv : ds) {
        nv->xuatThongTin();
    }
    // Liệt kê nhân viên có lương thấp hơn lương trung bình
    cout << "\nNhan vien co luong thap hon luong trung binh (" << luongTrungBinh << "):\n";
    for (const auto& nv : ds) {
        if (nv->tinhLuong() < luongTrungBinh) {
            nv->xuatThongTin();
        }
    }
    return 0;
}
