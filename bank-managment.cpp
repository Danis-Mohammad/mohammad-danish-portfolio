#include<iostream>
#include<windows.h>
#include<fstream>
#include<string>
#include<conio.h>
#include<stdio.h>

using namespace std;

class bank
{
    private:
    long long phone;
    float balance;
    string id,name,addres,pass,fname;

    public:
    void atm_transfer(){
        fstream file,file1;
        string s_id,r_id,t_pass;
        char ch;
        int found=0;
        float amount;
        system("cls");
        cout<<"\n\n\t\tTransfer Money";
        file.open("bank.txt",ios::in);
        if(!file){
            cout<<"\n\n\tFile Opening Error !";
        }else{
            cout<<"\n\tEnter Sender Id : ";
            cin>>s_id;
            cout<<"\n\tEnter Password : ";
            for(int i=0;i<5;i++){
                ch = getch();
                t_pass += ch;
                cout<<"*";
            }
            cout<<"\n\tEnter Reciver Id : ";
            cin>>r_id;
            cout<<"\n\tEnter Tranfer Amount : ";
            cin>>amount;
            file>>id>>name>>fname>>addres>>pass>>phone>>balance;
            while (!file.eof())
            {
                if(s_id==id and balance>=amount and t_pass == pass){
                    found++;
                }else if(r_id==id){
                    found++;
                }else if(found==1 and r_id==id){
                    cout<<"\n\tYour Current Balance is Low !";
                }
                file>>id>>name>>fname>>addres>>pass>>phone>>balance;
            }
            file.close();
            if(found==2){
                file.open("bank.txt",ios::in);
                file1.open("bank1.txt",ios::app|ios::out);
                file>>id>>name>>fname>>addres>>pass>>phone>>balance;
                while(!file.eof()){
                    if(s_id==id){
                        balance -= amount;
                        file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
                    }else if(r_id == id){
                        balance += amount;
                        cout<<"\n\tAmount Transfer Succesful !";
                        file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
                    }else{
                        file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
                    }
                    file>>id>>name>>fname>>addres>>pass>>phone>>balance;
                }
                file.close();
                file1.close();
                remove("bank.txt");
                rename("bank1.txt","bank.txt");
            }else{
                cout<<"\n\n\t\tERROR 404....ID Does'Not Exist ";
            }
        }
        Sleep(3000);
        bank_management();
    }

    void detail(){
        fstream file;
        int found=0;
        string t_id,t_pass;
        char ch;
        system("cls");
        cout<<"\n\n\t\tCheck Detail ";
        file.open("bank.txt",ios::in);
        if(!file){
            cout<<"\n\tFile NOT found !";
        }else{
            cout<<"\n\tEnter User Id : ";
            cin>>t_id;
            cout<<"\nEnter Password : ";
            for(int i=0;i<5;i++){
                ch = getch();
                t_pass += ch;
                cout<<"*";
            }
        }
        file>>id>>name>>fname>>addres>>pass>>phone>>balance;
        while(!file.eof()){
            if(t_id == id  and t_pass == pass){
                cout<<"\n\n\tId : "<<id;
                cout<<"\n\tName : "<<name;
                cout<<"\n\tFather Name : "<<fname;
                cout<<"\n\tAddress : "<<addres;
                cout<<"\n\tPhone No : "<<phone;
                cout<<"\n\tBalance : "<<balance;
                found++;
                }
                file>>id>>name>>fname>>addres>>pass>>phone>>balance;
        }
        file.close();
        if(found == 0){
            cout<<"\n\tId Not Found !";
        }
        Sleep(3000);
        atm_management();
    }

