#include <stdio.h>
#include <stdlib.h>
#include<string.h>
FILE *mainFile,*binmainFile,*stud,*binstd,*books,*binbooks,*authers,*binauthers;
int bcount=0,stdcount=0;
int index;
char mainFileNamebin[20]="Main File.bin";
char mainFileNametxt[20]="Main File.txt";
char bookFileNamebin[20]="Book File.bin";
char bookFileNametxt[20]="Book File.txt";
char studentFileNametxt[20]="Student File.txt";
struct date
{
    int y,m,d;
};
struct date today,lastdate,tempdate;
struct Author
{
    char auth_name[21];
};
struct Book
{
    int isbn;
    char title[21];
    struct Author bauthor[21];
    int numofauth;
    char section[21];
    int copies;
    int counter;
};
struct Book allbook[201],SortedBook[201];
struct Student
{
    int id;
    char student_name[21];
};
struct stdborrow
{
    struct Student std;
    int numofbook;
    struct Book st_books[3];
    struct date stbr_date[3];
    struct date stre_date[3];
    struct date stpun_date;
    int punshid;
};
struct stdborrow student[201];
void close()
{
    if(bcount == 0)
        return ;
    binmainFile=fopen(mainFileNamebin,"wb");
    mainFile=fopen(mainFileNametxt,"w");
    binbooks=fopen(bookFileNamebin,"wb");
    books=fopen(bookFileNametxt,"w");
    stud=fopen(studentFileNametxt,"w");
    if(binmainFile==NULL || mainFile==NULL || binbooks==NULL || stud==NULL)
    {
        printf("Error");
        exit(EXIT_FAILURE);
    }
    int i;
    int j;
    for(i=0; i<stdcount; i++)
        fwrite(&student[i],sizeof(struct stdborrow),1,binmainFile);
    fclose(binmainFile);

    for(i=0; i<bcount; i++)
        fwrite(&allbook[i],sizeof(struct Book),1,binbooks);
    fclose(binbooks);

    for(i=0; i<stdcount; i++)
    {
        fprintf(stud,"Student ID : %d\n",student[i].std.id);
        fprintf(stud,"student name : %s\n",student[i].std.student_name);
        fprintf(stud,"___________________________________________________\n");
    }
    fclose(stud);
    for(i=0; i<stdcount; i++)
    {
        fprintf(mainFile,"Student ID :  %d\n",student[i].std.id);
        fprintf(mainFile,"student name :  %s\n",student[i].std.student_name);
        fprintf(mainFile,"Number Of Book :  %d\n",student[i].numofbook);
        for(j=0; j<student[i].numofbook; j++)
        {
            fprintf(mainFile,"Book %d :  \n",j+1);
            fprintf(mainFile,"ISBN is :  %d\n",student[i].st_books[j].isbn);
            fprintf(mainFile,"Title :  %s\n",student[i].st_books[j].title);
            fprintf(mainFile,"date of borrow :  %d/%d/%d\n",student[i].stbr_date[j].d,student[i].stbr_date[j].m,student[i].stbr_date[j].y);
            fprintf(mainFile,"the date of return :  %d/%d/%d\n",student[i].stre_date[j].d,student[i].stre_date[j].m,student[i].stre_date[j].y);
        }
        fprintf(mainFile,"___________________\n");
        if(student[i].punshid == 1)
            fprintf(mainFile,"the date of ending the punish :  %d/%d/%d\n",student[i].stpun_date.d,student[i].stpun_date.m,student[i].stpun_date.y);
        else
            fprintf(mainFile,"This Student is not punished \n");
            fprintf(mainFile,"___________________________________________________\n");
    }
    fclose(mainFile);
    for(i=0; i<bcount; i++)
    {
        fprintf(books,"ISBN :  %d\n",allbook[i].isbn);
        fprintf(books,"Title :  %s\n",allbook[i].title);
        fprintf(books,"Authors :  %d\n",allbook[i].numofauth);
        for(j=0; j<allbook[i].numofauth; j++)
        {
            fprintf(books,"%d- %s\n",j+1,allbook[i].bauthor[j].auth_name);
        }
        fprintf(books,"Section :  %s\n",allbook[i].section);
        fprintf(books,"Copies :  %d\n",allbook[i].copies);
        fprintf(books,"___________________________________________________\n");
    }
    fclose(books);
}
void GetData()
{
    binmainFile = fopen(mainFileNamebin,"rb");
    binbooks = fopen(bookFileNamebin,"rb");
    if(binbooks == NULL || binmainFile == NULL)
    {
        printf("Now Data Yet! Let's Add\n");
        getDate();
        fclose(binbooks);
        fclose(binmainFile);
        return ;
    }
    while(!feof(binmainFile))
    {
        fread(&student[stdcount],sizeof(struct stdborrow),1,binmainFile);
        stdcount ++;
    }
    stdcount --;
    while(!feof(binbooks))
    {
        fread(&allbook[bcount],sizeof(struct Book),1,binbooks);
        bcount++;
    }
    bcount--;
    check_date();
    fclose(binbooks);
    fclose(binmainFile);
}
int input()
{
    int result = 0;
    int numOfLast=0;
    int i=0;
    int myInput[20];
    int h;
    do
    {
        h=getchar();
        if(h==10 && i==0)
        {
            printf("Enter Only Numbers \t");
            fflush(stdin);
            continue ;
        }
        if(h == 10)
            break;
        if(h<'0' || h >'9')
        {
            printf("Enter Only Numbers \t");
            fflush(stdin);
            i=0;
            h=0;
            continue ;
        }
        h=h-48;
        myInput[i]=h;
        i++;
    }
    while(h!=-38);
    numOfLast=i;
    for (i = 0; i < numOfLast; i++)
    {
        result = 10 * result + myInput[i];
    }
    return result;
}
void read_char(char matrix[21])
{
    fflush(stdin);
    char ch;
    int n=0;
    do
    {
        ch=getchar();
        if ((ch=='\n' && n==0) || (ch == ' ' && n==0))
        {
            printf("Re-enter:Please enter the correct string input:\n");
            fflush(stdin);
            ch = '&';
            continue ;
        }
        if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z') || ch == ' ')
        {
            matrix[n]=ch;
            n++;
        }
        else if(ch!='\n')
        {
            printf("Enter Only Letter :  ");
            n=0;
            fflush(stdin);
        }
    }while(ch!='\n');
    matrix[n] = '\0';
}
void date_for_borrow_in_month()
{
    struct date temp;
    int h;
    printf("Enter the date (Month/year) : \n");

    do
    {
        h=input();
        if(h > 12 || h < 1)
        {
            printf("Wrong Month!, Month Must be between (1,12)... Retry !\n ");
            h = -1;
        }
    }
    while(h == -1);
    temp.m = h;
    fflush(stdin);
    do
    {
        h = input();
        if(h > 2050 || h < 2000)
        {
            printf("Wrong Year!, Year Must be between (2000,2050)... Retry! ");
            h = -1;
        }
    }
    while(h == -1);
    temp.y = h;
    tempdate = temp;
}
void getDate()
{
    struct date temp;
    int h;
    printf("Enter The date (day,Month,year) : \n");
    do
    {
        h=input();
        if(h > 30 || h < 1)
        {
            printf("Wrong Day!, Day Must be between (1,30)... Retry! ");
            h = -1;
        }
    }
    while(h == -1);
    temp.d = h;
    fflush(stdin);
    do
    {
        h=input();
        if(h > 12 || h < 1)
        {
            printf("Wrong Month!, Month Must be between (1,12)... Retry! ");
            h = -1;
        }
    }
    while(h == -1);
    temp.m = h;
    fflush(stdin);
    do
    {
        h = input();
        if(h > 2050 || h < 2000)
        {
            printf("Wrong Year!, Year Must be between (2000,2050)... Retry! ");
            h = -1;
        }
    }while(h == -1);
    temp.y = h;
    today = temp;
}
void newbook()
{
    int h,i,j,r;
    char name[20];
    printf("Enter The New Book Details.....\n");
    printf("Enter The International Stander Book Number:  ");
    h=input();
    r = search(2,h);
    if(r>=0)
    {
        printf("This Book Exist In the library , How many copies you want to add ?   ");
        fflush(stdin);
        h=input();
        allbook[r].copies+=h;
        return ;
    }
    allbook[bcount].isbn = h ;
    printf("The Title of Book:  ");
    fflush(stdin);
    char ch;
    int n=0,t=0;
    do
    {
            ch=getchar();
        if ((ch=='\n' && n==0) || (ch == ' ' && n==0))
        {
            printf("Re-enter:Please enter the correct string input:\n");
            fflush(stdin);
            ch='%';
            continue ;
        }
       allbook[bcount].title[n]=ch;
        n++;
    }while(ch!='\n');
    allbook[bcount].title[n-1]='\0';
    do
    {
        printf("Number Of Authors:  ");
        h=input();
        if(h==0)
        {
            printf("No Book Has No Author: Pleas Re-enter!\n ");
        }
    }while( h == 0 );
    allbook[bcount].numofauth = h;
    for(i = 0 ; i < h ; i++)
    {
        printf("Enter Author name :  ");
        fflush(stdin);
        read_char(allbook[bcount].bauthor[i].auth_name);
    }
    fflush(stdin);
    printf("The section of Book :  ");
    do
    {
           ch=getchar();
          if ((ch=='\n' && t==0) || (ch == ' ' && t==0))
        {
            printf("Re-enter:Please enter the correct string input:\n");
            fflush(stdin);
            ch='&';
            continue ;
        }
        allbook[bcount].section[t]=ch;
        t++;
    }while(ch!='\n');
    allbook[bcount].section[t-1]='\0';
    fflush(stdin);
    do
    {
        printf("The Number Of copies in the library :  ");
        h=input();
        if(h == 0)
        {
            printf("No Book Has No Copies : Pleas Re-enter!\n ");
        }
    }
    while( h == 0 );
    allbook[bcount].copies = h;
    printf("the Book  %d saved successfully ...\n\n", ++bcount );
}
void display_book(int o)
{
    int i,j,K;
    if(o==1) //  4
    {
        for(i=0; i<bcount; i++)
        {
            printf("ISBN :  %d\n",allbook[i].isbn);
            printf("Title :  %s\n",allbook[i].title);
            printf("The Author(s) : \n");
            for(j=0; j<allbook[i].numofauth; j++)
                printf("%d- %s\n",j+1,allbook[i].bauthor[j].auth_name);
            printf("Section :  %s\n",allbook[i].section);
            printf("Copies in Library :  %d\n",allbook[i].copies);
            if( i != bcount-1)
            {
            printf("______________________________\n");
            }

        }
    }
    else if(o==2) // 9
    {
        for(i=0; i<bcount; i++)
        {
            printf("ISBN :  %d\n",SortedBook[i].isbn);
            printf("Title :  %s\n",SortedBook[i].title);
            printf("The Authors :  \n");
            for(j=0; j<SortedBook[i].numofauth; j++)
                printf("%d- %s\n",j+1,SortedBook[i].bauthor[j].auth_name);
            printf("Section :  %s\n",SortedBook[i].section);
            printf("Copies in Library :  %d\n",SortedBook[i].copies);
            if( i != bcount-1)
            {
            printf("______________________________\n");
            }
        }
    }
}
void search_by_title()
{
    int i,j,n=0,k=0;
    char stitle[21];
    printf("Enter Title Of the Book :  ");
    fflush(stdin);
    gets(stitle);
    fflush(stdin);
    for(i=0; i<bcount; i++)
    {
        if(strcmp(stitle,allbook[i].title)==0)
        {
            k++;
            printf("ISBN :  %d\n",allbook[i].isbn);
            printf("Title :  %s\n",allbook[i].title);
            printf("The Authors :\n");
            for(j=0; j<allbook[i].numofauth; j++)
                printf("%d- %s\n",j+1,allbook[i].bauthor[j].auth_name);
            printf("Section :  %s\n",allbook[i].section);
            printf("Copies in Library :  %d\n",allbook[i].copies);
        }
    }
    if(k==0)
        printf("there is no such a book !\n");

}
void display_book_by_author()
{
    int l=0,i,j,k=1;
    char name[21];
    printf("Enter the name of the author :  ");
    read_char(name);
    fflush(stdin);
    printf("The book(s) are : \n");
    for(i=0; i<bcount; i++)
    {
        for(j=0; j<allbook[i].numofauth; j++)
        {
            if(  strcmp(allbook[i].bauthor[j].auth_name,name)==0 )
            {
                l=1;
                printf("%d- %s\n",k,allbook[i].title);
                k++;
            }
        }
    }
    if (l==0)
        printf("the writer %s has no book in the library \n",name);
}
void sortByMostCounters()
{
    struct Book temp;
    int i;
    for(i=0; i<bcount; i++)
    {
        SortedBook[i]=allbook[i];
    }
    int h=0;
    do
    {
        h=0;
        for(i=0; i<bcount; i++)
        {
            if(SortedBook[i].counter < SortedBook[i+1].counter)
            {
                temp=SortedBook[i];
                SortedBook[i]=SortedBook[i+1];
                SortedBook[i+1]=temp;
                h=1;
            }
        }
    }while(h==1);
    display_book(2);
}
struct stdborrow cheak_pun(struct stdborrow temp)
{
    int i,j=0,k,r=0;
    struct date dtemp[3];
    struct date bigdate;

