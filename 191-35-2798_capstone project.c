#include <stdio.h> ///for input output functions like printf, scanf
#include <stdlib.h>
#include <conio.h>
#include <windows.h> ///for windows related functions
#include <string.h>  ///string operations

// Used Function
void add_data();
void modify();
void delet();
void list();




    FILE *fp, *ft; /// file pointers
    char another, choice;

    /** structure that represent a student */
    struct std
    {
        char name[40]; ///name of student
        int age; /// age of student
        float bs; /// ID of student
    };

    struct std e; /// structure variable creation

    char stdname[40]; /// string to store name of the student

    long int recsize; /// size of each record of student


/** Main function started */

int main()
{
    /** open the file in binary read and write mode
    * if the file EMP.DAT already exists then it open that file in read write mode
    * if the file doesn't exit it simply create a new copy
    */
    fp = fopen("EMP.DAT","rb+");
    if(fp == NULL)
    {
        fp = fopen("EMP.DAT","wb+");
        if(fp == NULL)
        {
            printf("Connot open file");
            exit(1);
        }
    }
    /// infinite loop continues untile the break statement encounter
    while(1)
    {
        system("cls"); ///clear the console window

        printf("1. Add Record\n"); /// option for add record

        printf("2. List Records\n"); /// option for showing existing record

        printf("3. Modify Records\n"); /// option for editing record

        printf("4. Delete Records\n"); /// option for deleting record

        printf("5. search Records\n");

        printf("5. Exit\n"); /// exit from the program

        printf("Your Choice: "); /// enter the choice 1, 2, 3, 4, 5
        fflush(stdin); /// flush the input buffer
        choice  = getche(); /// get the input from keyboard
        switch(choice)
        {
        case '1':  /// if user press 1
            add_data();
            break;
        case '2':
            list();
            break;

        case '3':  /// if user press 3 then do editing existing record
            modify();

            break;
        case '4':
            delet();
            break;
        case '5':
            search();
            break;
        case '6':
            fclose(fp);  /// close the file
            exit(0); /// exit from the program
        }
    }
    return 0;
}
void add_data()
{
  system("cls");
            fseek(fp,0,SEEK_END); /// search the file and move cursor to end of the file
            /// here 0 indicates moving 0 distance from the end of the file

            another = 'y';
            while(another == 'y')  /// if user want to add another record
            {
                printf("\nEnter name: ");
                scanf("%s",e.name);
                printf("\nEnter age: ");
                scanf("%d", &e.age);
                printf("\nEnter ID: ");
                scanf("%f", &e.bs);

                fwrite(&e,recsize,1,fp); /// write the record in the file

                printf("\nAdd another record(y/n): ");
                fflush(stdin);
                another = getche();
            }
}
void modify()
{
 system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("Enter the student name to modify: ");
                scanf("%s", stdname);
                rewind(fp);
                while(fread(&e,recsize,1,fp)==1)  /// fetch all record from file
                {
                    if(strcmp(e.name,stdname) == 0)  ///if entered name matches with that in file
                    {
                        printf("\nEnter new name,age and ID: ");
                        scanf("%s%d%f",e.name,&e.age,&e.bs);
                        fseek(fp,-recsize,SEEK_CUR); /// move the cursor 1 step back from current position
                        fwrite(&e,recsize,1,fp); /// override the record
                        break;
                    }
                }
                printf("\nModify another record(y/n):");
                fflush(stdin);
                another = getche();
            }
}
void delet()
{
    system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter name of student to delete: ");
                scanf("%s",stdname);
                ft = fopen("Temp.dat","wb");  /// create a intermediate file for temporary storage
                rewind(fp); /// move record to starting of file
                while(fread(&e,recsize,1,fp) == 1)  /// read all records from file
                {
                    if(strcmp(e.name,stdname) != 0)  /// if the entered record match
                    {
                        fwrite(&e,recsize,1,ft); /// move all records except the one that is to be deleted to temp file
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("EMP.DAT"); /// remove the orginal file
                rename("Temp.dat","EMP.DAT"); /// rename the temp file to original file name
                fp = fopen("EMP.DAT", "rb+");
                printf("Delete another record(y/n):");
                fflush(stdin);
                another = getche();
            }
}
void list()
{
    recsize = sizeof(e);
    system("cls");
            rewind(fp); ///this moves file cursor to start of the file
            while(fread(&e,recsize,1,fp)==1)  /// read the file and fetch the record one record per fetch
            {
                printf("\n%s %d %.2f",e.name,e.age,e.bs); /// print the name, age and ID
            }
            getch();

}
void search()
{
   int k=0;
    system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("\nEnter name of student to search: ");
                scanf("%s",stdname);
                rewind(fp);
                while(fread(&e,recsize,1,fp) == 1)
                {
                    if(strcmp(e.name,stdname) == 0)
                    {
                       k=1;
                       break;

                    }
                    else
                    {
                        k=0;

                    }
                }
                if(k==1){printf("found\n");}
                else if (k==0){printf("not found\n");}


                 printf("\nModify another record(y/n):");
                fflush(stdin);
                another = getche();
            }

}


