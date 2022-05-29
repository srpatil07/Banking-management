#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int login_account();               //function for login account
int create();                      //function for open new account
void manager_view();               //function for manager view
int dateofbirth(int,int,int);      //date of birth verification
int adhar(long long int);          //aadhar number verification
int pancard(char []);              //PAN number verification
int pincode(int);                  //pincode verification
int mobile(long long int);         //mobile number verification
int password(int,int);             //password verification
long int gen_ac_no(int);           //account number generation
int Deposit_Amount();              //function declaration for amount deposit
int Withdraw_Amount();             //function declaration for amount withdraw
int Balance_Enquiry();             //function declaration for balance enquiry
int Change_password();             //function declaration for changing password
int my_passbok();                  //function declaration for passbook print;
int delete_account();              //function deletion account deletion

//structure declaration for opening new account;
typedef struct creat
{
   char fname[20];             //for first name
   char lname[20];             //for last name
   char pname[20];             // for parents details
   struct dob
   {
       int date;
       int month;
       int year;
   }dob;                      //date of birth format
   long long int adhar;       // for adhar number
   char pan[10];              //for pancard number
   struct address             // address details
   {
       int hno;
       char area[20];
       char taluk[20];
       char dist[20];
       char state[20];
       char country[20];
       int pincode;
   }address;
   long long int mobile;      //for mobile number
   char email[30];            //for email address
   int password;          // for password creation
   long int account_no;
   char account_type[2];
   int checkbook;
   float deposit;
}creat;
creat new_account,temp,real,temp_pan,temp_adhar,temp_mobile,temp_ac,change,change1,my_p,delete_ac;

//user login to their account structure
typedef struct login
{
    long long int mobile_no;
    int password;
}login;
login user;

//structure for storing updates of SB account holders trasaction
typedef struct sb
{
    long int account_no;
    float amount;
}sb;
sb current,temp1,temp2,my_balance;

void main()
{
    int i;
    printf("********************** WELCOME TO PATIL'S BANK **********************\n");
    for(i=1;i<70;i++) printf("\xcd");
    printf("\n");
    printf("                            MAIN MENU \n");
    printf("[1] Login your account \n");
    printf("[2] Create new account\n");
    printf("[3] Manager view\n");
    printf("[4] Exit\n\n");
    for(i=1;i<70;i++) printf("\xcd");
    printf("\n");

    int choice,value,choice1;

        printf("Enter your choice : ");
        scanf("%d",&choice);
        switch(choice)
        {
             case 1:value = login_account();    //login your account if you have
             break;
             case 2:create();                   //create new account for new users
             break;
             case 3:manager_view();               //this is only for manager
             break;
             case 4:exit(0);
             default:
                 {
                     printf("Invalid option...\n\n\n");
                     printf("*********************   Thanks    ***************************\n\n\n");
                     return 0;
                 }
        }
        for(i=1;i<70;i++) printf("\xcd");
        printf("\n");
        //once you have login your account, then you have below servises
        if(value == 1)
        {
             printf("                               MENU \n");
             printf("[1] Deposit Amount\n");
             printf("[2] Withdraw Amount\n");
             printf("[3] Balance Enquiry\n");
             printf("[4] Change password\n");
             printf("[5] Passbook\n");
             printf("[6] Delete account\n");
             printf("[7] Exit\n\n");
             for(i=1;i<70;i++) printf("\xcd");
             printf("\n");
             while(1)
             {
                  printf("Enter your choice : ");
                  scanf("%d",&choice1);
                  switch(choice1)
                  {
                      case 1: Deposit_Amount();         //this function for deposit amount into your accont
                              break;
                      case 2: Withdraw_Amount();        //this is for withdraw amount from your account
                              break;
                      case 3: Balance_Enquiry();        // this is for balance enquiry
                              break;
                      case 4: Change_password();        //change your login password
                              break;
                      case 5: my_passbook();            //your passbook front page
                              break;
                      case 6: delete_account();         //delete your account permanently
                              break;
                      case 7: exit(0);
                      default: printf("Invalid choice .......!\n");
                  }
                  for(i=1;i<70;i++) printf("\xcd");
                  printf("\n");
             }
        }
}