    if(datecmp(temp.stpun_date,today))
    {
        temp.punshid = 0;
    }
    for(i=0; i<temp.numofbook ; i++)
    {
        if(temp.stre_date[i].d==today.d && temp.stre_date[i].m==today.m && temp.stre_date[i].y==today.y )
            continue ;
        if(datecmp(temp.stre_date[i],today))
        {
            printf("today is %d/%d/%d \n",today.d,today.m,today.y);
            printf("He Should Return the book (%s) in %d/%d/%d\n",temp.st_books[i].title,temp.stre_date[i].d,temp.stre_date[i].m,temp.stre_date[i].y);
            dtemp[j].d = today.d;
            r=1;
            if(today.m == 12)
            {
                dtemp[j].m = 1;
                dtemp[j].y = today.y + 1;
            }
            else
            {
                dtemp[j].m = today.m + 1;
                dtemp[j].y = today.y ;
            }
            j++;
        }
    }
    if(r)
    {
        bigdate=dtemp[0];
        for(k=0; k<j; k++)
        {
            if(k==j-1)
                break;
            if(datecmp(dtemp[k],dtemp[k+1]))
            {
                bigdate=dtemp[k+1];
            }
        }
        printf("This Student Have To be Punished  to %d/%d/%d \n",bigdate.d,bigdate.m,bigdate.y);
        temp.punshid = 1;
        temp.stpun_date=bigdate;
    }
    return temp;
}
void search_date()
{
    int i,j;
    struct date temp;
    date_for_borrow_in_month();
    for(i=0; i<stdcount; i++)
    {
        if((tempdate.m== student[i].stbr_date[student[i].numofbook].m)&&(tempdate.y==student[i].stbr_date[student[i].numofbook].y ));
        for(j=0; j<student[i].numofbook; j++)
            printf("the Title of book : %s\n",student[i].st_books[j].title);
    }
}
struct date makedates(int numofbook)
{
    struct date temp;
    int h,re;
    printf("Enter The returned (day,Month,year): \n");
    do{
    do
    {
        h=input();
        if(h > 30 || h < 1)
        {
            printf("Wrong Day!, Day Must be between 1~30, Retry! ");
            h = -1;
        }
    }
    while(h == -1);
    temp.d = h;
    fflush(stdin);
    do
    {
        h=input();
        if(h > 12 || h < 1)
        {
            printf("Wrong Month!, Month Must be between 1~12, Retry! ");
            h = -1;
        }
    }
    while(h == -1);
    temp.m = h;
    fflush(stdin);
    do
    {
        h = input();
        if(h > 2030 || h < 2000)
        {
            printf("Wrong Year!, Year Must be between 2000~2030, Retry! ");
            h = -1;
        }
    }while(h == -1);
    temp.y = h;
       re=datecmp(temp,today);
      if(re == 1)
      {
          printf("you can not enter day previous to today . plz re_enter the return date \n");
      }
    }while(re == 1);
    return temp ;
}
int datecmp(struct date temp1,struct date temp2)
{
    if(temp1.y<temp2.y)
    {
        return 1;
    }
    else if (temp1.y>temp2.y)
    {
        return 0;
    }
    else
    {
        if(temp1.m<temp2.m)
        {
            return 1;
        }
        else if (temp1.m>temp2.m)
        {
            return 0;
        }
        else
        {
            if(temp1.d<temp2.d)
            {
                return 1;
            }
            else if (temp1.d>temp2.d)
            {
                return 0;
            }
            else
            {
                return 1 ;
            }
        }
    }
}
void last_date()
{
    lastdate.d = student[stdcount-1].stbr_date[student[stdcount-1].numofbook -1].d ;
    lastdate.m = student[stdcount-1].stbr_date[student[stdcount-1].numofbook -1].m ;
    lastdate.y = student[stdcount-1].stbr_date[student[stdcount-1].numofbook -1].y ;
}
void check_date()
{
    int e ;
    last_date();
    printf("Enter Today's Date ..\n");
    do
    {
        printf("last date is %d/%d/%d/\n",lastdate.d,lastdate.m,lastdate.y);
        getDate();
        e = datecmp ( lastdate, today ) ;
        if ( e == 0 )
            printf(" you can not enter previous date to last one ...\nplease enter the date again \n");
    }
    while( e != 1);
}
int search(int o,int num)
{
    int i;
    if(o == 1)
    {
        for( i = 0; i < stdcount ; i++ )
        {
            if( num == student[i].std.id )
            {
                return i;
            }
        }
        return -1;
    }
    else if (o == 2)
    {
        for(i = 0; i < bcount ; i++)
        {
            if(num == allbook[i].isbn)
            {
                return i;
            }
        }
        return -1;
    }
}
void exist(int ix)
{
    int i,r,h;
    if(student[ix].numofbook == 3)
    {
        printf("This Student Have 3 Book Already so he can not borrow one ..\n");
        return ;
    }
        printf("Enter ISBN of The Book :  ");
    do{
        h=input();
    }while(h<=0);
    r = search(2,h);
    if(allbook[r].copies == 0)
    {
        printf("There Is no more copies of this book , sorry !\n");
        return ;
    }
    allbook[r].copies--;
    student[ix].st_books[student[ix].numofbook].isbn=h;
    student[ix].stbr_date[student[ix].numofbook]=today;
    student[ix].stre_date[student[ix].numofbook] = makedates(student[ix].numofbook);
    strcpy(student[ix].st_books[student[ix].numofbook].title,allbook[r].title);
    student[ix].numofbook+=1;
    allbook[r].counter ++ ;
}
void newborrow ()
{
    char name[20];
    int r,h;
    printf("Student Id: ");
    h = input();
    r = search(1,h);
    if(r>=0)
    {
        printf("this student is already borrowed a book ! \n");
        student[r] = cheak_pun(student[r]);
        if(student[r].punshid == 1)
        {
            if ( datecmp(student[r].stpun_date, today))
            {
                student[r].punshid == 0 ;
            }
            if (student[r].punshid == 1){
                printf("this student is punched \n");
                return ;}
        }
        exist(r);
        return;
    }
    student[stdcount].std.id = h;
    printf("Student Name :  ");
    read_char(student[stdcount].std.student_name);
    fflush(stdin);
    do
    {
        printf("Enter the ISBN of book :  ");
        h = input();
        r = search(2,h);
        if ( r == -1 )
          {
             printf("there is no book have this number \n");
          }
    }while(r==-1);
    if(allbook[r].copies == 0)
    {
        printf("No Copies Available Now , Please Come Back Later \n");
        return ;
    }
    strcpy(student[stdcount].st_books[student[stdcount].numofbook].title,allbook[r].title);
    student[stdcount].st_books[student[stdcount].numofbook].isbn=h;
    student[stdcount].punshid=0;
    student[stdcount].stbr_date[student[stdcount].numofbook]=today;
    allbook[r].copies--;
    allbook[r].counter++;
    student[stdcount].stre_date[student[stdcount].numofbook] = makedates(student[stdcount].numofbook);
    student[stdcount].numofbook+=1;
    stdcount++;
}
void deletstd(int h)
{
    int i;
    for(i=h; i<stdcount; i++)
    {
        student[i]=student[i+1];
    }
    stdcount--;
}
void deletbook(struct Book a[],int numofbook,int h)
{
    int i;
    for(i=h; i<numofbook; i++)
    {
        a[i]=a[i+1];
    }
}
void deletdate(struct  date a[],int numofbook,int h)
{
    int i;
    for(i=h; i<numofbook; i++)
    {
        a[i]=a[i+1];
    }
}
void reback()
{
    int r,h,i,x,k;
    printf("Enter the number of the student who wants to return a book :  ");
    do
    {
        h = input();
        r=search(1,h);
        if(r==-1)
            printf("The student not found,Please enter the correct university number \n");
    }
    while(r==-1);
    printf("this student has %d book(s) : \n",student[r].numofbook);
     student[r] = cheak_pun(student[r]);
    for(i=0; i<student[r].numofbook; i++)
    {
        printf("(%d)- %s\n",i+1,student[r].st_books[i].title);
    }
    printf("Enter the number of the book which you want return to the library \t");
    do
    {
        x=input();
        if(x>student[r].numofbook)
        {
            printf("Please Chose from list \t");
        }
    }while(x>student[r].numofbook);
    k = search(2,student[r].st_books[x-1].isbn);
    allbook[k].copies++;
    allbook[k].counter++;
    student[r].numofbook--;
    if(student[r].numofbook==0 && student[r].punshid == 0)
    {
        deletstd(r);
        return ;
    }
    deletbook(student[r].st_books,student[r].numofbook,x);
    deletdate (student[r].stbr_date,student[r].numofbook,x);
    deletdate (student[r].stre_date,student[r].numofbook,x);
}
void show_book_student()
{
    int k,i,j;
    printf("Enter the number of the student :  ");
    fflush(stdin);
    k=input();
    fflush(stdin);
    for(i=0; i<stdcount; i++)
    {
        if(k==student[i].std.id)
        {
            printf("Student %s Has %d Book(s) , and it's :\n",student[i].std.student_name,student[i].numofbook);
            for(j=0; j<student[i].numofbook; j++)
                printf("%d- %s\n",j+1,student[i].st_books[j].title);
            return ;
        }
    }
    printf("there is no such a student !\n");
}
void late_book()
{
    int i, j, k=1 ;
    for( i=0 ; i<stdcount ; i++ )
    {
        for( j=0 ; j<student[i].numofbook ; j++ )
        {
            if ((datecmp(student[i].stre_date[j],today)) == 1 )
            {
                printf("the informations of book are (ISBN,title,return date) :  %d-%s  : %d/%d/%d\n",student[i].st_books[j].isbn,student[i].st_books[j].title,student[i].stre_date[j].d,student[i].stre_date[j].m,student[i].stre_date[j].y);
                k++;
            }
        }
    }
    if ( k ==1 )
        printf(" there is no late book \n");
}
int main()
{
    printf("\n\t\t\t\t\tITE collage\n\t\t\t\t\tMs.Manar\n\t\t\t\t\tMohammad baker Kazmoz & Mohammad Bishr Alkhoja\n\t\t\t\t\tWelcome In Our Project ..\n");
    int x;
    GetData();
    do
    {
        printf("__________________________________________________________________________________________________________________________\n");
        printf("                               * Chose Options: \n");
        printf("                                   press (1) for add new book in library:\n");
        printf("                                   press (2) for A New Borrow:\n");
        printf("                                   press (3) for Return A Book:\n");
        printf("                                   press (4) for display all book in library:\n");
        printf("                                   press (5) Search Book By Title:\n");
        printf("                                   press (6) for display all book By Author:\n");
        printf("                                   press (7) for display all book With Student:\n");
        printf("                                   press (8) for display all Borrow in a month\n");
        printf("                                   press (9) for display all book Sorted By Most Wanted:\n");
        printf("                                   press (10) for display all book That Not returned:\n");
        printf("                                   press (0)  for exit\n");
        printf("                                    your choice is...  ");
        x = input();
        switch(x)
        {

        case 1:
            newbook();
            break;
        case 2:
            if(bcount==0)
            {
                printf("There is no Book in the Library! Please add first!\n");
                continue;
            }
            newborrow();
            break;
        case 3:
            if(bcount==0)
            {
                printf("There is no Book in the Library! Please add first!\n");
                continue;
            }
            if(stdcount == 0)
            {
                printf("there  is no student !\n");
                continue;
            }
            reback();
            break;
        case 4:
            if(bcount==0)
            {
                printf("There is no Book in the Library! Please add first!\n");
                continue;
            }
            display_book(1);
            break;
        case 5:
            if(bcount==0)
            {
                printf("There is no Book in the Library! Please add first!\n");
                continue;
            }
            search_by_title();
            break;
        case 6:
            if(bcount==0)
            {
                printf("There is no Book in the Library! Please add first!\n");
                continue;
            }
            display_book_by_author();
            break;
        case 7:
            if(bcount==0)
            {
                printf("There is no Book in the Library! Please add first!\n");
                continue;
            }
                        if(stdcount == 0)
            {
                printf("there  is no student !\n");
                continue;
            }
            show_book_student();
            break;
        case 8:
            if(bcount==0)
            {
                printf("There is no Book in the Library! Please add first!\n");
                continue;
            }
            search_date();
            break;
        case 9:
            if(bcount==0)
            {
                printf("There is no Book in the Library! Please add first!\n");
                continue;
            }
            sortByMostCounters();
            break;
        case 10:
            if(bcount==0)
            {
                printf("There is no Book in the Library! Please add first!\n");
                continue;
            }
            late_book();
            break;
        case 0 :
            printf("\n\n\n\t\t\t\t^^^^^  Thank You for Using our Program  ^^^^^\n\n\n\n\n\n\n\n");
            printf("__________________________________________________________________________________________________________________________\n");
            printf("\t\t\t\t\t__________________________________________\n");
            close();
            break;
        default:
            printf("wrong choice ! \n");
        }
    }while(x!=0);
    return 0;
}
