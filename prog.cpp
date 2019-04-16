#include<fstream>
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
using namespace std;
struct day{
    int date,month,year;
    };
struct passenger{
    int PNR,SER,AGE,BER;
    day D;
    char NAME[31],COH[2];
    };
void Takedata(passenger &PT)
{
    cout<<"\n Enter the name of passenger : ";
    cin>>PT.NAME;
    cout<<"\n Enter the age of the Passenger : ";
    cin>>PT.AGE;
    cout<<"\n Enter the date of travel : ";
    cout<<"\n Enter Date : ";
    cin>>PT.D.date;
    cout<<"\n Enter Month : ";
    cin>>PT.D.month;
    cout<<"\n Enter Year : ";
    cin>>PT.D.year;

}
void Print(passenger P)
{
    int s=strlen(P.NAME);
    ofstream fout;
    fout.open("Ticket/Ticket.txt",ios::out);
    fout<<" ";
    for(int i=0;i<65;i++)
    fout<<"_";
    fout<<"\n| \t \t \t--INDIAN RAILWAYS-- \t \t \t ";
    fout<<" |\n|";
    for(int i=0;i<65;i++)
        fout<<"-";
    fout<<"|\n|PNR - "<<P.PNR<<" ";
    fout<<" Date - "<<P.D.date<<"/"<<P.D.month<<"/"<<P.D.year;
    fout<<" Distance - 634 ";
    fout<<" Serial No - "<<P.SER<<"|\n|";
    fout<<"Name - "<<P.NAME;
    for(int i=0;i<58-s;i++)
        fout<<" ";
    fout<<"|\n|Age - "<<P.AGE;
    for(int i=0;i<57;i++)
        fout<<" ";
    fout<<"|\n|Train No - 12418";
    for(int i=0;i<49;i++)
        fout<<" ";
    fout<<"|\n|Reserved From- Allahabad\t\t";
    fout<<"Departure-"<<P.D.date<<"/"<<P.D.month<<"/"<<P.D.year<<" 21:30";

    fout<<"|\n|Reserved To - Delhi\t\t\t";
    fout<<"Arrival - "<<P.D.date+1<<"/"<<P.D.month<<"/"<<P.D.year<<" 08:05 ";
    fout<<"|\n|";
    for(int i=0;i<65;i++)
        fout<<" ";
    fout<<"|\n|Class - SLR";
    for(int i=0;i<54;i++)
        fout<<" ";
    fout<<"|\n|Coach - "<<P.COH<<"\t Berth - "<<P.BER;
    fout<<"\t\t\t \t \t ";
    fout<<" |\n|";
    for(int i=0;i<65;i++)
        fout<<"_";
    fout<<"|";
    fout.close();
}
int readfile()
{   int K=0;
    passenger PR;
    ifstream fin;
    fin.open("source/data.txt",ios::in);
    while(!fin.eof())
    {
        fin.read((char*)&PR,sizeof(PR));
        if(PR.BER!=10+K)
            break;
        K=K+1;
    }
    fin.close();
    cout<<"\n \t Available Berth no is = "<<K+10;
    return K;
}
void write(passenger P)
{
    passenger P1;
    ifstream fin;
    fin.open("source/data.txt",ios::in);
    ofstream fout;
    fout.open("source/temp.txt",ios::out);
    int C=1;
    while(!fin.eof())
    {
        fin.read((char*)&P1,sizeof(P1));
        if(P1.BER>P.BER&&C==1)
            {fout.write((char*)&P,sizeof(P)); C=0; }
        if(fin.eof()) break;
        fout.write((char*)&P1,sizeof(P1));
    }
if(C) fout.write((char*)&P,sizeof(P));
    fout.close();
    fin.close();
    remove("source/data.txt");
    rename("source/temp.txt","source/data.txt");
}
void booking()
{
    passenger P;
    int K=readfile();
    Takedata(P);
    P.PNR=15000+K;
    P.SER=10000+K;
    P.BER=10+K;
    strcpy(P.COH,"S1");
    write(P);
    Print(P);
    cout<<"\n \t Booked";

}
void canceling(int PNR,int AGE)
{
    int S=0;
    passenger P1;
    ifstream fin;
    ofstream fout;
    fin.open("source/data.txt",ios::in);
    fout.open("source/temp.txt",ios::out);
    while(!fin.eof())
    {
        fin.read((char*)&P1,sizeof(P1));if(fin.eof()) break;
            if(P1.PNR==PNR&&P1.AGE==AGE)
            {S=1; continue; }
        fout.write((char*)&P1,sizeof(P1));
    }
    if(!S) cout<<"\n WRONG PNR or AGE";
    fin.close();
    fout.close();
    remove("source/data.txt");
    rename("source/temp.txt","source/data.txt");
    cout<<"\n \t Canceled";
}
int main()
{
    int TAKE,PNR,AGE;
    cout<<"\n\t\t \t"<<"  WELCOME TO INDIAN RAILWAYS  "<<"\t \t\t";
    cout<<"\n\n\n";
    cout<<"\t Press 1 to Book Ticket \n\t Press 2 to Cancel Ticket \n\t Press 3 to Check Status \n\t Press 4 for ADMIN LOGIN";
    cout<<"\n\n\t\t USER RESPONSE : ";
    cin>>TAKE;
    if(TAKE==1) booking();
    else if(TAKE==2)
    {
        cout<<"\n Enter PNR no : ";
        cin>>PNR;
        if(PNR==15000){cout<<"\n\t Acess Denied\n"; system("pause"); exit(0);}
        cout<<"\n Enter Age : ";
        cin>>AGE;
        canceling(PNR,AGE);
    }
    else if(TAKE==3)
    { passenger P1;
        cout<<"\n Enter PNR : ";
        cin>>PNR;
        ifstream fin;
        fin.open("source/data.txt",ios::in);
        while(!fin.eof())
        {
            fin.read((char*)&P1,sizeof(P1));
            if(fin.eof()) break;
            if(P1.PNR==PNR) cout<<"\t Your Current Seat Number is : "<<P1.BER;
        }
        fin.close();
    }
    else if(TAKE==4)
    {   int PASSWORD;
        system("cls");
        cout<<"\n\t\t \t"<<"  WELCOME TO INDIAN RAILWAYS  "<<"\t \t\t";
        cout<<"\n\n\n";
        cout<<"\n\t Enter 5 digit Password : ";
        cin>>PASSWORD;
        if(PASSWORD!=12345)
        {
            cout<<"\t Invalid password\n";
            system("pause");
            exit(0);
        }
        system("cls");
        cout<<"\n\t\t \t"<<"  WELCOME TO INDIAN RAILWAYS  "<<"\t \t\t";
        cout<<"\n\n\n";
        passenger P1;
        cout<<"\n\t \t\t Details of PASSENGERS\n";
        ifstream fin;
        fin.open("source/data.txt",ios::in);
        while(!fin.eof())
        {
        fin.read((char*)&P1,sizeof(P1));if(fin.eof()) break;
        cout<<"\n"<<P1.SER<<"\t"<<P1.NAME<<"\t"<<P1.AGE<<"\t"<<P1.BER<<"\t"<<P1.PNR<<"\t"<<P1.D.date<<" "<<P1.D.month<<" "<<P1.D.year<<" \t12418";
        }
    fin.close();
    }
    else{cout<<"\n\t WRONG INPUT \n";}
    cout<<"\n";
    system("pause");
    return 0;
}
