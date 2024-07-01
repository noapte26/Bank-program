#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
int *globalPointer;
typedef struct{
    int m;
    int y;
}date;
typedef struct{
    long long int account_number;
    char name[100];
    char mobile[20];
    char email[100];
    double balance;
    date d;
}account;
typedef struct
{
    long long int accnumm;
    float transactions;
}transactionsdata;
void initializeGlobalPointer() {
    int n=0;
     if (globalPointer != NULL) {
        free(globalPointer);
    }
    // Allocate memory and assign its address to the global pointer
    globalPointer = (int *)malloc(sizeof(int));
     FILE* file_acc;
    file_acc = fopen("accounts.txt", "r");

        // Count the number of users in the file
     while (fscanf(file_acc, "%*d,%*[^,],%*s,%*f,%*s,%*d-%*d\n") == 0) {
        n++;
    }
    *globalPointer=n;
    fclose(file_acc);
}
account* Load(){
    int n ,k =0;
    n=*globalPointer;
    account* accounts = (account*)malloc(n * sizeof(account));

    FILE* file_acc;
    file_acc = fopen("accounts.txt", "r");

    int i = 0;

    while (i < n && fscanf(file_acc, "%lld,%[^,],%[^,],%lf,%[^,],%d-%d\n", &accounts[i].account_number, accounts[i].name, accounts[i].email, &accounts[i].balance, accounts[i].mobile, &accounts[i].d.m, &accounts[i].d.y) == 7) {
        i++;
    }

    fclose(file_acc);
    return accounts;
}
int save(account a[]) {
    int n;
    n=*globalPointer;
    int save_confirmed = 0,i;

    while (!save_confirmed) {
        printf("Do you want to save changes ? (y/n): ");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            save_confirmed = 1;

        } else if (choice == 'n' || choice == 'N') {
            printf("Changes discarded.\n");
            return 0;
        } else {
            printf("Invalid choice. Please enter 'y' or 'n'.\n");
        }

    }

     FILE *fp = fopen("accounts.txt", "w");
    for (i=0;i<n;i++)
    {
      fprintf(fp, "%lld,%s,%s,%lf,%s,%d-%d\n", a[i].account_number, a[i].name, a[i].email, a[i].balance, a[i].mobile, a[i].d.m, a[i].d.y);
    }
    fclose(fp);
    return 1;
}

int savedelete(account a[]) {
    int n;
    n=*globalPointer;
    int save_confirmed = 0,i;

    while (!save_confirmed) {
        printf("Do you want to save changes (y/n): ");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            save_confirmed = 1;

        } else if (choice == 'n' || choice == 'N') {
            printf("Changes discarded.\n");
            return 0;
        } else {
            printf("Invalid choice. Please enter 'y' or 'n'.\n");
        }

    }
     FILE *fp = fopen("accounts.txt", "w");
    for (i=0;i<n-1;i++)
    {
      fprintf(fp, "%lld,%s,%s,%lf,%s,%d-%d\n", a[i].account_number, a[i].name, a[i].email, a[i].balance, a[i].mobile, a[i].d.m, a[i].d.y);
    }
    fclose(fp);
    initializeGlobalPointer();
    return 1;
}
int isAccount_numberValid(long long int accountNumber){
    char sAccountNum[20];
    sprintf(sAccountNum, "%lld", accountNumber);    /*storing account number as a string*/
    int i , count=0;
    for(i=0 ; i< 10 ; i++){
        if(isdigit(sAccountNum[i])){
            count++;
        }
    }
    if(strlen(sAccountNum) == 10 && count == 10){
        return 1;
    }
    else{

        return 0;
    }

}
int validate_email(char *email) {
    int length=strlen(email);
    int counter=0;
    int i, count, n1 = -1, n2 = -1;
    for (i =length-1; i>-1; i--) {
        if (email[i] == '@')
            n1 = i;
        else if (email[i] == '.')
            if(counter==0){
            counter++;
            n2 = i;}
    }
    if (n1 == -1 || n2 == -1 || n1 > n2)
        {return 0;}
     else return 1;




}