    void withdraw_atm(){
        system("cls");
        cout<<"\n\n\t\tUser Login";
        fstream file,file1;
        int found=0;
        string t_id,t_pass;
        char ch;
        float wid; 
        file.open("bank.txt",ios::in);
        if(!file){
            cout<<"\n\tFile NOT found";
        }else{
            cout<<"\n\tEnter User Id : ";
            cin>>t_id;
            cout<<"\n\tEnter Password : ";
            for(int i=0;i<5;i++){
                ch = getch();
                t_pass += ch;
                cout<<"*";
            }
        }
        file>>id>>name>>fname>>addres>>pass>>phone>>balance;
        while(!file.eof()){
            if(t_id == id  and t_pass == pass){
                cout<<"\n\tEnter Amount to Withdraw : ";
                cin>>wid;
                if(wid<=balance){
                    balance -=wid;
                    file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
                    cout<<"\n\tAmount Succesfully Withdraw ";
                    cout<<"\n\tCurrent Balance : "<<balance;
                    found++;
                }else{
                    file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
                    cout<<"\n\tYour current Banlance is Less Than Withdraw Amount !";
                    cout<<"\n\tCurrent Balance :"<<balance;
                    found++;
                }
                }else{
                    file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
                }
                file>>id>>name>>fname>>addres>>pass>>phone>>balance;
        }
        file.close();
        if(found == 0){
            cout<<"\n\tId Not Found !";
        }
        Sleep(3000);
        atm_management();
    }

    void user_balance(){
        system("cls");
        cout<<"\n\n\t\tUser Login";
        fstream file;
        int found=0;
        string t_id,t_pass;
        char ch;
        file.open("bank.txt",ios::in);
        if(!file){
            cout<<"\n\tFile NOT found";
        }else{
            cout<<"\n\tEnter User Id : ";
            cin>>t_id;
            cout<<"\n\tEnter Password : ";
            for(int i=0;i<5;i++){
                ch = getch();
                t_pass += ch;
                cout<<"*";
            }
            file>>id>>name>>fname>>addres>>pass>>phone>>balance;
            while(!file.eof()){
                if(t_id==id and t_pass==pass){
                    cout<<"\n\tYour Current BALANCE : "<<balance;
                    found++;
                }
                file>>id>>name>>fname>>addres>>pass>>phone>>balance;
            }
            file.close();
            if(found == 0){
                cout<<"\n\n\tId or Password Invalid !";
            }
        }
        Sleep(3000);
        atm_management();
    }

    void show_record(){
        system("cls");
        fstream file;
        int found =0;
        string t_id;
        cout<<"\n\n\t\tShow All User Record";
        file.open("bank.txt",ios::in);
        if(!file){
            cout<<"\n\n\tFile NOT found !";
        }else{
            file>>id>>name>>fname>>addres>>pass>>phone>>balance;
            while(!file.eof()){
                cout<<"\n\n\tId : "<<id;
                cout<<"\n\tName : "<<name;
                cout<<"\n\tFather Name : "<<fname;
                cout<<"\n\tAddress : "<<addres;
                cout<<"\n\tPhone No : "<<phone;
                cout<<"\n\tBalance : "<<balance;
                cout<<"\n==========================================================";
                file>>id>>name>>fname>>addres>>pass>>phone>>balance;
                found++;
            }
            file.close();
            if(found==0){
                cout<<"\n\n Data Not Found !";
            }
        }
        Sleep(3000);
        bank_management();
    }

    void delet(){
        system("cls");
        fstream file,file1;
        string t_id;
        int found=0;
        cout<<"\n\n\t\tDelet User Record ";
        file.open("bank.txt",ios::in);
        if(!file){
            cout<<"\n\tFile NOT Found !";
        }else{
            cout<<"\n\tEnter User Id : ";
            cin>>t_id;
            file1.open("bank1.txt",ios::app|ios::out);
            file>>id>>name>>fname>>addres>>pass>>phone>>balance;
            while(!file.eof()){
                if(t_id==id){
                    cout<<"\n\n\tRecord Delet Succesfully";
                    found++;
                }else{
                    file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
                }
                file>>id>>name>>fname>>addres>>pass>>phone>>balance;
            }
            file.close();
            file1.close();
            remove("bank.txt");
            rename("bank1.txt","bank.txt");
        }
        Sleep(3000);
        bank_management();
    }