int login_account()   //user login function
{
    int value=0,n=0,i=0;
    //user verification by mobile number and password
    printf("\nEnter your mobile number : ");
    scanf("%lld",&user.mobile_no);
    printf("Enter your password : ");
    scanf(" %d",&user.password);

    FILE *fp;
    fp=fopen("E:/file_handling/my_bank.txt","r");  //open file in reading mode
    while(fread(&temp,sizeof(struct creat),1,fp))
    {
        if(temp.mobile == user.mobile_no && temp.password == user.password) break;
        else value++;
    }
    fclose(fp);
    if(value!=0)
        {
            printf("\nInvalid username or passward");
            return 0;
        }
    else return 1;
}

int create()            //create  new account
{
    FILE *fp,*fpp;           //file creation for mentain record of account holder
    char pan[10];
    int pass,repass;
    int d,m,y,a=0,b=0,c=0,i,e=0,pin,f=0,g=0,choice,temp=0;
    long long int x,z;
    long int ac_no;
    printf("......Enter below details......\n");
    fp=fopen("E:/file_handling/my_bank.txt","a+");  // open file in writting mode
    // start taking information from customer
    printf("First name : ");
    scanf(" %s",new_account.fname);
    printf("Last name : ");
    scanf(" %s",new_account.lname);
    printf("Parents name : ");
    scanf(" %s",new_account.pname);

    while(a != 1)                                 // date of birth verification
    {
    printf("Date of Birth(dd mm yyyy) : ");
    scanf("%d %d %d",&d,&m,&y);
    a=dateofbirth(d,m,y);
    if(a==1)
    {
       new_account.dob.date=d;
       new_account.dob.month=m;
       new_account.dob.year=y;
    }
    else printf("Invalid date of birth...!");
    }

    while(b != 1)                              // adhar number length verifiaction
    {
       printf("Adhar number : ");
       scanf("%lld",&x);
       b=adhar(x);
       if(b==1) new_account.adhar=x;
       else if(b==2) printf("Adhar already exist...!\n");
       else printf("Invalid ADHAR NUMBER....!\n");
    }

    while(c != 1)                            //PAN number length and format verification
    {
        printf("PAN number : ");
        scanf(" %s",pan);
        c=pancard(pan);
        if(c==1)
        {
            for(i=0;pan[i] != '\0';i++)
            new_account.pan[i]=pan[i];
        }
        else if(c==2) printf("PAN numder is already exist....!\n");
        else printf("Invalid PAN NUMBER....\n");
    }
    //getting residential address of new user
    printf("House number : ");
    scanf("%d",&new_account.address.hno);
    printf("Area name : ");
    scanf(" %s",new_account.address.area);
    printf("Taluk : ");
    scanf(" %s",new_account.address.taluk);
    printf("District : ");
    scanf(" %s",new_account.address.dist);
    printf("State : ");
    scanf(" %s",new_account.address.state);
    printf("Country : ");
    scanf(" %s",new_account.address.country);

    while(e!=1)                                //pincode length verification
    {
       printf("Pincode : ");
       scanf(" %d",&pin);
       e= pincode(pin);
       if(e==1) new_account.address.pincode=pin;
       else printf("Invalid pin code.....!");
    }

   while(f!= 1)                               // mobile number length verification
    {
        printf("Mobile number : ");
        scanf("%lld",&z);
        f=mobile(z);
        if(f==1) new_account.mobile=z;
        else if(f==2) printf("Mobile number is already exist....!\n");
        else printf("Invalid mobile number...!\n");
    }

    printf("Email ID : ");                   //getting email ID
    scanf(" %s",new_account.email);

    while(g!=1)                             //password verification
    {
        printf("Password (4 digit) : ");
        scanf(" %d",&pass);
        printf("Re enter Password : ");
        scanf("%d",&repass);
        g=password( pass,repass);
        if(g==1)new_account.password=pass;
        else if(g==2) printf("password Length must be 4 digits....!\n");
    }

    ac_no=gen_ac_no(pin);                   //*** generation of account number based on their area pincode
    new_account.account_no=ac_no;
    printf("[1] SB\n[2] FD\n[3] RD\n");     // which type of account servises available in bank
        char sb[]={'S','B'},rd[]={'R','D'},fd[]={'F','D'};
        printf("Enter your choice ");
        scanf("%d",&choice);
        switch(choice)
        {
             case 1:                       //saving account procedure
                 {
                     new_account.account_type[0]=sb[0];
                     new_account.account_type[1]=sb[1];
                     {
                         printf("[1] without checkbook \n[2] with checkbook\n");
                         while(temp == 0)
                         {
                             printf("Enter your choice : ");
                             scanf("%d",&choice);
                             switch(choice)
                             {
                             case 1:                //without check book facilities
                                {
                                    new_account.checkbook=0;
                                    temp++;
                                    float depo;
                                    while(temp==1)
                                    {
                                        printf("**** Minimum initial deposit is 1000/- ****\n");
                                        printf("Enter your deposit amount : ");
                                        scanf("%f",&depo);
                                        if(depo >= 1000)
                                        {
                                            new_account.deposit=depo;
                                            temp++;
                                        }
                                        else printf(" deposit minimum amount\n");
                                    }
                                    break;
                                }
                             case 2:               //with check book facilities
                                 {
                                    new_account.checkbook=1;
                                    temp++;
                                    float depo;
                                    while(temp==1)
                                    {
                                        printf("**** Minimum initial deposit is 3000/- ****\n");
                                        printf("Enter your deposit amount : ");
                                        scanf("%f",&depo);
                                        if(depo >= 3000)
                                        {
                                            new_account.deposit=depo;
                                            temp++;
                                        }
                                        else printf(" deposit minimum amount\n");
                                    }
                                    break;
                                }
                             default :printf("Enter invalid choice\n");
                            }
                         }
                     }
                    break;
                 }
             case 2:                   // Recurring deposit account
                 {
                     printf("Currentiy servises are unavailable....\n ");exit(0);
                     //new_account.account_type[0]=fd[0];
                     //new_account.account_type[1]=fd[1];
                     // break;
                 }
             case 3:                  // fixed deposit account
                 {
                     printf("Currentiy servises are unavailable....\n ");exit(0);
                     //new_account.account_type[0]=rd[0];
                     //new_account.account_type[1]=rd[1];
                     // break;
                 }
             default : printf("Invalid account type\n");
        }
    fwrite(&new_account,sizeof(struct creat),1,fp);         //storing account information in file
    fclose(fp);
    fpp=fopen("E:/file_handling/sb_account.txt","a+");
            current.account_no=new_account.account_no;
            current.amount =new_account.deposit;
            printf(" %ld  %.2f\n",current.account_no,current.amount);
            fwrite(&current,sizeof(struct sb),1,fpp);       //storing trasaction information in file
    fclose(fpp);
}