void Withdraw()
{
     int n,flag=0,i;
    n=*globalPointer;
    account* accounts=Load();
    long long int accnum;
    printf("Please, Enter the account number \n");
    scanf("%lld",&accnum);
    for(i=0 ; i<n ; i++){
        if(accnum == accounts[i].account_number){
              flag=i ;
               break; }
           }
if (flag==0 && i !=0 )
     {printf("This account does not exist ");
     printf("Returning to main menu \n");
     Menu();
     }

       float Withdrawalmoney;
        printf("Enter the value you want to Withdraw\n");
        printf("Note 'Maximum withdrawal is 10,000$ per transaction\n");
        scanf("%f",&Withdrawalmoney);
        Withdrawalmoney=abs(Withdrawalmoney);
       while(abs(Withdrawalmoney)>10000)
       {
           printf("Wrong value , Please re-enter it");
           scanf("%f",&Withdrawalmoney);
           Withdrawalmoney=abs(Withdrawalmoney);
       }
       if(Withdrawalmoney>accounts[flag].balance)
       {
           printf("Insufficient Funds, returning to main menu");
          Menu();
       }
       accounts[flag].balance=accounts[flag].balance-Withdrawalmoney;
       FILE *Tpointer;
       int num = save(accounts);
       if (num!=0)
       {
       Tpointer=fopen("reportfile.txt","a");
       fprintf(Tpointer,"%lld %f\n",accnum,(-Withdrawalmoney));
       fclose(Tpointer);
       printf("Withdrawal Success\n");}
       printf("Returning to main menu \n");
       Menu();


    }
void Deposit()
{
 int n,flag=0,i;
    n=*globalPointer;
    account* accounts=Load();
    long long int accnum;
    printf("Please, Enter the account number \n");
    scanf("%lld",&accnum);
    for(i=0 ; i<n ; i++){
        if(accnum == accounts[i].account_number){
              flag=i ;
               break; }
           }
if (flag==0 && i !=0 )
     {printf("This account does not exist ");
     printf("Returning to main menu \n");
     Menu();
     }

       float Depositmoney;
        printf("Enter the value you want to Deposit\n");
        printf("Note 'Maximum Deposit is 10,000$ per transaction\n");
        scanf("%f",&Depositmoney);
        Depositmoney=abs(Depositmoney);
       while(abs(Depositmoney)>10000)
       {
           printf("Wrong value , Please re-enter it");
           scanf("%f",&Depositmoney);
           Depositmoney=abs(Depositmoney);
       }
       accounts[flag].balance=accounts[flag].balance+Depositmoney;
       FILE *Tpointer;
       int num = save(accounts);
       if (num!=0)
       {
       Tpointer=fopen("reportfile.txt","a");
       fprintf(Tpointer,"%lld %f\n",accnum,(+Depositmoney));
       fclose(Tpointer);
       printf("Deposite Success\n");}
       printf("Returning to main menu \n");
       Menu();

    }
void Transfer()
{
    int n,flag=0,flag2=0,i,j;
    n=*globalPointer;
    account* accounts=Load();
    long long int accnumto,accnumfrom;
    printf("Please, Enter the account number that will send the money \n");
    scanf("%lld",&accnumfrom);
    for(i=0 ; i<n ; i++){
        if(accnumfrom == accounts[i].account_number){
              flag=i ;
               break; }
           }
           if (flag==0 && i !=0 )
     {printf("This account does not exist ");
     printf("Returning to main menu \n");
      Menu();
     }

    printf("Please, Enter the account number that will recieve the money \n");
    scanf("%lld",&accnumto);
    for(j=0 ; j<n ; j++){
        if(accnumto == accounts[j].account_number){
              flag2=j ;
               break; }
           }
           if (flag2==0 && j !=0 )
     {printf("This account does not exist ");
      Menu();
     }

    float Transferedmoney;
    printf("Enter the value you want to Transfer");
    scanf("%f",&Transferedmoney);
     if(Transferedmoney>accounts[flag].balance)
       {
           printf("Error Insufficient Funds, returning to main menu");
           Menu();
       }

       accounts[flag].balance=accounts[flag].balance-Transferedmoney;
       accounts[flag2].balance=accounts[flag2].balance+Transferedmoney;
       FILE *Tpointer;
       int num = save(accounts);
       if (num!=0){
       Tpointer=fopen("reportfile.txt","a");
       fprintf(Tpointer,"%lld %f\n",accnumfrom,(-Transferedmoney));
       fprintf(Tpointer,"%lld %f\n",accnumto,(Transferedmoney));
       fclose(Tpointer);
       printf("\n Money transferred successfully\n");}
       printf("Returning to main menu \n");
       Menu();


}


