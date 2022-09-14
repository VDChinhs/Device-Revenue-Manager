#include"header.h"

int main(){
	system("cls");
	///tao file
	fstream fileout(FILENAME,ios::app);

	MatHang mh[100];
	int answer, daymoi, spmoi;
	int So_Ngay = 0;
	int So_Hang = 0;
	int daycu = Docsongaytrongfile();
	int spcu = Somhanginfile();
	int Tong_ngay = 0;
	int Tong_sp = 0;
	bool checkluu = false;
	if(spcu == -1){
		daycu = 0;
		spcu = 0;
	}
	if(daycu > 0){
		DocFile(mh,daycu);
		cout<<"-Doc file thanh cong-"<<endl;
	}
	while (true){
		Tong_ngay = So_Ngay + daycu;
		Tong_sp = So_Hang + spcu;
		system("cls");
		cout<<"So ngay dang quan ly: "<<Tong_ngay<<endl<<"So mat hang dang quan ly: "<<Tong_sp<<endl;
		cout<<"Chuong trinh quan ly cua hang dien may "<<endl;
		cout<<"--------MENU--------"<<endl;
		cout<<"1. Nhap/ Them"<<endl;
		cout<<"2. Xem toan bo"<<endl;
		cout<<"3. Tim kiem"<<endl;
		cout<<"4. Thong ke/ Xuat ra File"<<endl;
		cout<<"5. Luu du lieu"<<endl;
		cout<<"6. Reset"<<endl;
		cout<<"7. Thoat"<<endl;
		cout<<"Ban muon thuc hien thao tac nao"<<endl;
		cout<<"Nhap so ung voi thao tac: ";
		cin>> answer;
		switch (answer){
			case 1:
				checkluu = true;
				if(Tong_ngay > 0){
					system("cls");
					int chon;
					cout<<"1.Them ngay"<<endl<<"2.Them san pham"<<endl;
					cout<<"Chon: ";
					cin>>chon;
					if(chon == 1){
						cout<<"Ban muon nhap them may ngay: ";
						cin>>daymoi;
						Themtheongay(mh,Tong_ngay,daymoi,Tong_sp);
						daycu = daycu + daymoi;
					}
					else if(chon == 2){
						system("cls");
						string kiemtra;
						cout<<"Ban muon them may san pham: ";
						cin>>spmoi;
						for (int i = Tong_sp; i < (Tong_sp + spmoi); i++){
							cout<<"Nhap thong tin mat hang "<<i+1<<" :"<<endl;
							NhapMatHang(mh[i],mh,i);
							system("cls");
						}
						for (int i = Tong_ngay-1; i < Tong_ngay; i++){
							for(int j =Tong_sp; j < Tong_sp + spmoi; j++){
								cout<< mh[j].Ten_Mat_Hang <<" vao ngay thu "<<i+1<<" ban duoc :";
								cin>>kiemtra;
								while (kiemtrachu(kiemtra)){
									cout<< mh[j].Ten_Mat_Hang <<" vao ngay thu "<<i+1<<" ban duoc :";
									cin>>kiemtra;
								}
								mh[j].SoLuong[i] = stoi(kiemtra);
							}
						}
						spcu = spcu + spmoi;
					}
				}
				else{
					string kiemtra;
					cout<<"Nhap so ngay can quan ly: ";
					cin>>So_Ngay;
					cout<<"Nhap so mat hang co san : ";
					cin>>So_Hang;
					system("cls");
					for (int i = 0; i < So_Hang; i++){
						cout<<"Nhap thong tin mat hang "<<i+1<<" :"<<endl;
						NhapMatHang(mh[i],mh,i);
						system("cls");
					}
					for (int i = 0; i < So_Ngay;i ++){
						for(int j =0; j < So_Hang; j++){
							cout<< mh[j].Ten_Mat_Hang <<" vao ngay thu "<<i+1<<" ban duoc :";
							cin>>kiemtra;
							while (kiemtrachu(kiemtra))
							{
								cout<< mh[j].Ten_Mat_Hang <<" vao ngay thu "<<i+1<<" ban duoc :";
								cin>>kiemtra;
							}
							mh[j].SoLuong[i] = stoi(kiemtra);
						}
					}
				}
				break;
			case 2:
				if(Tong_ngay == 0 && Tong_sp == 0){
					cout<<"Khong co du lieu"<<endl;
					system("pause");
				}
				else{
					for(int i = 0; i < Tong_ngay; i++){
						XuatBang(mh,i,Tong_sp);
					}
					system("pause");
				}
				break;
			case 3:{
				if(Tong_ngay == 0 && Tong_sp == 0){
					cout<<"Khong co du lieu"<<endl;
					system("pause");
				}
				else{
					system("cls");
					int choice;
					cout<<"1.Tim kiem ma mat hang "<<endl;
					cout<<"2.Tim kiem theo ngay "<<endl;
					cout<<"Nhap so ung voi thao tac tim kiem: ";
					cin>>choice;
					cin.ignore();
					if(choice == 1){
						system("cls");
						char tiep = 'Y';
						while(toupper(tiep) == 'Y'){
							string mmh;
							cout<<"Nhap ma mat hang can tim: ";
							cin>>mmh;
							Tk_Ma_Mat_Hang(mh, Tong_sp, Tong_ngay, mmh);
							cin.ignore();
							cout<<"Ban co muon tiep tuc khong (Y/N): ";
							cin>>tiep;
						}
					}
					if(choice == 2){
						system("cls");
						char tiep = 'Y';
						while(toupper(tiep) == 'Y'){
							int find;
							cout<<"Moi nhap ngay can tim: ";
							cin>>find;
							if (find > Tong_ngay){
								cout<<"Khong co du lieu ngay: "<<find<<endl;
							}
							else{XuatBang(mh,find-1,Tong_sp);}
							cin.ignore();
							cout<<"Ban co muon tiep tuc khong (Y/N): ";
							cin>>tiep;
						}
					}
				}
				break;
			}
			case 4:
				if(Tong_ngay == 0 && Tong_sp == 0){
					cout<<"Khong co du lieu"<<endl;
					system("pause");
				}else quanlythongke(Tong_ngay,Tong_sp,mh);
				break;
			case 5:
				if(Tong_ngay == 0 && Tong_sp == 0 ){
					cout<<"Khong co du lieu"<<endl;
					system("pause");
				}
				else{
					LuuFile(mh,Tong_ngay,Tong_sp);
					checkluu = false;
				}
				break;
			case 6:
				checkluu = false;
				reset();
				daycu = 0;
				spcu = 0;
				So_Ngay = 0;
				So_Hang = 0;
				break;
			case 7:{
				char chon;
				if (checkluu){
					cout<<"Ban chua luu du lieu. Ban co muon luu khong(Y/N): ";
					cin>>chon;
					if(toupper((chon)) == 'Y'){
						LuuFile(mh,Tong_ngay,Tong_sp);
					}
				}
				return 0;
			}
		}	
	}
}
