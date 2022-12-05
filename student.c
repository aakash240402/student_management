#include<stdio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>

FILE *fp,*tmp;

COORD coord = {0,0};
void gotoxy(int x, int y)
{
    coord.X=x;
    coord.Y=y;
};
struct data
{
    char id[20];
    char name[20];
    char add[20];
    char pname[20];
    char Batch[20];
    char phone_no[20];
}s1;

struct student
{
    struct data stud;
    struct student *next;
}*head,*temp,*curr;

void main()
{
    int pass, x=10;
    char z[5];
    while (x!=0)
    {
        printf("\nInput the password: ");
        scanf("%d",&pass);
        if (pass==1006)
        {
            printf("Correct password");
            x=0;
            int i,j,choice;
            p:
            system("cls");

            printf("\t\t\t\t\tSTUDENT MANAGEMENT SYSTEM \n\n");
            printf("\t\t\t\t1. Insert Student Record\n");
            printf("\t\t\t\t2. Search Student Record\n");
            printf("\t\t\t\t3. Modify Student Record\n");
            printf("\t\t\t\t4. Delete Student Record\n");
            printf("\t\t\t\t5. Show All Records\n");
            printf("\t\t\t\t6. Exit\n\n");
            printf("\t\t\t\t\tEnter your choice: ");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1:
                    system("cls");
                    do
                    {
                        insert();
                        printf("\n\n\t\t\t\t\tAdd Another Student Record (Y, N): ");
                        scanf("%c",z);
                    }while(z=='y'||z=='Y');
                    break;
                case 2:
                    system("cls");
                    search();
                    break;
                case 3:
                    system("cls");
                    modify();
                    break;
                case 4:
                    system("cls");
                    del();
                    break;
                case 5:
                    system("cls");
                    show();
                    break;
                case 6:
                    exit(0);
                    break;
                default:
                    printf("INVALID!!");
                    break;
            }
            getch();
            goto p;
        }
        else
        {
           printf("Wrong password, try another!!");
        }
        printf("\n");
    }
}