void Report() {
    int n, flag = -1, i;
    n = *globalPointer;
    account *accounts = Load();
    long long int accnum;
    printf("Enter the account number of the account you want to report:\n");
    scanf("%lld", &accnum);

    for (i = 0; i < n; i++) {
        if (accnum == accounts[i].account_number) {
            flag = i;
            break;
        }
    }

    if (flag == -1) {
        printf("This account does not exist.\n");
        printf("Returning to main menu.\n");
        Menu();

    }

    FILE *Tpointer;
    Tpointer = fopen("reportfile.txt", "r");

    if (Tpointer == NULL) {
        printf("Error opening the report file.\n");
        printf("Returning to main menu.\n");
        Menu();

    }

    int counter = 0;
    while (fscanf(Tpointer, "%*lld %*f\n") != EOF) {
        counter++;
    }

    rewind(Tpointer);

    if (counter == 0) {
        printf("No transactions in the report file.\n");
        printf("Returning to main menu.\n");
        fclose(Tpointer);
        Menu();
    }

    transactionsdata t[counter];

    int k = 0;
    while (fscanf(Tpointer, "%lld %f\n", &t[k].accnumm, &t[k].transactions) == 2) {
        k++;
    }

    fclose(Tpointer);


    int z = counter - 1, printtranscounter = 0;
    while (printtranscounter < 5 && z >= 0) {
        if (accnum == t[z].accnumm) {
            printf("\n %lld\t %.3f $ \n", t[z].accnumm, t[z].transactions);
            printtranscounter++;
        }
        z--;
    }

    if (printtranscounter == 0) {
        printf("No transactions on this account.\n");
    }
int num9 ;
printf("\nenter a number : 1. Return to main menu\n2. Quit\n");
scanf("%d",&num9);
if(num9==1)
Menu ();
else if (num9==2)
    Quit();
else {printf("Invalide choice, returning to main menu");
       Menu();}
}

