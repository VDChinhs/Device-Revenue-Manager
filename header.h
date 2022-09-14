#include<iostream>
#include<fstream>
#include<iomanip>
#define FILENAME "D:\\123\\MaHang.txt"
using namespace std;

struct MatHang{
	string Ma_Mat_Hang;
	string Ten_Mat_Hang;
	int SoLuong[100];	
	int DonGia;
};

bool checktrungma(MatHang a[],int mhdangnhap,string m);
string Chuyen_Tien(long a);
bool kiemtrachu(string chuoi);
void NhapMatHang(MatHang &hh, MatHang a[], int mhdangnhap);
int tong1mhban_Mngay(int So_Ngay, MatHang mh);
void Tk_Ma_Mat_Hang(MatHang mh[], int So_Hang,int songay, string mmh);
string bandcnhieunhattrongngay(int So_Ngay, int So_Hang, MatHang a[]);
void XuatBang(MatHang a[],int So_Ngay,int So_Hang);
float Total_Prize(int So_Ngay, int So_Hang, MatHang a[]);
int Ngaybannhieunhat(int So_Ngay, int So_Hang, MatHang a[]);
int Docsongaytrongfile();
int Somhanginfile();
void DocFile(MatHang a[], int So_Ngay);
void LuuFile(MatHang a[],int So_Ngay,int So_Hang);
void Themtheongay(MatHang a[], int daycu, int daymoi,int So_Hang);
void quanlythongke(int So_Ngay, int So_Hang, MatHang a[]);
void reset();
void XuatraFile(int So_Ngay, int So_Hang, MatHang a[]);