void insert()
{
    int i;
    struct student *new_node;
    new_node=(struct student*)malloc(sizeof(struct student));
    printf("\n\t\t\t\t\tEnrollment No.: ");
    for(i=0;i<=29;i++)
    {
        new_node->stud.id[i]='\0';
        new_node->stud.name[i]='\0';
        new_node->stud.add[i]='\0';
        new_node->stud.Batch[i]='\0';
        new_node->stud.phone_no[i]='\0';
    }
    scanf("%s",new_node->stud.id);
    printf("\t\t\t\t\tName: ");
    scanf("%s",new_node->stud.name);
    printf("\t\t\t\t\tAddress: ");
    scanf("%s",new_node->stud.add);
    printf("\t\t\t\t\tParent's name: ");
    scanf("%s",new_node->stud.pname);
    printf("\t\t\t\t\tBatch: ");
    scanf("%s",new_node->stud.Batch);
    printf("\t\t\t\t\tPhone Number: ");
    scanf("%s",new_node->stud.phone_no);
    printf("\n\t\t\t\t\tThe record is successfully added");
    new_node->next=NULL;
    if(head==NULL)
    {
        head=new_node;
        curr=new_node;
    }
    else
    {
        curr->next=new_node;
        curr=new_node;
    }
    fp=fopen("data.txt","ab+");
    fwrite(&curr->stud, sizeof(curr->stud), 1, fp);
    fclose(fp);
}
void search()
{
    int i;
    char s_id[20];
    fp = fopen("data.txt","rb");
    if(fp==NULL)
    {
        printf("\n\t\t\t\t\tCannot Open File!!");
        return;
    }
    for(i=0;i<=19;i++)
    {
        s_id[i]='\0';
        s1.id[i]='\0';
    }
    int isFound = 0;
    printf("\t\t\t\t\tEnter ID to Search: ");
    scanf("%s",s_id);

    i=0;
    while(fread(&s1, sizeof(s1), 1, fp) == 1)
    {
        if(strcmp(s_id,s1.id) == 0)
        {
            isFound = 1;
            break;
        }
    }
    if(isFound == 1)
    {
        printf("\n\n\t\t\t\t\tRECORD FOUND!!\n");
        printf("\n\t\t\t\t\tID: %s",s1.id);
        printf("\n\t\t\t\t\tName: %s",s1.name);
        printf("\n\t\t\t\t\tAddress: %s",s1.add);
        printf("\n\t\t\t\t\tParent's Name: %s",s1.pname);
        printf("\n\t\t\t\t\tBatch: %s",s1.Batch);
        printf("\n\t\t\t\t\tPhone No: %s",s1.phone_no);
    }
    else
    {
        printf("\n\n\t\t\t\t\tSORRY, RECORD NOT FOUND!!");
    }
    fclose(fp);
    printf("%d",i);
    return;
}
void del()
{
    int i,flag;
    int isFound = 0;
    char s_id[20];
    fp = fopen("data.txt","rb");
    if(fp==NULL)
    {
        printf("\n\t\t\t\t\tCannot Open File!!");
        return;
    }
    for(i=0;i<=19;i++)
    {
        s_id[i]='\0';
        s1.id[i]='\0';
    }
    printf("\t\t\t\t\tEnter enrollment no. to delete: ");
    scanf("%s",s_id);
    temp = fopen("temp.txt", "wb");
    i=0;
    while(fread(&s1, sizeof(s1), 1, fp) == 1)
    {
        i++;
        if(strcmp(s_id,s1.id) != 0)
        {
            fwrite(&s1, sizeof(s1), 1, temp);
        }
        else
        {
            printf("\n\t\t\t\t\tNo Such Record Found!!");
        }
    }
    fclose(fp);
    fclose(temp);
    remove("data.txt");
    rename("temp.txt","data.txt");
    printf("\n\t\t\t\t\tRecord Deleted Successfully!!\n");
    return;
}
void modify()
{
    char s_id[19];
    int isFound = 0;
    printf("\t\t\t\t\tEnter enrollment no. to Modify: ");
    scanf("%s",s_id);
    fp = fopen("data.txt","rb+");
    while(fread(&s1, sizeof(s1),1,fp) == 1)
    {
        if(strcmp(s_id, s1.id) == 0)
        {
            printf("\n\t\t\t\t\tID: ");
            scanf("%s",s1.id);
            printf("\t\t\t\t\tName: ");
            scanf("%s",s1.name);
            printf("\t\t\t\t\tAddress: ");
            scanf("%s",s1.add);
            printf("\t\t\t\t\tParent's name: ");
            scanf("%s",s1.pname);
            printf("\t\t\t\t\tBatch: ");
            scanf("%s",s1.Batch);
            printf("\t\t\t\t\tPhone Number: ");
            scanf("%s",s1.phone_no);
            fseek(fp,-sizeof(s1), SEEK_CUR);
            fwrite(&s1,sizeof(s1), 1, fp);
            isFound = 1;
            break;
        }
    }
    if(!isFound)
    {
        printf("\t\t\t\t\tNo Record Found");
    }
    else
    {
        printf("\t\t\t\t\tRecord modified\n");
    }
    fclose(fp);
    return;
}
void show()
{
    fp=fopen("data.txt","rb");
    if(fp==NULL)
    {
        gotoxy(5,7);
        printf("\t\t\t\t\tERROR!!");
    }
    gotoxy(35,1);
    printf("\t\t\t\t ----- STUDENT DETAILS ----- \n");
    gotoxy(18,3);
    printf("\n\nID\t\t NAME\t\t ADDRESS\t ParentsName\t BATCH\t\t CONTACT\n\n");
    gotoxy(18,6);
    while(fread(&s1,sizeof(s1),1,fp)==1)
    {
            printf("\n%-12s\t %-12s\t %-12s\t %-12s\t %-12s\t %-12s",s1.id,s1.name,s1.add,s1.pname,s1.Batch,s1.phone_no);
    }
    fclose(fp);
    getch();
}