char* Firstname(char *name) {
   char temp[100];
   strcpy(temp,name);
    char *token = strtok(temp," ");
    return token;
}
char* Secondname(char *name)
{
    char temp1[100];
   strcpy(temp1,name);
   strtok(temp1, " ");
   char *token;
   token = strtok(NULL, " ");
   return token;
}
void Advancedsearch() {
    getchar();
    printf("\n");
    int flag = 0, flag2 = 0, n, i;
    account* accounts = Load();
    n = *globalPointer;
    char keyword[100];

    printf("Please, Enter the Keyword: \n ");
    gets(keyword);


    for (i = 0; i < n; i++) {
        if (stricmp(keyword, Firstname(accounts[i].name)) == 0) {
            flag = 1;
            printAccountInfo(accounts[i]);
        }
    }


    for (i = 0; i < n; i++) {
        if (stricmp(keyword, Secondname(accounts[i].name)) == 0) {
            flag2 = 1;
            printAccountInfo(accounts[i]);
        }
    }

    if (flag == 0 && flag2 == 0) {
        printf("\n No account Found that matches this keyword\n");
    }

   int num9 ;
printf("\nenter a number : 1. Return to main menu\n2. Quit\n");
scanf("%d",&num9);
if(num9==1)
Menu ();
else if (num9==2)
    Quit();
else {printf("Invalide choice, returning to main menu");
       Menu();}
}
int checkAccountNum(account a [], long long num)
{ int i ,n;
n=*globalPointer;
for (i=0;i<n;i++)
{
    if (num==a[i].account_number)
    {
        return 0 ;
    }
}
return 1 ;
}
void Add(){
    time_t t = time (NULL) ;
    struct tm date = *localtime (&t);
    int n,m,flag1,flag2;
    n=*globalPointer;
    account* accounts= Load();
    account newAccount;
    newAccount.d.y = date.tm_year+1900 ;
    newAccount.d.m = date.tm_mon+1 ;
    int i;
    printf("enter the account number (recommended '%lld'):\n",accounts[n-1].account_number+1);
    scanf("%lld",&newAccount.account_number);

    while(1){   flag1= checkAccountNum(accounts,newAccount.account_number );
                flag2 = isAccount_numberValid(newAccount.account_number);
            if (flag1==1&&flag2==1) break ;
            else if (flag2==0)
            {  printf("Invalid account number, please enter another one consists of 10 digits\n");
               scanf("%lld",&newAccount.account_number);}
            else if (flag1==0)
             { printf("This account number already exists please enter another one\n");
                scanf("%lld",&newAccount.account_number);}
           }
    while (getchar() != '\n'); //this constructs a loop that repeatedly calls getchar() until a newline character is encountered


    printf("Enter the name :\n");
    gets(newAccount.name);
    printf("enter the mobile:\n");
    scanf("%s", newAccount.mobile);
    getchar();

    while (strlen(newAccount.mobile)!= 11){
        printf("Invalid phone number, please, enter 11 digits \n");
        scanf("%s", newAccount.mobile);
        getchar();
        }

    printf("Enter the email address:\n");
    gets(newAccount.email);


    while(! validate_email(newAccount.email)){
        printf("Invalid email address.. please, try again \n");
        gets(newAccount.email);
    }

    printf("Enter the balance: \n");
    scanf("%lf",&newAccount.balance);
    int save_confirmed = 0;
    while (!save_confirmed) {
        printf("Do you want to save changes ? (y/n): ");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'y' || choice == 'Y') {
            save_confirmed = 1;

        } else if (choice == 'n' || choice == 'N') {
            printf("Changes discarded.\n");
            Menu();
        } else {
            printf("Invalid choice. Please enter 'y' or 'n'.\n");
        }

    }
    char fileName[20];
    sprintf(fileName, "%lld.txt", newAccount.account_number);

    FILE* newFile;
    newFile = fopen(fileName, "w");
    fprintf(newFile,"%lld,%s,%s,%f,%s,%d-%d\n",newAccount.account_number,newAccount.name,newAccount.email,newAccount.balance,newAccount.mobile,newAccount.d.m,newAccount.d.y );
    fclose(newFile);

    FILE *fp = fopen("accounts.txt", "a");
    fprintf(fp, "%lld,%s,%s,%lf,%s,%d-%d\n", newAccount.account_number, newAccount.name, newAccount.email,newAccount.balance,newAccount.mobile,newAccount.d.m, newAccount.d.y);
    fclose(fp);
    initializeGlobalPointer();
    printf("\nThe account has been successfully added\n\n");
    printf("\nReturning to main menu\n\n");
    Menu();
}
void Modify(){
    account* accounts=Load();
    int i, flag =0,m,z ;
    int n;
    n=*globalPointer;
    char newMobile[20];
    char newEmail[20];
    long long int accountNum;
    printf("enter the account number of account you want to modify \n");
    scanf("%lld",&accountNum);
    for(i=0 ; i<n ; i++){
        if(accountNum == accounts[i].account_number){
              flag=i ;
               break; }
           }
if (flag==0 && i !=0 )
     {printf("This account does not exist \n");
     printf("Returning to main menu \n");
     Menu();
     }

else {for (i=0;i<n;i++)
    {
        if (i==flag)
        {printf("what do you want to change please enter a number :\n1.mobile number\n2.email\n");
        scanf("%d",&m);
        if (m==1)
        {
        printf("enter the new mobile number\n");
        getchar ();
        scanf("%s",newMobile);
        while (strlen (newMobile)!=11)
        {   printf("Invalid mobile number, please enter a mobile number consists if 11 numbers\n");
            scanf("%s",newMobile);}
        strcpy(accounts[i].mobile,newMobile);
        break ; }

        else if (m==2)
        { printf("enter the new email\n");
        getchar ();
        gets(newEmail);
        z= validate_email(&newEmail) ;
        while (!z)
        {   printf("Invalid email, please enter email and make sure that your email contain '@' and '.' \n");
            scanf("%s",newEmail);
            z= validate_email(&newEmail) ;
            }
        strcpy(accounts[i].email,newEmail);
            break;
        } }
    }
}
    int num = save(accounts);
    if (num!=0)
    {printf("\nThe account has been successfully modified\n\n");}
    printf("Returning to main menu \n\n");
    Menu();

}
void Delete(){
    int n;

   n=*globalPointer;
    account* accounts=Load();
    account newAccounts[n];

    int i,k,flag=0;
    long long int  deletedAccountNum ;
    printf("enter the account number you want to delete: \n");
    scanf("%lld",&deletedAccountNum);
    for (i=0;i<n;i++){
            if (deletedAccountNum==accounts[i].account_number){
                    flag=i;
                    break;}
                    }

    if(flag == 0 && i!=0 ){
        printf("Error: the account you want to delete does not exist\n");
        free(accounts);
        printf("Returning to main menu");
        Menu();
}
    if (accounts[flag].balance > 0)
        {
            printf("this account cannot be deleted ");
            free(accounts);
            printf("Returning to main menu");
            Menu();
        }
    for (k=0,i=0 ; k<n-1 && i<n; k++,i++)
        {
                if (k==flag){
                    i++;
                }
                newAccounts[k].account_number=accounts[i].account_number;
                strcpy(newAccounts[k].name, accounts[i].name);
                strcpy(newAccounts[k].email, accounts[i].email);
                newAccounts[k].balance=accounts[i].balance;
                strcpy(newAccounts[k].mobile, accounts[i].mobile);
                newAccounts[k].d.m=accounts[i].d.m;
                newAccounts[k].d.y=accounts[i].d.y;
        }

    int y=savedelete(newAccounts);
    free(accounts);
    if (y!=0)
    {printf("\nThe account has been successfully deleted\n\n");}
    printf("Returning to main menu \n\n");
    Menu();
}
void printMonth(int num)
{
    switch (num)
    {
        case 1 :  if (num==1) {printf("January");}
        case 2 :  if (num==2) {printf("February");}
        case 3 :  if (num==3) {printf("March");}
        case 4 :  if (num==4) {printf ("April");}
        case 5 :  if (num==5) {printf("May");}
        case 6 :  if (num==6) {printf("June");}
        case 7 :  if (num==7) {printf ("July");}
        case 8 :  if (num==8) {printf("August");}
        case 9 :  if (num==9) {printf("September");}
        case 10 : if (num==10) {printf("October");}
        case 11 : if (num==11) {printf("November");}
        case 12 : if (num==12) {printf("December");}
    }
}
void printAccountInfo(account a){
    printf("\n");
    printf("Account number: %lld\n", a.account_number);
    printf("Name: %s\n", a.name);
    printf("Mobile:%s \n",a.mobile);
    printf("Email: %s \n",a.email );
    printf("Balance: %0.2lf$\n",a.balance);
    printf("Date opened: ");
    printMonth(a.d.m);
    printf(" %d", a.d.y);
    printf("\n");
}
void Query(){
    long long int accountNum;
    printf("enter the account number you want to Search for: \n");
    scanf("%lld",&accountNum);
    account* accounts=Load();

    int i,n;
    n=*globalPointer;
    for(i=0 ; i<n ; i++){
        if(accountNum == accounts[i].account_number){
            printAccountInfo(accounts[i]);
            free(accounts);
            int num9 ;
             printf("\nenter a number : 1. Return to main menu\n2. Quit\n");
               scanf("%d",&num9);
              if(num9==1)
              Menu ();
             else if (num9==2)
             Quit();
else {printf("Invalide choice, returning to main menu");
       Menu();}
        }
    }
    printf("Account not found, returning to main menu\n");
    free(accounts);
    printf("Returning to main menu \n");
    Menu();

}
void sortNameAZ(account a[],int n)
{ int i , j; account temp ;
 for (i=0;i<n;i++)
{ for (j=0;j<n-1;j++)
    {if (strcmp(a[j].name,a[j+1].name)==1)
       {  temp = a[j] ;
           a[j] = a[j+1];
          a[j+1] = temp ;}}}
   for (i=0;i<n;i++)
   { printAccountInfo( a [i]) ;
     printf("\n");
   }
}
void sortNameZA(account a[],int n)
{ int i , j; account temp ;
 for (i=0;i<n;i++)
{ for (j=0;j<n-1;j++)
    {if (strcmp(a[j].name,a[j+1].name)==-1)
       {  temp = a[j] ;
           a[j] = a[j+1];
          a[j+1] = temp ;}}}
   for (i=0;i<n;i++)
   { printAccountInfo( a [i]);
   printf("\n");
   }
}
void sortBalanceAscendingly (account a[],int n)
{ int i,j; account temp ;
for (i=0;i<n;i++)
{ for (j=0;j<n-1;j++)
    {if (a[j+1].balance<a[j].balance)
       {  temp = a[j] ;
           a[j] = a[j+1];
          a[j+1] = temp ;}}}
for (i=0;i<n;i++)
   { printAccountInfo( a [i]);
   printf("\n");
   }}

