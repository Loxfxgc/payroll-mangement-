#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>

COORD coord={0,0};

void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
int main()
{
    FILE *fp,*ft;
    char another,choice;

    struct emp
    {
     char name[40];
     int age;
     float salery;
    };
    struct emp e;

    char empname[40];
    long int recsize ;

    fp=fopen("EMP.DAT","rb+");

    if(fp==NULL)
    {
        fp=fopen("EMP.DAT","wb+");
        if(fp==NULL)
        {
            printf("cannot open the file");
            exit(1);
        }
    }

    recsize=sizeof(e);

    while(1)
    {
system("cls");
gotoxy(30,10);
printf("1. Add Record");
gotoxy(30,12);
printf("2. List Records");
gotoxy(30,14);
printf("3. Modify Records");
gotoxy(30,16);
printf("4. Delete Records");
gotoxy(30,18);
printf("5. Exit");
gotoxy(30,20);
printf("Your Choice: ");
fflush(stdin);
choice = getche();
switch(choice)
{
case '1':
system("cls");
fseek(fp,0,SEEK_END);
another = 'y';

while (another == 'y')

{
printf("\nEnter name: ");
scanf("%s",e.name);
printf("\nEnter age: ");
scanf("%d", &e.age);
printf("\nEnter basic salary: ");
scanf("%f", &e.salery);

fwrite(&e, recsize,1,fp);

printf("\nAdd another record(y/n) ");
fflush(stdin);
another = getche();
}
break;

case '2':
system("cls");
rewind(fp);
while(fread(&e, recsize,1,fp)==1)
{
printf("\n%s %d %.2f",e.name,e.age,e.salery);
}
getch();
break;

case '3':
system("cls");
another = 'y';
while (another == 'y')
{
printf("Enter the employee name to modify: ");
scanf("%s", empname);
rewind(fp);
while(fread(&e, recsize,1,fp)==1)
{
if(strcmp(e.name, empname) == 0)
{
printf("\nEnter new name, age and salery: ");
scanf("%s%d%f",e.name,&e.age,&e.salery);
fseek(fp,-recsize, SEEK_CUR);
fwrite(&e, recsize,1,fp);
break;
}
}
printf("\nModify another record(y/n)");
fflush(stdin);
another = getche();
}
break;
case '4':
system("cls");
another = 'y';
while(another == 'y')
{
printf("\nEnter name of employee to delete: ");
scanf("%s", empname);
ft = fopen("Temp.dat", "wb");
rewind(fp);
while(fread(&e, recsize,1,fp) == 1)
{
if(strcmp(e.name,empname) != 0)
{
fwrite(&e, recsize, 1, ft);
}
}
fclose(fp);
fclose(ft);
remove("EMP.DAT");
rename("Temp.dat", "EMP.DAT");
fp = fopen("EMP.DAT", "rb+");
printf("Delete another record(y/n)");
fflush(stdin);
another = getche();
}
break;
case '5':
    fclose(fp);
    exit(0);
}}}