void manager_view()
{
    FILE *fp;
    fp=fopen("E:/file_handling/my_bank.txt","r");
    while(fread(&temp,sizeof(struct creat),1,fp))
    {
          printf("%s %-5s\t%d/%d/%d    %lld     %s      %lld        %ld\t%s\n",temp.fname,temp.lname,temp.dob.date,temp.dob.month,temp.dob.year,temp.adhar,temp.pan,temp.mobile,temp.account_no,temp.account_type);
    }
    fclose(fp);
}

int dateofbirth(int d,int m,int y) //date of birth verification function
{
    int n=0,temp;
    temp=y;
    while(temp>0)                  //year length verification
    {
        temp=temp/10;
        n++;
    }
    if(y >= 1947 && n==4 &&  y <= 2019)  //only valid from 1947 to 2019
    {
        if(y%4==0)                       //for leaf year
        {
            if(m==1 ||m==3 ||m==5 ||m==7 ||m==8 ||m==10 ||m==12) //months which haveing 31 days
            {
                if(d<= 31) return 1;
                else return 0;
            }
            else if(m==2)                        //february month
            {
                if(d <= 29) return 1;
                else return 0;
            }
            else if(m==4 ||m==6 ||m==9 ||m==11 ) // months which having 30 days
            {
                if(d<=30) return 1;
                else return 0;
            }
            else return 0;
         }
         else                             //not leaf year
         {
             if(m==1 ||m==3 ||m==5 ||m==7 ||m==8 ||m==10 ||m==12) //months which have 31 days
             {
                if(d<= 31) return 1;
             }
             else if(m==2)              //february month
             {
                if(d <= 28) return 1;
             }
             else if(m==4 ||m==6 ||m==9 ||m==11 )  //months which having 30 days
             {
                if(d<=30) return 1;
             }
             else return 0;
          }
    }
    else return 0;                     //invalid year
}