void sortBalanceDescendingly (account a[],int n)
{ int i,j; account temp ;
for (i=0;i<n;i++)
{ for (j=0;j<n-1;j++)
    {if (a[j+1].balance>a[j].balance)
       {  temp = a[j] ;
           a[j] = a[j+1];
          a[j+1] = temp ;}}}
for (i=0;i<n;i++)
   { printAccountInfo( a [i]);
   printf("\n");
   }}

 void sortDateNewest (account a[],int n)
 { int i , j ; account temp ;
  for (i=0;i<n;i++)
{ for (j=0;j<n-1;j++)
    {if (a[j].d.y<a[j+1].d.y|| (a[j].d.y == a[j + 1].d.y && a[j].d.m < a[j + 1].d.m))
       {  temp = a[j] ;
           a[j] = a[j+1];
           a[j+1] = temp ;} }}
  for (i=0;i<n;i++)
   { printAccountInfo( a [i]);
     printf("\n");
   }}

void sortDateOldest (account a[],int n)
 { int i , j ; account temp ;
  for (i=0;i<n;i++)
{ for (j=0;j<n-1;j++)
    {if (a[j].d.y>a[j+1].d.y|| (a[j].d.y == a[j + 1].d.y && a[j].d.m > a[j + 1].d.m))
       {  temp = a[j] ;
           a[j] = a[j+1];
           a[j+1] = temp ;} }}
  for (i=0;i<n;i++)
   { printAccountInfo( a [i]);
   printf("\n");
   }}