    void search(){
        system("cls");
        int found =0;
        fstream file;
        string t_id;
        cout<<"\n\n\t\tSearch Record";
        file.open("bank.txt",ios::in);
        if(!file){
            cout<<"\n\tFile not Exist";
        }else{
            cout<<"\n\tEnter User Id : ";
            cin>>t_id;
            file>>id>>name>>fname>>addres>>pass>>phone>>balance;
            while(!file.eof()){
                if(t_id==id){
                    system("cls");
                    cout<<"\n\n\t\tSearch Record";
                    cout<<"\n\nUser Id : "<<id<<"  "<<"\tName : "<<name<<"\nFather Name : "<<fname<<"\tAddres : "<<addres<<"\nPhone No : "<<phone<<"\tBalance : "<<balance;
                    found++;
                }
            file>>id>>name>>fname>>addres>>pass>>phone>>balance;
            } 
            file.close();
            if(found == 0){
                cout<<"\n\tRecord Not Found !";
            }
        }
        Sleep(5000);
        bank_management();
    }

    void transfer(){
       fstream file,file1;
       string s_id,r_id;
       int found=0;
       float amount;
       system("cls");
       cout<<"\n\n\t\tTransfer Money";
       file.open("bank.txt",ios::in);
        if(!file){
            cout<<"\n\n\tFile Opening Error !";
        }else{
            cout<<"\n\tEnter Sender Id : ";
            cin>>s_id;
            cout<<"\n\tEnter Reciver Id : ";
            cin>>r_id;
            cout<<"\n\tEnter Tranfer Amount : ";
            cin>>amount;
            file>>id>>name>>fname>>addres>>pass>>phone>>balance;
            while (!file.eof())
            {
                if(s_id==id and balance>=amount){
                    found++;
                }else if(r_id==id){
                    found++;
                }else if(found==1 and r_id==id){
                    cout<<"\n\tYour Current Balance is Low !";
                }
                file>>id>>name>>fname>>addres>>pass>>phone>>balance;
            }
            file.close();
            if(found==2){
                file.open("bank.txt",ios::in);
                file1.open("bank1.txt",ios::app|ios::out);
                file>>id>>name>>fname>>addres>>pass>>phone>>balance;
                while(!file.eof()){
                    if(s_id==id){
                        balance -= amount;
                        file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
                    }else if(r_id == id){
                        balance += amount;
                        cout<<"\n\n\t\tTranfer succesful";
                        file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
                    }else{
                        file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
                    }
                    file>>id>>name>>fname>>addres>>pass>>phone>>balance;
                }
                file.close();
                file1.close();
                remove("bank.txt");
                rename("bank1.txt","bank.txt");
            }else{
                cout<<"\n\n\t\tERROR 404....ID Does'Not Exist ";
            }
        }
        Sleep(3000);
        bank_management();
    }

    void deposit(){
        fstream file,file1;
        string t_id;
        float dep;
        int found=0;
        system("cls");
        cout<<"\n\n\t\tDeposit Amount Option";
        file.open("bank.txt",ios::in);
        if(!file){
            cout<<"\n\n\tFile Opening Error !";
        }else{
            cout<<"\n\n\tEnter User Id : ";
            cin>>t_id;
            file1.open("bank1.txt",ios::app|ios::out);
            file>>id>>name>>fname>>addres>>pass>>phone>>balance;
        }while(!file.eof()){
            if(t_id == id){
                cout<<"\n\tEnter Amount to Deposit : ";
                cin>>dep;
                balance += dep;
                file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
                found ++;
                cout<<"\n\n\tAmount Succesfully Deposit ";
            }else{
                file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
            }
            file>>id>>name>>fname>>addres>>pass>>phone>>balance;
        }
        file.close();
        file1.close();
        remove("bank.txt");
        rename("bank1.txt","bank.txt");
        if(found == 0){
            cout<<"\n\tId Not Found !";
        }
        Sleep(3000);
        bank_management();
    }