int adhar(long long int x)
{
    int n=0;
    long long int y=x;
    while(x>0)
    {
        x=x/10;
        n++;
    }
    if(n==12)
    {
        FILE *fp;
        fp=fopen("E:/file_handling/my_bank.txt","r");  //open file in reading mode
        if(fread(&temp_adhar,sizeof(struct creat),1,fp) == NULL) return 1;
        else
        {
            do
            {
                  if(temp_adhar.adhar == y)
                  {
                        fclose(fp);
                        return 2;
                  }
            }while(fread(&temp_adhar,sizeof(struct creat),1,fp));
            fclose(fp);
            return 1;
        }
    }
    else return 0;
}

int pancard(char pan[])
{
    int i,j,k=0,l=0;
    for(i=0;pan[i] != '\0';i++)
    {
         if(i<=4) //check first 5 characters are alphabets
         {
            j=pan[i];
            if( j>=65 && j<=90) k++;
            else return 0;
         }
         else if(i>4 && i<9)//check next 4 characters are numbers
         {
             j=pan[i];
             if( j >= 48 && j <= 57) k++;
             else return 0;
         }
         else if(i == 9)//check last character is alphabet
         {
             j=pan[i];
             if( j>=65 && j<=90) k++;
             else return 0;
         }
      }
         if(k==10)
         {
             FILE *fp;
             fp=fopen("E:/file_handling/my_bank.txt","r");  //open file in reading mode
             if(fread(&temp_pan,sizeof(struct creat),1,fp)== NULL) return 1;
             else{
                do
               {
                l=strcmp(temp_pan.pan,pan);

                   if(l== 0)
                    {
                      fclose(fp);
                      return 2;
                    }
               }while(fread(&temp_pan,sizeof(struct creat),1,fp));
               fclose(fp);
               return 1;
            }
        }
}

int pincode(int a)
{
    int i=0;
    while(a>0)
    {
        a=a/10;
        i++;
    }
    if(i==6) return 1;
    else return 0;
}

int mobile(long long int y)
{
    int i=0,j;
    long long int x=y;
    while(y>0)
    {
        y=y/10;
        i++;
    }
    if(i==10)
    {
        FILE *fp;
        fp=fopen("E:/file_handling/my_bank.txt","r");  //open file in reading mode
        if(fread(&temp_mobile,sizeof(struct creat),1,fp) == NULL) return 1;
        else
        {
            do
            {
                  if(temp_mobile.mobile == x)
                  {
                        fclose(fp);
                        return 2;
                  }
            }while(fread(&temp_mobile,sizeof(struct creat),1,fp));
            fclose(fp);
            return 1;
        }
    }
    else return 0;
}

int password(int pass,int repass)
{
    int i=0,temp=pass;
    while(temp>0)
    {
        i++;
        temp=temp/10;
    }
    if(i==4)
    {
      if(pass==repass) return 1;
      else return 0;
    }
    else return 2;
}

long int gen_ac_no(int pin)
{
    int n=0;
    FILE *fp;
    fp=fopen("E:/file_handling/my_bank.txt","r");
        while(fread(&temp_ac,sizeof(struct creat),1,fp))
            if(temp_ac.address.pincode == pin) n++;
    fclose(fp);
    return pin*1000+n;
}

