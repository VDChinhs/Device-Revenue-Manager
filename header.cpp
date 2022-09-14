#include "header.h"
//kiem tra ma mat hang trung nhau khong
bool checktrungma(MatHang a[],int mhdangnhap,string m){
	bool thongbao;
	for(int i = 0; i < mhdangnhap; i++){
		if (a[i].Ma_Mat_Hang == m){
			return true;
		}
		else thongbao = false;
	}
	return thongbao;
}
//kiem tra co ky tu chu khong
bool kiemtrachu(string chuoi){
	bool bao;
	for(int i = 0; i < chuoi.length(); i++ ){
		if(static_cast<int>(chuoi[i]) < 48 || static_cast<int>(chuoi[i]) > 57){
			return true;
		}
		else bao = false;
	}
	return bao;
}
void NhapMatHang(MatHang &hh, MatHang a[], int mhdangnhap){
	string kiemtra;
	cout<<"Nhap ma mat hang: ";
	cin>>hh.Ma_Mat_Hang;
	while (checktrungma(a,mhdangnhap,hh.Ma_Mat_Hang))
	{	
		cout<<"Nhap lai ma mat hang: ";	
		cin>>hh.Ma_Mat_Hang;
	}
	cin.ignore();
	cout<<"Nhap ten mat hang: ";
	getline(cin,hh.Ten_Mat_Hang);
	cout<<"Nhap gia ban: ";
	cin>>kiemtra;
	while(kiemtrachu(kiemtra)){
		cout<<"Nhap lai gia ban: ";
		cin>>kiemtra;
	}
	hh.DonGia = stoi(kiemtra);
}
//tinh tong so luong cua 1 mat hang trong tat ca cac ngay
int tong1mhban_Mngay(int So_Ngay, MatHang mh){
	int total = 0;
	for (int i = 0; i < So_Ngay; i++){
		total+=mh.SoLuong[i];
	}
	return total;
}
//tim kiem theo ma
void Tk_Ma_Mat_Hang(MatHang mh[], int So_Hang,int songay, string mmh){
	int k=0;
	for(int i=0;i<So_Hang;i++){
		if(mmh== mh[i].Ma_Mat_Hang){
			cout<<"Ma mat hang "<<mh[i].Ma_Mat_Hang << " co ten "<<mh[i].Ten_Mat_Hang<<" co gia "<<Chuyen_Tien(mh[i].DonGia)<<" ban duoc "<<tong1mhban_Mngay(songay,mh[i])<<" san pham"<<endl;
			k++;
			break;
		}
	}
	if(k==0) cout<<"Not found";
}
//tinh mat hang ban duoc nhieu nhat moi ngay
string bandcnhieunhattrongngay(int So_Ngay, int So_Hang, MatHang a[]){
	string Ten_mh = a[0].Ten_Mat_Hang;
	int soluong = a[0].SoLuong[So_Ngay];
		for (int j = 0; j < So_Hang-1; j++){
			if (a[j].SoLuong[So_Ngay] < a[j+1].SoLuong[So_Ngay] ){
				Ten_mh = a[j+1].Ten_Mat_Hang;
				soluong = a[j+1].SoLuong[So_Ngay];
			}
		}
		string chuoi = Ten_mh + " (" + to_string(soluong) +" san pham"+ ")";
	return chuoi;
}
//Chuyen tien
string Chuyen_Tien(long a){
	int count1 =0;
	int count2 = 3;
	int i =1000;
	string b = to_string(a);
	if(b.length()/3!=0){
		while(a/i>0){
            if(b.length()-count2>0){
			    b.insert(b.length()-count2,",");
			    i*=1000;
			    count2+=4;
            }
		}
	}
	return b;
}
void XuatBang(MatHang a[],int So_Ngay,int So_Hang){
		cout<<"Ngay "<<So_Ngay+1<<endl;
		cout<<"+-----------------------+-----------------------+-----------------------+-----------------------+-----------------------+"<<endl;
		cout<<"|\tMa Mat Hang\t|\tTen Mat Hang\t|\tDon Gia \t| \tSo Luong\t|\tThanh Tien\t|"<<endl;
		cout<<"+-----------------------+-----------------------+-----------------------+-----------------------+-----------------------+"<<endl;
		for(int j = 0; j < So_Hang; j++){
			cout<<"|"<<setw(15)<<a[j].Ma_Mat_Hang<<setw(9)<<"\t|"<<setw(15)<<a[j].Ten_Mat_Hang<<setw(9)<<"\t|"<<setw(15)<<Chuyen_Tien(a[j].DonGia)<<setw(9)<<"\t|"<<setw(12)<<a[j].SoLuong[So_Ngay]<<setw(9)<<"\t|"<<setw(16)<<Chuyen_Tien(a[j].SoLuong[So_Ngay]*a[j].DonGia)<<setw(2)<<"\t|"<<endl;
		}
	cout<<"+-----------------------+-----------------------+-----------------------+-----------------------+-----------------------+"<<endl<<endl;
}
//tinh tong tien thu dc trong 1 ngay
float Total_Prize(int So_Ngay, int So_Hang, MatHang a[]){
	float Total = 0;
	for( int i=0; i< So_Hang;i++) { 
		Total += a[i].SoLuong[So_Ngay] * a[i].DonGia;
	} 
	return Total;
}
//ngay ban duoc nhieu nhat
int Ngaybannhieunhat(int So_Ngay, int So_Hang, MatHang a[]){
	int Ngay_max = 1;
	for(int i = 0; i < So_Ngay-1;i++){
		if(Total_Prize(i,So_Hang,a) < Total_Prize((i+1),So_Hang,a)){
			Ngay_max = i+2;
		}
	}
	return Ngay_max;
}
//dem so ngay dang co trong file
int Docsongaytrongfile(){
	int songayluu;
	ifstream filein;
	filein.open(FILENAME,ios::in);
	filein>>songayluu;
	return songayluu;
}
//dem so mat hang dang co trong fifle
int Somhanginfile(){
	int i=0;
	string line;
	string bo;
	fstream filein(FILENAME);
	if (filein.fail()){
		cout << "Khong ton tai co file nay(songay)";
	}	
	getline(filein,bo,'\n');
	while(!filein.eof()){
		getline(filein,line);
		i++;
	}
	return i-1;
	filein.close();
}
//doc du lieu truyen lai vao mang Mathang kieu struc
void DocFile(MatHang a[], int So_Ngay){
	string bo;
	fstream filein(FILENAME);
	if (filein.fail()){
		cout << "Khong ton tai co file nay(docfile)";
	}
		getline(filein,bo,'\n');
		for (int i = 0; i < Somhanginfile(); i++){
		getline(filein, a[i].Ma_Mat_Hang,'\t');
		getline(filein, a[i].Ten_Mat_Hang,'\t');
		filein>>a[i].DonGia;
		for(int j = 0; j < So_Ngay; j++){
			filein>>a[i].SoLuong[j] ;
		}
		filein.ignore();
		}
	filein.close();
}
//luufile
void LuuFile(MatHang a[],int So_Ngay,int So_Hang){
	ofstream fileout;
	fileout.open(FILENAME,ios::out);
	fileout<<So_Ngay<<endl;
	for(int i = 0; i < So_Hang; i++){
		fileout<<a[i].Ma_Mat_Hang<<"\t"<<a[i].Ten_Mat_Hang<<"\t"<<a[i].DonGia;
		for(int j = 0; j < So_Ngay; j++){
			fileout<<"\t"<<a[i].SoLuong[j];
		}
		fileout<<endl;
	}
	fileout.close();
	cout<<"-Luu File thanh cong-"<<endl;
	system("pause");
}
//them theo ngay
void Themtheongay(MatHang a[], int daycu, int daymoi,int So_Hang){
	string kiemtra;
	for(int i = daycu; i < (daycu + daymoi); i++){
		for(int j = 0; j < So_Hang;j++){
			cout<< a[j].Ten_Mat_Hang <<" vao ngay thu "<<i+1<<" ban duoc :";
			cin>>kiemtra;
			while (kiemtrachu(kiemtra)){
				cout<< a[j].Ten_Mat_Hang <<" vao ngay thu "<<i+1<<" ban duoc :";
				cin>>kiemtra;
			}
			a[j].SoLuong[i] = stoi(kiemtra);
		}
	}
}
// quan ly thong ke
void quanlythongke(int So_Ngay, int So_Hang, MatHang a[]){
	ofstream xuatfile;
	int choose;
	bool h = true;
	// mat hang ban it nhat
	int min2 = tong1mhban_Mngay(So_Ngay,a[0]);
	string Ten_mh2 = a[0].Ten_Mat_Hang;
		for (int i = 0; i < So_Hang-1; i++){
			if (min2 > tong1mhban_Mngay(So_Ngay,a[i+1])){
				min2 =  tong1mhban_Mngay(So_Ngay,a[i+1]);
				Ten_mh2 = a[i+1].Ten_Mat_Hang;
			}
		}
	// mat hang ban nhieu nhat
	int max3 = tong1mhban_Mngay(So_Ngay,a[0]);
	string Ten_mh3 = a[0].Ten_Mat_Hang;
		for (int i = 0; i < So_Hang-1; i++){
			if (max3 < tong1mhban_Mngay(So_Ngay,a[i+1])){
				max3 =  tong1mhban_Mngay(So_Ngay,a[i+1]);
				Ten_mh3 = a[i+1].Ten_Mat_Hang;
			}
		}
	// mat hang ban it tien nhat
	int min4 = tong1mhban_Mngay(So_Ngay,a[0])*a[0].DonGia;
	string Ten_mh4 = a[0].Ten_Mat_Hang;
		for (int i = 0; i < So_Hang-1; i++){				
			if (min4 > tong1mhban_Mngay(So_Ngay,a[i+1])*a[i+1].DonGia){
				min4 =  tong1mhban_Mngay(So_Ngay,a[i+1])*a[i+1].DonGia;
				Ten_mh4 = a[i+1].Ten_Mat_Hang;
			}
		}
	// mat hang ban nhieu tien nhat
	int max5 = tong1mhban_Mngay(So_Ngay,a[0])*a[0].DonGia;
	string Ten_mh5 = a[0].Ten_Mat_Hang;
		for (int i = 0; i < So_Hang-1; i++){
			if (max5 < tong1mhban_Mngay(So_Ngay,a[i+1])*a[i+1].DonGia){
				max5 =  tong1mhban_Mngay(So_Ngay,a[i+1])*a[i+1].DonGia;
				Ten_mh5 = a[i+1].Ten_Mat_Hang;
			}
		}
	// tong mat hang ban duoc
	int Tongmh = 0;
		for(int i = 0; i <So_Hang; i++){
			Tongmh+=tong1mhban_Mngay(So_Ngay,a[i]);
		}
	// tong tien thu duoc
	unsigned long Tongtien = 0;
		for(int i = 0; i <So_Hang; i++){
			Tongtien+=tong1mhban_Mngay(So_Ngay,a[i])*a[i].DonGia;
		}
	
	xuatfile.open("D://123//Thongke.txt",ios::out);
	for(int i = 0; i < So_Ngay; i++){
		xuatfile<<"Ngay "<<i+1<<endl;
		xuatfile<<"+-----------------------+-----------------------+-----------------------+-----------------------+-----------------------+"<<endl;
		xuatfile<<"|\tMa Mat Hang\t|\tTen Mat Hang\t|\tDon Gia \t| \tSo Luong\t|\tThanh Tien\t|"<<endl;
		xuatfile<<"+-----------------------+-----------------------+-----------------------+-----------------------+-----------------------+"<<endl;
			for(int j = 0; j < So_Hang; j++){
				xuatfile<<"|"<<setw(15)<<a[j].Ma_Mat_Hang<<setw(9)<<"\t|"<<setw(15)<<a[j].Ten_Mat_Hang<<setw(9)<<"\t|"<<setw(15)<<Chuyen_Tien(a[j].DonGia)<<setw(9)<<"\t|"<<setw(12)<<a[j].SoLuong[i]<<setw(9)<<"\t|"<<setw(16)<<Chuyen_Tien(a[j].SoLuong[i]*a[j].DonGia)<<setw(2)<<"\t|"<<endl;
			}
		xuatfile<<"+-----------------------+-----------------------+-----------------------+-----------------------+-----------------------+"<<endl<<endl;
	}
	xuatfile<<"Ngay ban duoc nhieu tien nhat : "<<Ngaybannhieunhat(So_Ngay,So_Hang,a)<<endl;
	xuatfile<<"Mat hang ban duoc it nhat la: "<<Ten_mh2<<endl;
	xuatfile<<"Mat hang ban duoc nhieu nhat la: "<<Ten_mh3<<endl;
	xuatfile<<"Mat hang ban duoc it tien nhat la: "<<Ten_mh4<<endl;
	xuatfile<<"Mat hang ban duoc nhieu tien nhat la: "<<Ten_mh5<<endl;
	xuatfile<<"Tong so mat hanh ban dc la: "<<Tongmh<<endl;
	xuatfile<<"Tong so tien thu dc la: "<<Chuyen_Tien(Tongtien)<<endl;
	
	while(h){
		system("pause");
		system("cls");
		cout<<"================================"<<endl;
		cout<<"1. Ngay ban nhieu tien nhat"<<endl;
		cout<<"2. Mat hang ban it nhat"<<endl;
		cout<<"3. Mat hang ban nhieu nhat"<<endl;
		cout<<"4. Mat hang ban it tien nhat"<<endl;
		cout<<"5. Mat hang ban nhieu tien nhat"<<endl;
		cout<<"6. Mat hang ban dc nhieu nhat moi ngay"<<endl; 
		cout<<"7. Tong mat hang ban dc"<<endl;
		cout<<"8. Tong tien thu dc "<<endl;
		cout<<"9. Thoat"<<endl;
		cout<<"Chon: ";
		cin>>choose;
		switch(choose){
			case 1:
				cout<<"Ngay ban duoc nhieu nhat : Ngay "<<Ngaybannhieunhat(So_Ngay,So_Hang,a)<<endl;
				break;
			case 2:
				cout<<"Mat hang ban duoc it nhat la: "<<Ten_mh2<<endl;
				break;
			case 3:
				cout<<"Mat hang ban duoc nhieu nhat la: "<<Ten_mh3<<endl;
				break;
			case 4:
				cout<<"Mat hang ban duoc it tien nhat la: "<<Ten_mh4<<endl;
				break;
			case 5:		
				cout<<"Mat hang ban duoc nhieu tien nhat la: "<<Ten_mh5<<endl;
				break;
			case 6:
				for (int i = 0; i < So_Ngay; i++){
					cout<<"Ngay "<< (i + 1) << " : "<<bandcnhieunhattrongngay(i,So_Hang,a)<<endl;
				}
				break;
			case 7:
				cout<<"Tong so mat hang ban dc la: "<<Tongmh<<endl;
				break;
			case 8:	
				cout<<"Tong so tien thu dc la: "<<Chuyen_Tien(Tongtien)<<endl;
				break;
			case 9:
				h = false;
				break;
		}
	}
}
void reset(){
	fstream fileout1(FILENAME,ios::out);
}