    void withdraw(){
        fstream file,file1;
        string t_id;
        float wid;
        int found=0;
        system("cls");
        cout<<"\n\n\t\tWithdraw Amount Option";
        file.open("bank.txt",ios::in);
        if(!file){
            cout<<"\n\tFile Opening Error !";
        }else{
            cout<<"\n\tEnter User Id : ";
            cin>>t_id;
            file1.open("bank1.txt",ios::app|ios::out);
            file>>id>>name>>fname>>addres>>pass>>phone>>balance;
        }while(!file.eof()){
            if(t_id == id){
                cout<<"\n\tEnter Amount to Withdraw : ";
                cin>>wid;
                if(wid<=balance){
                    balance -=wid;
                    file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
                    found ++;
                    cout<<"\n\n\tAmount Succesfully Withdraw ";
                }else{
                    file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
                    cout<<"\n\n\tYour current Banlance is Less Than Withdraw Amount !";
                    cout<<"\n\tCurrent Balance :"<<balance;
                    found ++;
                }
                
            }else{
                file1<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
            }
            file>>id>>name>>fname>>addres>>pass>>phone>>balance;
        }
        file.close();
        file1.close();
        remove("bank.txt");
        rename("bank1.txt","bank.txt");
        if(found == 0){
            cout<<"\n\tId Not Found !";
        }
        Sleep(3000);
        bank_management();
    }

    void already_user(){
        system("cls");
        string t_id;
        int found = 0;
        fstream file;
        cout<<"\n\n\t\tAlraedy User Acount ";
        file.open("bank.txt",ios::in);
        if(!file){
            cout<<"\n\n\tFile Opening Error !";
        }else{
            cout<<"\n\n\tEnter User Id : ";
            cin>>t_id;
            file>>id>>name>>fname>>addres>>pass>>phone>>balance;
        }while(!file.eof()){
            if(t_id == id){
                system("cls");
                cout<<"\n\n\t\tUser Id : "<<id<<"\n\n\t\tPassword : "<<pass<<"\n\n\t\tName : "<<name<<"\n\n\t\tAddress : "<<addres;
                found ++;
            }
            file>>id>>name>>fname>>addres>>pass>>phone>>balance;
        }
        file.close();
        if(found == 0){
            cout<<"\n\tId Not Found !";
        }
        Sleep(3000);
        bank_management();
    }

    void menu(){
        p:
        system("cls");
        int choise;
        char ch;
        string pin,pass,email;
        cout<<"\n\n\t\t\tCONTROL PANEL";
        cout<<"\n\n\t1.Bank Management";
        cout<<"\n\t2.ATM Management";
        cout<<"\n\t3.exit";
        cout<<"\n\tEnter your choice : ";
     a: cin>>choise;
        try
        {
            if(choise > 3 or choise < 1){
            throw invalid_argument("\n\n\tenter a number between 1-3 : ");
            }
        }
        catch(invalid_argument e)
        {
            cout<<e.what();
            goto a;
        }

        switch (choise){
            case 1: 
            system("cls");
            cout<<"\n\n\t\tLogin Acount";
            cout<<"\n\tEnter E-mail : ";
            cin>>email;
            cout<<"\n\tEnter Password : ";
            for(int i=0;i<5;i++){
                ch =getch();
                pass +=ch;
                cout<<"*";
            }
            if(email=="danish@gmail.com" and pass=="54321"){
                bank_management();
            }else{
                cout<<"\n\n\tWorng pin or email ";
                Sleep(3000);
                menu();
            }
            
            break;
            case 2:
            atm_management();
            break;
            case 3:
            exit(0);
            break;
            getch();
            goto p;
        }
        
    }

    void bank_management(){
        system("cls");
        int choise;
        cout<<"\n\n\t\t\tBank Management System";
        cout<<"\n\n\t1. ->New User";
        cout<<"\n\t2. ->Already User";
        cout<<"\n\t3. ->Deposit Option";
        cout<<"\n\t4. ->Withdraw Option";
        cout<<"\n\t5. ->Tranfer Option";  
        cout<<"\n\t6. ->Search User Record";      
        cout<<"\n\t7. ->Delet User Record";  
        cout<<"\n\t8. ->Show User Record";    
        cout<<"\n\t9. ->Go back";  
        cout<<"\n\n\tEnter Your Choise : ";
     b: cin>>choise;
        try
        {
            if(choise > 9 and choise < 1){
            throw invalid_argument("\n\n\tenter a number between 1-9 : ");
            }
        }
        catch(invalid_argument e)
        {
            cout<<e.what();
            goto b;
        }
        switch (choise){
            case 1:
            new_user();
            break;
            case 2:
            already_user();
            break;
            case 3:
            deposit();
            break;
            case 4:
            withdraw();
            break;
            case 5:
            transfer();
            break;
            case 6:
            search();
            break;
            case 7:
            delet();
            break;
            case 8:
            show_record();
            break;
            case 9:
            menu();
            break;
        }
    }