int Deposit_Amount()
{
    float amount;
    FILE *fp,*fpp;
    fp=fopen("E:/file_handling/sb_account.txt","r");
    fpp=fopen("E:/file_handling/temp.txt","w");
    printf("Enter deposite amount : ");
    scanf("%f",&amount);

    while(fread(&temp1,sizeof(struct sb),1,fp))
    {
        if(temp1.account_no == temp.account_no)
        {
           temp2.account_no= temp1.account_no;
           temp2.amount = temp1.amount +amount;
        }
        else
        {
            temp2.account_no= temp1.account_no;
            temp2.amount = temp2.amount;
        }
        fwrite(&temp2,sizeof(struct sb),1,fpp);
    }
          fclose(fp);
          fclose(fpp);

    fp=fopen("E:/file_handling/temp.txt","r");
    fpp=fopen("E:/file_handling/sb_account.txt","w");
    while(fread(&temp1,sizeof(struct sb),1,fp))
    {
        temp2.account_no= temp1.account_no;
        temp2.amount = temp2.amount;
        fwrite(&temp2,sizeof(struct sb),1,fpp);
    }
    fclose(fp);
    fclose(fpp);

}

int Withdraw_Amount()
{
    float amount;
    FILE *fp,*fpp;
    fp=fopen("E:/file_handling/sb_account.txt","r");
    fpp=fopen("E:/file_handling/temp.txt","w");
    printf("Enter withdraw amount : ");
    scanf("%f",&amount);

    while(fread(&temp1,sizeof(struct sb),1,fp))
    {
        if(temp1.account_no == temp.account_no)
        {
            if(temp.checkbook ==0)
            {
                if(temp1.amount - amount >= 1000)
                {
                  temp2.account_no= temp1.account_no;
                  temp2.amount = temp1.amount -amount;
                }
                else printf("You should mentain minimum balance.....!\n");
            }
            if(temp.checkbook ==1)
            {
                if(temp1.amount - amount >= 3000)
                {
                  temp2.account_no= temp1.account_no;
                  temp2.amount = temp1.amount -amount;
                }
                else printf("You should mentain minimum balance.....!\n");
            }

        }
        else
        {
            temp2.account_no= temp1.account_no;
            temp2.amount = temp2.amount;
        }
        fwrite(&temp2,sizeof(struct sb),1,fpp);
    }
          fclose(fp);
          fclose(fpp);

    fp=fopen("E:/file_handling/temp.txt","r");
    fpp=fopen("E:/file_handling/sb_account.txt","w");
    while(fread(&temp1,sizeof(struct sb),1,fp))
    {
        temp2.account_no= temp1.account_no;
        temp2.amount = temp2.amount;
        fwrite(&temp2,sizeof(struct sb),1,fpp);
    }
    fclose(fp);
    fclose(fpp);
}

int Balance_Enquiry()
{
    FILE *fp;
    fp=fopen("E:/file_handling/sb_account.txt","r");
    while(fread(&temp1,sizeof(sb),1,fp))
    {
        if(temp1.account_no == temp.account_no)
        printf("\n\n Balance amount =  %.2f\n\n",temp1.amount);
    }
    fclose(fp);
    return 0;
}

int Change_password()
{
    int pass,repass,g=0;
    while(g!=1)                             //password verification
    {
        printf("Password (4 digit) : ");
        scanf(" %d",&pass);
        printf("Re enter Password : ");
        scanf("%d",&repass);
        g=password( pass,repass);
        if(g==1)
        {
            FILE *fp,*fpp;
            fp=fopen("E:/file_handling/my_bank.txt","r");
            fpp=fopen("E:/file_handling/temp.txt","w");
            while(fread(&change,sizeof(struct creat),1,fp))
            {
                if(change.mobile == temp.mobile)
                {
                    change1=change;
                    change1.password=pass;
                    fwrite(&change1,sizeof(struct creat),1,fpp);
                }
                else
                {
                    change1=change;
                    fwrite(&change1,sizeof(struct creat),1,fpp);
                }
            }
            fclose(fp);
            fclose(fpp);
            fp=fopen("E:/file_handling/my_bank.txt","w");
            fpp=fopen("E:/file_handling/temp.txt","r");
            while(fread(&change,sizeof(struct creat),1,fpp))
            {
                change1=change;
                fwrite(&change1,sizeof(struct creat),1,fp);
            }
            exit(0);
        }
        else if(g==2) printf("password Length must be 4 digits....!\n");
    }
}