void printSort ()
{ int i,j,num1,n,num=0,num2=0,num3=0;
 n=*globalPointer;
 account* accounts=Load();
printf("Do you want to sort by :\n1. name\n2. balance\n3. date opened\nplease ente a number:  \n");
scanf("%d",&num);
while (( num!=1)&&(num!=2)&&(num!=3))
{
    printf("Invalide input please enter a correct choice ");
    scanf("%d",&num);
}
if (num==1)
 {
     printf("Do you want to print names :\n1. A-Z\n2. Z-A\nplease enter a number: \n");
     scanf("%d",&num1);
     while (( num1!=1)&&(num1!=2))
{   printf("Invalide input please enter a correct choice ");
    scanf("%d",&num1);
}
if (num1==1)
  sortNameAZ(accounts , n);
  else if (num1==2)
    sortNameZA(accounts, n);
}
else if (num==2)
{ printf("Do you want to sort balance :\n1. Ascendingly\n2. Descendingly\nplease enter a number: \n");
     scanf("%d",&num2);
     while (( num2!=1)&&(num2!=2))
   {printf("Invalide input please enter a correct choice ");
    scanf("%d",&num2);}
    if (num2==1)
  sortBalanceAscendingly(accounts , n);
  else if (num2==2)
    sortBalanceDescendingly(accounts, n);
 }
else if (num==3)
{
  printf("Do you want to sort date from :\n1. Newest to Oldest\n2. Oldest to Newest\nplease enter a number: \n");
     scanf("%d",&num3);
     while (( num3!=1)&&(num3!=2))
   {printf("Invalide input please enter a correct choice ");
    scanf("%d",&num3);}
    if (num3==1)
  sortDateNewest(accounts , n);
  else if (num3==2)
   sortDateOldest(accounts, n);
}
int num9 ;
printf("\nenter a number : 1. Return to main menu\n2. Quit\n");
scanf("%d",&num9);
if(num9==1)
{Menu ();}
else if (num9==2)
    {Quit();}
else {printf("Invalide choice, returning to main menu");
       Menu();}


}