    void atm_management(){
        system("cls");
        int choise;
        cout<<"\n\n\t\t\tATM Managment System";
        cout<<"\n\t1. ->User Login ANd Check Balance";
        cout<<"\n\t2. ->Withdraw Amount";
        cout<<"\n\t3. ->Transfer Amount";
        cout<<"\n\t4. ->User Detail";
        cout<<"\n\t5. ->Go Back";  
        cout<<"\n\n\tEnter Your Choise : ";
     c: cin>>choise;
        try
        {
            if(choise > 5 and choise < 1){
            throw invalid_argument("\n\nenter a number between 1-4 : ");
            }
        }
        catch(invalid_argument e)
        {
            cout<<e.what();
            goto c;
        }
        switch (choise){
            case 1:
            user_balance();
            break;
            case 2:
            withdraw_atm();
            break;
            case 3:
            atm_transfer();
            break;
            case 4:
            detail();
            break;
            case 5:
            menu();
            break;
        }
          
    }

    void new_user(){
    d:  system("cls");
        fstream file;
        int ph;
        string n,ad,i,ps,fn;
        double b;
        cout<<"\n\n\t\tAdd New User";
        cout<<"\n\tUser Id : ";
        cin>>id;
        cout<<"\n\tEnter Name : ";
        cin>>name;
        cout<<"\n\tEnter Father Name : ";
        cin>>fname;
        cout<<"\n\tEnter Addres : ";
        cin>>addres;
        cout<<"\n\tEnter pass(5 Digit) : ";
        cin>>pass;
        cout<<"\n\tEnter mobile No : ";
        cin>>phone;
        cout<<"\n\tEnter Balance : ";
        cin>>balance;
        file.open("bank.txt",ios::in);
        if(!file){
            file.open("bank.txt",ios::app|ios::out);
            file<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
            file.close();
        }else{
            file>>i>>n>>fn>>ad>>ps>>ph>>b;
            while(!file.eof()){
                if(i == id){
                    cout<<"\n\tThis Id Alreay Exist";
                    getch();
                    goto d;
                }
            file>>i>>n>>fn>>ad>>ps>>ph>>b;
            }
            file.close();
            file.open("bank.txt",ios::app|ios::out);
            file<<" "<<id<<" "<<name<<" "<<fname<<" "<<addres<<" "<<pass<<" "<<phone<<" "<<balance<<"\n";
            file.close();
        }
        cout<<"\n\n\t\tAdd New User Succesful.";
        Sleep(3000);
        bank_management();
    }
};

void introduction(){
    system("cls");
    cout<<"\t\t***********************************************************************************************************************";
    cout<<"\n\t\t *********************************************************************************************************************";
    cout<<"\n\t\t  *******************************************************************************************************************";
    cout<<"\n\t\t  *\t\t\t\t\t\t\t\t\t\t\t\t\t\t    *";
    cout<<"\n\t\t  *\t\t\t\t\t\t\t\t\t\t\t\t\t\t    *";
    cout<<"\n\t\t  *\t\t\t\t\t\tMY BANK MANAGMENT SYSTEM :)\t\t\t\t\t    *";
    cout<<"\n\t\t  *\t\t\t\t\t\t\t\t\t\t\t\t\t\t    *";
    cout<<"\n\t\t  *\t\t\t\t\t\t\t\t\t\t\t\t\t\t    *";
    cout<<"\n\t\t  *\t\t\t\t\t\tBy--> Mohammad Danish Shaik\t\t\t\t\t    *";
    cout<<"\n\t\t  *\t\t\t\t\t\t\t\t\t\t\t\t\t\t    *";
    cout<<"\n\t\t  *\t\t\t\t\t\t\t\t\t\t\t\t\t\t    *";
    cout<<"\n\t\t  *******************************************************************************************************************";
    cout<<"\n\t\t *********************************************************************************************************************\n";
    cout<<"\t\t***********************************************************************************************************************\n";    
    Sleep(3000);
}

int main(){
    bank obj;
    introduction();
    obj.menu();
}