int my_passbook()
{
   int i;
   FILE *fp;
   fp=fopen("E:/file_handling/my_bank.txt","r");
   while(fread(&my_p,sizeof(struct creat),1,fp))
   {
       if(my_p.mobile == temp.mobile)
       {
          printf("\n\n\n");
          for(i=0;i<75;i++) printf("\xcd");
          printf("\n");
          printf("****************************** PATIL'S BANK *******************************\n");
          for(i=0;i<75;i++) printf("\xcd");
          printf("\n\n");
          printf("            Account no : %ld            Type : %s \n\n",my_p.account_no,my_p.account_type);
          printf("Name    : %s %s %s\n",my_p.fname,my_p.pname,my_p.lname);
          printf("DOB     : %d/%d/%d\n",my_p.dob.date,my_p.dob.month,my_p.dob.year);
          printf("Mobile  : %lld\n",my_p.mobile);
          printf("Address : %d, %s, %s\n",my_p.address.hno,my_p.address.area,my_p.address.taluk);
          printf("          %s, %s\n",my_p.address.dist,my_p.address.state);
          printf("          %s %d\n",my_p.address.country,my_p.address.pincode);
          printf("\n\n");
          for(i=0;i<75;i++) printf("\xcd");
          printf("\n");
       }
   }
   fclose(fp);
   fp=fopen("E:/file_handling/sb_account.txt","r");
   while(fread(&my_balance,sizeof(struct sb),1,fp))
   {
       if(my_balance.account_no == temp.account_no)
        printf("                                      Balance amount : %.2f/-\n",my_balance.amount);
   }
   fclose(fp);
   for(i=0;i<75;i++) printf("\xcd");
   printf("\n\n");
}

int delete_account()
{
    int choice,pass;
    printf("Delete your account permanently...?\n");
    printf("[1] Yes\n");
    printf("[2] No\n");
    printf("Enter your choice : ");
    scanf("%d",&choice);
    if(choice ==1)
    {
        printf("login password  : ");
        scanf(" %d",&pass);
        if(temp.password == pass)
        {
           FILE *fp,*fpp;
           fp=fopen("E:/file_handling/my_bank.txt","r");
            fpp=fopen("E:/file_handling/temp.txt","w");
            while(fread(&delete_ac,sizeof(struct creat),1,fp))
            {
                if(delete_ac.account_no != temp.account_no) fwrite(&delete_ac,sizeof(struct creat),1,fpp);
            }
            fclose(fp);
            fclose(fpp);
            fp=fopen("E:/file_handling/my_bank.txt","w");
            fpp=fopen("E:/file_handling/temp.txt","r");
            while(fread(&delete_ac,sizeof(struct creat),1,fpp))
            {
                fwrite(&delete_ac,sizeof(struct creat),1,fp);
            }
            fclose(fp);
            fclose(fpp);
            fp=fopen("E:/file_handling/sb_account.txt","r");
            fpp=fopen("E:/file_handling/temp.txt","w");
            while(fread(&temp1,sizeof(struct sb),1,fp))
            {
                if(temp1.account_no != temp.account_no) fwrite(&temp1,sizeof(struct sb),1,fpp);
            }
            fclose(fp);
            fclose(fpp);
            fp=fopen("E:/file_handling/sb_account.txt","w");
            fpp=fopen("E:/file_handling/temp.txt","r");
            while(fread(&temp1,sizeof(struct sb),1,fpp))
            {
                fwrite(&temp1,sizeof(struct creat),1,fp);
            }
            fclose(fp);
            fclose(fpp);
            exit(0);

        }
        else
        {
            printf("Wrong password....\n");
            return 0;
        }
    }
    else if(choice == 2) return 0;
    else exit(0);
}