void Quit()
{
    exit(1);
}
void Menu()
{
    printf("\n\n\n");
    int Entrynummenu;
    printf("*Welcome to the Main Menu* \n\nEnter (1) to Add Account \n\nEnter (2) to Delete Account\n\nEnter (3) to Modify Account \n\nEnter (4) Search Account\n\nEnter (5) Advanced Search\n\nEnter (6) to Withdraw\n\nEnter (7) to Deposit\n\nEnter (8) to Transfer Money\n\nEnter (9) to Report\n\nEnter (10) to print all User's Data\n\nEnter (0) to Quit the program\n");
    scanf("%d",&Entrynummenu);
    while(Entrynummenu<0 && Entrynummenu>10)
    {
        printf("Wrong number Please enter again");
         printf("Here is the menu \n\nEnter (1) to Add Account \n\nEnter (2) to Delete Account\n\nEnter (3) to Modify Account \n\nEnter (4) Search Account\n\nEnter (5) Advanced Search\n\nEnter (6) to Withdraw\n\nEnter (7) to Deposit\n\nEnter (8) to Transfer Money\nEnter (9) to Report\n\nEnter (10) to print all User's Data\n\nEnter (0) to Quit the program");
        scanf("%d",&Entrynummenu);
    }
   switch(Entrynummenu){
 case 1:
    Add();
    break;
 case 2:
    Delete();
    break;
 case 3:
    Modify();
    break;
 case 4:
    Query();
    break;
 case 5:
    Advancedsearch();
    break;
 case 6:
    Withdraw();
    break;
 case 7:
    Deposit();
    break;
 case 8:
   Transfer();
   break;
   case 9:
   Report();
   break;
   case 10:
   printSort ();
   break;
   case 0:
   Quit();
   break;
    }
}
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n') {
        // read and Cdiscard characters until a newline
    }
}

int main()
{
initializeGlobalPointer();
 FILE* file_acc;
     file_acc = fopen("accounts.txt","r");
    if(file_acc == NULL){
        printf("Unable to Load the account File");
        exit(1);
    }
    int choice;
    char userName[20];
    char password[20];
    FILE* fileUsers;
    fileUsers = fopen("fileusers.txt","r");
    if(fileUsers == NULL){
        printf("File data is missing\n");
        exit(1);
    }
    char FuserName[20];
    char Fpassword[20];
    int flag=0;
    while (1) {
        printf("Menu:\n");
        printf("1. Login\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();


        if (choice == 1) {
            printf("Please, enter the user name:\n");
            scanf("%[^\n]%*c",userName);


            printf("Please, enter the password:\n");
            scanf("%s",password);

            rewind(fileUsers);

            while (fscanf(fileUsers, "%s %s", FuserName, Fpassword) == 2) {
                if (strcmp(userName, FuserName) == 0 && strcmp(password, Fpassword) == 0) {
                    flag = 1;
                    break;
                }
            }

            if (flag) {
                printf("Login successful.\n");
                Menu();
            } else {
                printf("Incorrect user name or Password. Please try again.\n");
            }
        } else if (choice == 2) {
            exit(1);
        } else {
            printf("Invalid choice. Please enter 1 or 2.\n");
        }
    }

    fclose(fileUsers);
}
