#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct node
{
  char bid[20];
  char bname[20];
  char author[20];
  int status;
  struct node *next;
}*start=NULL;

struct member
{
    char mid[20];
    char mname[20];
    char dept[20];
    struct member *next;
}*first=NULL;

int flag=1;

void create()
{
  int n,temp;
  printf("Enter the no of books to be added\n");
  scanf("%d",&n);
  if(n<0)
  {
    flag=1;
  }
  temp=n;
  while(n>0)
  {
     struct node *new_node,*cur;
     new_node=(struct node*)malloc(sizeof(struct node));
     printf("Enter book name,book id and author \n");
     scanf("%s%s%s",new_node->bname,new_node->bid,new_node->author);
     new_node->status=1;
     new_node->next=NULL;
     if(start==NULL)
     {
         start=new_node;
      }
      else
      {
         cur=start;
         while(cur->next!=NULL)
         {
             cur=cur->next;
         }
        cur->next=new_node;
      }
      n--;
      flag=0;
    }
    if(flag==0)
      printf("%d books are added successfully......\n",temp);
    return;
}

void display()
{
   if(flag==1)
   {
       printf("No books available in library\n");
   }
   else
   {

       struct node *new_node;
       printf("---BOOK ID---\t---BOOK NAME---\t----AUTHOR---\t----STATUS---\n");
       new_node=start;
       while(new_node!=NULL)
       {
           printf("%s\t\t%s\t\t%s\t\t",new_node->bid,new_node->bname,new_node->author);
           if(new_node->status==1)
               printf("available\n");
            else
                printf("Issued\n");
            new_node=new_node->next;
        }
   }
}


void addmember()
{
  char id[20];
  char name[20],dep[20];
  int n,ans;
  printf("Enter the number of members to be added\n");
  scanf("%d",&n);
  ans=n;
  if(n==0)
    {
        return;
    }
  while(n>0)
  {
  printf("Enter member id,name and department\n");
  scanf("%s%s%s",id,name,dep);
  struct member *temp=NULL;
  temp=first;
  h:
  while(temp!=NULL)
  {
      if(strcmp(temp->mid,id)==0)
      {
          printf("Entered ID is already taken...Enter new ID\n");
          scanf("%s",id);
          goto h;
      }
      temp=temp->next;
  }
  struct member *cur;
  cur=(struct member*)malloc(sizeof(struct member));
  cur->next=NULL;
  if(first==NULL)
  {
    strcpy(cur->mid,id);
    strcpy(cur->mname,name);
    strcpy(cur->dept,dep);
    first=cur;
  }
  else
  {
      temp=first;
      while(temp->next!=NULL)
      {
        temp=temp->next;
      }
     strcpy(cur->mid,id);
     strcpy(cur->mname,name);
     strcpy(cur->dept,dep);

     temp->next=cur;
  }
  n--;
  }
  printf("%d member added successfull...\n\n",ans);
}

void issue()
{
   char temp[20];
   char id[10];
   int tag=0;
   struct node *cur1;
   cur1=start;
   struct member *cur;
   cur=first;
   if(cur1==NULL)
   {
       printf("No books are available in library\n\n");
       return;
   }
   printf("Enter member id\n");
   scanf("%s",id);
   while(cur!=NULL)
   {
       if(strcmp(cur->mid,id)==0)
       {
           tag=1;
       }
       cur=cur->next;
   }
   if(tag==0)
    {
      printf("not a member of library\n\n");
      return ;
    }
   printf("Enter the name of book to be issued\n");
   scanf("%s",temp);
     {
        while(cur1!=NULL)
        {
            if(strcmp(cur1->bname,temp)==0)
            {
                printf("book found\n");
                if(cur1->status==1)
                {
                   printf("available for issue\n");
                   cur1->status=0;
                   printf("book is issued\n");
                   printf("%s is issued by member whose id is %s\n\n",temp,id);
                   return;
                }
                else
                {
                    printf("Already issued\n\n");
                     return;
                }
            }
            cur1=cur1->next;
        }
        printf("No such book available in library\\n\n");
        return;
    }

}

void deletemember()
{
    char c[20];
    struct member *temp,*prev;
    temp=first;
    printf("Enter the Member Id to be deleted\n");
    scanf("%s",c);
    printf("Member Deleted\n");

    if (temp!=NULL && strcmp(temp->mid,c)==0)
    {
        first=temp->next;
        free(temp);
        return;
    }

    while (temp!=NULL && strcmp(temp->mid,c)!=0)
    {
        prev=temp;
        temp=temp->next;
    }
    if (temp==NULL) return;

    prev->next=temp->next;

    free(temp);
}

void idisplay()
{
    struct member *cur;
    cur=first;
    printf("----MEMBER ID---\t---MEMBER NAME-----\tDEPARTMENT-----\n");
    while(cur!=NULL)
    {
        printf("%s\t\t\t%s\t\t\t%s\n",cur->mid,cur->mname,cur->dept);
        cur=cur->next;
    }
}

int returnbook()
{
    char bk[10];
    int a,fine;
    struct node *temp1;
    temp1=start;
    if(temp1==NULL)
    {
        printf("No books in library...\n\n");
        return;
    }
    printf("enter the name of book to be returned\n");
    scanf("%s",bk);
    printf("Enter the number of days from issue to return");
    scanf("%d",&a);
    while(temp1!=NULL)
    {
        if(strcmp(temp1->bname,bk)==0)
        {
            if(temp1->status==0)
           {
            temp1->status=1;
            fine=(a-30)*2;
            if(fine>0)
                printf("book is returned with a fine of Rs %d\n\n",fine);
            else
                printf("book is returned with no fine\n\n");

             return 0;
          }
          else
            {
               printf("Book is not yet issued\n\n");
               return;
            }
        }
        temp1=temp1->next;
    }
    printf("book does not belong to library\n\n");
}

void main()
{
   int ch;
   printf("\t\t\t\t\tLIBRARY MANAGEMENT SYSTEM\n\n");
   printf("1.Add Book\n2.Issue Book\n3.Return Books(with fine if any)\n4.View Book List\n5.Add Members\n6.Delete Member\n7.View Member List\n8.Close Application\n\n");
   do
   {
   printf("Enter your choice\n");
   scanf("%d",&ch);
   switch(ch)
    {
        case 1 : create();
                     break;
        case 2 : issue();
                     break;
        case 3 : returnbook();
                     break;
        case 4 : display();
                     break;
        case 5 : addmember();
                     break;
        case 6 : deletemember();
                     break;
        case 7 : idisplay();
                  break;
        case 8 : printf("THANK YOU\n");
                     return;
        default : printf("Invalid choice\n");
                   break;
   }
   }while(ch<=8);
}
