#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>



#define TOTAL_CONTACTS 100
#define fnameSize 31
#define lnameSize 31
#define telepSize 15
#define cellpSize 15


struct contact{
	char fname[fnameSize];
	char lname[lnameSize];
	char telep[telepSize];
	char cellp[cellpSize];
};

struct contact_node{
	char fname[fnameSize];
	char lname[lnameSize];
	char telep[telepSize];
	char cellp[cellpSize];
	struct contact_node *_next;
	struct contact_node *_next_fname; 
	struct contact_node *_next_lname; 
	struct contact_node *_next_cellp; 
	struct contact_node *_next_telep; 
};




struct contact_node *head=NULL;
struct contact_node *fname_head=NULL;
struct contact_node *lname_head=NULL;
struct contact_node *cellp_head=NULL;
struct contact_node *telep_head=NULL;
struct contact_node *temp=NULL;
struct contact_node *ptr=NULL;
struct contact_node *front=NULL,*rear=NULL;
struct contact_node *prev=NULL;
void clrscr(void);
void gotoxy(int x, int y);
void insert(void);
void delet(void);
void edit(void);
void search(void);
void searchf(void);
void searchl(void);
void searchp(void);
void searchc(void);
void list(void);
void list2(int c);
void sort(void);
void sortf(void);
void sortl(void);
void sortp(void);
void sortc(void);
void help(void);
void display();
int check_user(struct contact c);
void add_node(struct contact c);
size_t get_input(char* dst,size_t max_size);

void update_node_fname(struct contact_node **new_node,struct contact_node **head);
void update_node_lname(struct contact_node **new_node,struct contact_node **head);
void update_node_cellp(struct contact_node **new_node,struct contact_node **head);
void update_node_telep(struct contact_node **new_node,struct contact_node **head);
void delete_node(struct contact_node **prev,struct contact_node **cur,char* dfname_string,char* dlname_string);
void delete_fname(char * fname,char * lname);
void delete_lname(char * fname,char * lname);
void delete_telep(char * fname,char * lname);
void delete_cellp(char * fname,char * lname);
int last=0;
int main()
{

	int count=1;
	char n;
	while(count) {
	clrscr();						
	printf("\n|Phone Book12<::>Home|\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("Welcome to PHONE BOOK2022!\nYou have inserted ( %d ) contacts.\n\n",last);
	printf("\t[1] |--> Insert\n");
	printf("\t[2] |--> Delete\n");
	printf("\t[3] |--> Edit\n");
	printf("\t[4] |--> Search\n");
	printf("\t[5] |--> Show All\n");
	printf("\t[6] |--> Sort\n");
	printf("\t[7] |--> Help\n");
	printf("\t[8] |--> Exit\n");
	printf("\n\tPlease Enter Your Choice (1-8): ");
	n = getc(stdin);
	getc(stdin);
	 switch(n) {
		  case '1':
		  insert();
		  break;
		  case '2':
		  delet();
		  break;
		  case '3':
		  edit();
		  break;
		  case '4':
		  search();
		  break;
		  case '5':
		  list();
		  break;
		  case '6':
		  sort();
		  break;
		  case '7':
		  help();
		  break;
		  case '8':
		  
		  exit(1);
		  break;
		  default:
		  printf("\nThere is no item with symbol \"%c\".Please enter a number between 1-8!\nPress any key to continue...",n);
		  getc(stdin);
	      getc(stdin);
		  break;
	  }//End of swicth
	}
	return 0;
}//End of main function!



int check_user(struct contact c)
{
	while(temp!=NULL)
		{
			
			 if (strcmp (c.fname , temp->fname) == 0 && strcmp (c.lname, temp->lname) == 0
			  && strcmp (c.telep, temp->telep) == 0  && strcmp (c.cellp, temp->cellp) == 0) 
			 {	
			 	
				return 1;			
			 }
			
		temp=temp->_next;	 
			
		}
		
	return 0;
}



size_t get_input(char* dst,size_t max_len)
{
	size_t len=max_len;
	size_t len_size=0;
	char* input=NULL;
	input=(char*) malloc(len*sizeof(char));
	
	len_size=getline(&input,&len,stdin);
	if(input[len_size -1]=='\n')
	{
		input[len_size -1 ] ='\0';
		len_size--;
	}
	if(len_size>= max_len)
	{
		input[max_len-1]='\0';
	}
	strcpy(dst,input);
	free(input);
}
	
void display()
{
        struct contact_node *ptr;
        if(head==NULL)
        {
                printf("List is empty:");
                return;
        }
        else
        {
                ptr=head;
                printf("\nThe List elements are:\n");
                while(ptr!=NULL)
                {
                
                        printf("%s\n",ptr->fname );
                        printf("%s\n",ptr->lname );
                        printf("%s\n",ptr->telep );
                        printf("%s\n",ptr->cellp );
                        ptr=ptr->_next ;
                        printf("%s\n","-----------");
                }
        }
        
        
        
        if(fname_head==NULL)
        {
                printf("List is empty:");
                return;
        }
        else
        {
                ptr=fname_head;
                printf("\nThe List elements are:\n");
                while(ptr!=NULL)
                {
                
                        printf("%s\n",ptr->fname );
                        printf("%s\n",ptr->lname );
                        printf("%s\n",ptr->telep );
                        printf("%s\n",ptr->cellp );
                        ptr=ptr->_next_fname ;
                        printf("%s\n","-----------");
                }
        }
        free(ptr);
}

void insert(void)
{
	
	
	char ans='y';
	char string[31];
	size_t len=0;
	size_t len_size=0;	
	int can_add=0;
	struct contact c;
	clrscr();
    printf("\nPhone Book12<::>Insert Contacts");
    printf("\n--------------------------------------------------------------------------------");

	char first_string [fnameSize] ;
	char last_string [lnameSize];
	
	
	
	while(ans=='y'){
		if(last == TOTAL_CONTACTS)
 			last = 0;
		else{
		
			
			
			
			printf("\n\nData of Contact %2.2d{\n",last+1);
			
			printf("\n\t  1-F.Name: ");
			len_size=get_input(c.fname,fnameSize);

			printf("\t  2-L.Name: ");
			len_size = get_input(c.lname,lnameSize);
			
			printf("\t  3-Tele.P: ");
			len_size = get_input(c.telep,telepSize);
			
			printf("\t  4-Cell.P: ");
			len_size = get_input(c.cellp,cellpSize);


			while(check_user(c)==1)
			{
			
			printf("\n\ncontact already in the phonebook %2.2d{\n",last+1);
			printf("\n\t  1-F.Name: ");
			len_size = get_input(c.fname,fnameSize);
			
			printf("\t  2-L.Name: ");
			len_size = get_input(c.lname,lnameSize);
			
			printf("\t  3-Tele.P: ");
			len_size = get_input(c.telep,telepSize);
			
			printf("\t  4-Cell.P: ");
			len_size = get_input(c.cellp,cellpSize);
			
			}
			add_node(c);	
			
			
			
			
	    		
			printf("\n|-->Data Recorded!}");
			printf("\n\t\t\tNext Contact?(y/n) Answer:");
		    ans = getc(stdin);
			getc(stdin);
		    last++;
			}
	}
	sort();
	printf("\n\nYou have inserted ( %d ) contact!\nPress a key to return main page & continue program|-->",last);
	getc(stdin);
	
	
	
	
	
	
	
	
	
}
void add_node(struct contact c)
{


			

			if (last==0)
			{
			 struct contact_node *temp=(struct contact_node *)malloc(sizeof(struct contact_node));
			 strncpy(temp->fname,c.fname,sizeof(temp->fname)-1);
			 strncpy(temp->lname,c.lname,sizeof(temp->lname)-1);
			 strncpy(temp->telep,c.telep,sizeof(temp->telep)-1);
			 strncpy(temp->cellp,c.cellp,sizeof(temp->cellp)-1);
			 temp->_next=NULL;
			 temp->_next_fname=NULL;
			 head=temp;
			 fname_head=temp;
			 lname_head=temp;
			 cellp_head=temp;
			 telep_head=temp;
			
			}
			else
			{
			
			
			 struct contact_node *temp1 = (struct contact_node *) malloc(sizeof(struct contact_node));
			
			 strncpy(temp->fname,c.fname,sizeof(temp->fname)-1);
			 strncpy(temp->lname,c.lname,sizeof(temp->lname)-1);
			 strncpy(temp->telep,c.telep,sizeof(temp->telep)-1);
			 strncpy(temp->cellp,c.cellp,sizeof(temp->cellp)-1);
			 update_node_fname(&temp,&fname_head);
			 update_node_lname(&temp,&lname_head);
			 update_node_telep(&temp,&telep_head);
			 update_node_cellp(&temp,&cellp_head);
			 
			  
			 temp->_next=NULL;
			 ptr=head;
               	 while(ptr->_next !=NULL)
                	 {
                       	 ptr=ptr->_next ;
                	 }
               	 ptr->_next =temp;
               	
			
			
			}
			
			
			

//free(temp);



}
void update_node_fname(struct contact_node **new_node,struct contact_node **head)
{


char string[31];
char new_string[31];
strncpy(string,(*head)->fname,sizeof(string)-1);
strncpy(new_string,(*new_node)->fname,sizeof(new_string)-1);

if (head==NULL||strcmp((*new_node)->fname,(*head)->fname)<0)
{
(*new_node)->_next_fname=*head;
*head=*new_node;

}

else
{
rear=*head;
front=rear->_next_fname;
while(front!=NULL&&strcmp((*new_node)->fname,front->fname)>0)
{
rear=front;
front=front->_next_fname;
}
(*new_node)->_next_fname=front;
rear->_next_fname=(*new_node);

}

}
void delet(void)
{
	
	char dfname_string[20],dlname_string[20];
	char input[100];
	size_t len=0;
	size_t len_size=0;
	register int i=0,j,find=0;
	char ch;
	clrscr();
	
    printf("\nPhone Book12<::>Delete Contacts");
    printf("\n--------------------------------------------------------------------------------");
	printf ("\n::Enter data of the contact that you want delete it,please:");
	printf("\n\n  ::Enter first name: ");
	len_size = get_input(input,fnameSize);
	strncpy(dfname_string,input,sizeof(dfname_string)-1);
	
	printf("\n  ::Enter last name: ");
	len_size = get_input(input,lnameSize);
	strncpy(dlname_string,input,sizeof(dlname_string)-1);
	temp=head;
	prev =temp;
	
	if (strcmp (dfname_string, head->fname) == 0 && strcmp (dlname_string, head->lname) == 0 )
	{
		printf("\nContact was found! Details:");
		printf("\n\nCantact %2.2d{",i+1);
		printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",head->fname,head->lname,head->telep,head->cellp);
		printf("\n\nAre you sure you want to delete this contact?(y/n)");
		ch = getc(stdin);
		getc(stdin);
		if(ch == 'y')
		{
		delete_node(&prev,&temp,dfname_string,dlname_string);
		printf("\t\t\n<<Target contact was successfully deleted from list!>>");
		last--;
		return;
		}
	}
	
	while(temp!=NULL)
	{
		 if (strcmp (dfname_string, temp->fname) == 0 && strcmp (dlname_string, temp->lname) == 0 )
		 {
		 
			printf("\nContact was found! Details:");
			printf("\n\nCantact %2.2d{",i+1);
			printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",temp->fname,temp->lname,temp->telep,temp->cellp);
			printf("\n\nAre you sure you want to delete this contact?(y/n)");
			ch = getc(stdin);
			getc(stdin);
			if(ch == 'y')
			{
		 	delete_node(&prev,&temp,dfname_string,dlname_string);
		 	find=1;
		 	last--;
		 	break;	
			}
		
		}
		prev=temp;
		temp=temp->_next;	
		i++;
	}	
	if (find==0)
		printf("\t\t\n<<This contact does not exist in this list or program can not delete it.>>");
	else
		printf("\t\t\n<<Target contact was successfully deleted from list!>>");
	printf("\n\n\nPress a key to return main page & continue program|-->");
	getc(stdin);
	//free(input);
}
void delete_node(struct contact_node **prev,struct contact_node **cur,char* dfname_string,char* dlname_string)
{
	if(*prev==*cur)
	{
	
		*cur=head;
		head=head->_next;
		delete_fname(dfname_string,dlname_string);
		delete_lname(dfname_string,dlname_string);
		delete_telep(dfname_string,dlname_string);
		delete_cellp(dfname_string,dlname_string);
	//	free(*cur);
	
	}
	else
	{
	
		  	(*prev)->_next=(*cur)->_next;
		  	delete_fname(dfname_string,dlname_string);
			delete_lname(dfname_string,dlname_string);
			delete_telep(dfname_string,dlname_string);
			delete_cellp(dfname_string,dlname_string);
		 	//free (*cur);
	}



}
void delete_fname(char * fname,char * lname)
{
temp=fname_head;
prev=temp;
if (strcmp (fname, temp->fname) == 0 && strcmp (lname, temp->lname) == 0 )
{
	fname_head=fname_head->_next_fname;
	return ;
}
while(temp!=NULL)
{
if (strcmp (fname, temp->fname) == 0 && strcmp (lname, temp->lname) == 0 )
{
	prev->_next_fname=temp->_next_fname;

}
prev=temp;
temp=temp->_next_fname;

}




}
void edit()
{
	
	char input[31];
	char dfname[fnameSize];
	char dlname[lnameSize];
	size_t len=0;
	size_t len_size=0;
	register int i=0,j,find=0;
	struct contact c;
	char ch;
	temp=head;
	struct contact_node *prev=temp;
	clrscr();	
    printf("\nPhone Book12<::>Edit Contacts");
    printf("\n--------------------------------------------------------------------------------");
	printf ("\n::Enter data of the contact that you want edit it,please:");
	
	printf("\n\n  ::Enter first name: ");
	len_size = get_input(dfname,fnameSize);
	printf("\n  ::Enter last name: ");
	len_size = get_input(dlname,lnameSize);



	while(temp!=NULL)
	{
	 if (strcmp (dfname, temp->fname) == 0 && strcmp (dlname, temp->lname) == 0 ) {
	 	printf("\nfound! Details:");
		printf("\n\nContact %2.2d{",i+1);
		printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",temp->fname,temp->lname,temp->telep,temp->cellp);
		printf("\n\nDo you want edit it?(y/n) ");
		ch = getc(stdin);
		getc(stdin);
		if(ch=='y'){
			printf("\n::Enter NEW data for this contact...");
			printf("\n >|Enter new first name: ");	
		
			
			len_size=get_input(dfname,fnameSize);
			strncpy(c.fname,dfname,sizeof(c.fname)-1);
			
			
			printf(" >|Enter new last name: ");
			len_size=get_input(dlname,lnameSize);
			strncpy(c.lname,dlname,sizeof(c.lname)-1);
			
			printf(" >|Enter new telephone number: ");
			len_size=get_input(input,telepSize);
			strncpy(c.telep,input,sizeof(c.telep)-1);

			printf(" >|Enter new cellphone number: ");
			len_size=get_input(input,cellpSize);
			strncpy(c.cellp,input,sizeof(c.cellp)-1);
			
			delete_node(&prev,&temp,temp->fname,temp->lname);
			add_node(c);
			
			
			
		   	find=1;
		    break;
		}
	 }
	 prev=temp;
	 temp=temp->_next;
	 i++;
	}
	if (find==0)
		printf("\t\t\n<<This contact does not exist or you chose not to Edit it.>>");
	else
		printf("\t\t\n<<Target contact was successfully updated!>>");
	printf("\n\n\n   ::Press a key to return main page & continue program|-->");
	getc(stdin);
	//free(dfname);
	//free(dlname);
}

void search(void)
{
	char ch;
	clrscr();
    printf("\nPhone Book12<::>$earch Contacts");
    printf("\n--------------------------------------------------------------------------------");
	printf("\nChoose search type,please:\n\n");
	printf("\t[1] |--> Search by first name\n");
	printf("\t[2] |--> Search by last name\n");
	printf("\t[3] |--> Search by phone number\n");
	printf("\t[4] |--> Search by cellphone number\n");
	printf("\t[5] |--> Main Menu\n");
	printf("\n\t::Enter a number (1-5): ");
	ch = getc(stdin);
	getc(stdin);
	printf("\n--------------------------------------------------------------------------------");
    switch(ch) {
		case '1':
		searchf();
	    break;
		case '2':
		searchl();
		break;
		case '3':
		searchp();
		break;
		case '4':
		searchc();
		break;
		case '5':
		default:
			return;
    }
}

void searchf(void)
{



	char fname[fnameSize];
	register int i=0,find=0;
	size_t len=0;
	size_t len_size=0;
	printf("Enter a first name to search:");
	len_size = get_input(fname,fnameSize);
	temp=head;
	

    	
    while(temp!=NULL)
    {
		if(strcmp(fname,temp->fname) == 0) 
		{
			find=1;
			break;
		}
		temp=temp->_next;
		i++;
    }		
	if(find==0)
		printf("\t\n<<Not Find!There is no contact with this name in phone book.>>");	
	else {
		//printf("\t\n<<Target contact found! Details:>>");
		printf("\n\nCantact %2.2d{",i+1);
		printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",temp->fname,temp->lname,temp->telep,temp->cellp);
	}
	printf("\nPress a key to search another contact.");
	getc(stdin);
	search();
	//free(fname);
}

void searchl(void)
{
	char lname[lnameSize];
	register int i=0,find=0;
	size_t len=0;
	size_t len_size=0;
	temp=head;
	printf("\n::Enter a last name to search:");
	len_size = get_input(lname,lnameSize);
    while(temp!=NULL)
    {
		if(strcmp(lname,temp->lname) == 0) 
		{
			find=1;
			break;
		}
		temp=temp->_next;
		i++;
    }	
	if(find==0)
		printf("\t\n<<Not Find!There is not contact with tish name in phone book.>>");	
	else {
		//printf("\t\n<<Target contact found! Details:>>");
		printf("\n\nCantact %2.2d{",i+1);
		printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",temp->fname,temp->lname,temp->telep,temp->cellp);
	}
	printf("\nPress a key to search another contact.");
	getc(stdin);
	search();
	//free(lname);
}

void searchp(void)
{
	
	char phone[telepSize];
	int i=0,find=0;
	char telep[5];
	size_t len=0;
	size_t len_size=0;
	temp=head;
	printf("\n::Enter a phone number to search:");
	len_size = get_input(phone,telepSize);
	strncpy(telep, phone,sizeof(telep)-1);
	  while(temp!=NULL)
    {
		if(strcmp(phone,temp->telep) == 0) 
		{
			find=1;
			break;
		}
		temp=temp->_next;
		i++;
    }	
	if(find==0)
		printf("\t\n<<Not Found!There is not contact with tish phone number  in phone book.>>");	
	else{
		//printf("\t\n<<Target contact found! Details:>>");
		printf("\n\nCantact %2.2d{",i+1);
		printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",temp->fname,temp->lname,temp->telep,temp->cellp);
	}
	printf("\nPress a key to search another contact.");
	getc(stdin);
	search();
	//free(phone);
}

void searchc(void)
{
	
	char phone[cellpSize] ;
	char cell[5];
	int i,find=0;
	size_t len=0;
	size_t len_size=0;
	printf("\n::Enter a cellphone number to search:");
	len_size = get_input(phone,cellpSize);
	strncpy(cell, phone,sizeof(cell)-1);
	temp=head;
     while(temp!=NULL)
    {
		if(strcmp(phone,temp->cellp) == 0) 
		{
			find=1;
			break;
		}
		temp=temp->_next;
		i++;
    }	
	if(find==0)
		printf("\t\n<<Not Find!There is not contact with tish cellphone number in phone book.>>");	
	else {
	
	printf("\n\nCantact %2.2d{",i+1);
	printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",temp->fname,temp->lname,temp->telep,temp->cellp);
	}
	printf("\nPress a key to search another contact.");
	getc(stdin);
	search();
	//free(phone);
}

void sort(void)
{
	char ch;
	clrscr();			
    printf("\nPhone Book12<::>$earch Contacts");
    printf("\n--------------------------------------------------------------------------------");
	printf("\nChoose sort type,please:\n\n");
	printf("\t[1] |--> Sort by first name\n");
	printf("\t[2] |--> Sort by last name\n");
	printf("\t[3] |--> Sort by phone number\n");
	printf("\t[4] |--> Sort by cellphone number\n");
	printf("\t[5] |--> Main Menu\n");	
	printf("\n\t::Enter a number (1-5): ");
	ch = getc(stdin);
	getc(stdin);
	printf("\n--------------------------------------------------------------------------------");
    switch(ch){
		case '1':
		sortf();
	    break;
		case '2':
		sortl();
		break;
		case '3':
		sortp();
		break;
		case '4':
		sortc();
		case '5':
		default:
			return ;
    }
}

void sortf(void)
{
	temp=fname_head;
			 
	printf("\nplease wait... .Contacts will be sorted by first names.");
	list2(0);
	printf("\n   ::Press any key to sort contact by another form... ");
	getc(stdin);
	sort();
}

void sortl(void)
{
	temp=lname_head;
	printf("\nplease wait... .Contacts will be sorted by last names.");
	list2(1);
	printf("\n   ::Press any key to sort contact by another form... ");
	getc(stdin);
	sort();
}
void sortp(void)
{
	temp=telep_head;
	printf("\nplease wait... .Contacts will be sorted by telephone numbers.");
	list2(2);
	printf("\n   ::Press any key to sort contact by another form... ");
	getc(stdin);
	sort();
}
void sortc(void)
{
	temp=cellp_head;
	printf("\nPlease wait... .Contacts will be sort by cellphone numbers.");
	list2(3);
	printf("\n   ::Press any key to sort contact by another form... ");
	getc(stdin);
	sort();
}

void list()
{
	temp=head;
	register int i=0;
	clrscr();
    printf("\nPhone Book12<::>All Contacts List");
    printf("\n--------------------------------------------------------------------------------");
	gotoxy(1,4);
	printf("Row");
	gotoxy(9,4);
	printf("First Name");
	gotoxy(27,4);
	printf("Last Name");
	gotoxy(44,4);
	printf("Telephone");
	gotoxy(60,4);
	printf("Cellphone");
	printf("\n--------------------------------------------------------------------------------");
	while(temp!=NULL)
	{
		gotoxy(1,i+6);						 
		printf("%3.3d",i+1);
		gotoxy(9,i+6);
		printf("%s",temp->fname);
		gotoxy(28,i+6);
		printf("%s",temp->lname);
		gotoxy(44,i+6);
		printf("%s",temp->telep);
		gotoxy(60,i+6);
		printf("%s",temp->cellp);
		temp=temp->_next;
		i++;
	}
	
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\n\t\t    **********End Of list!**********");	
	printf("\n\n\n   ::Press a key to return main page & continue program.|-->");
	getc(stdin);
	

	
}

void list2(int c)
{
	register int i=0;
    printf("\n--------------------------------------------------------------------------------");
	gotoxy(1,18);
	printf("Row");
	gotoxy(9,18);
	printf("First Name");
	gotoxy(27,18);
	printf("Last Name");
	gotoxy(44,18);
	printf("Telephone");
	gotoxy(60,18);
	printf("Cellphone");
	printf("\n--------------------------------------------------------------------------------");
	
	while(temp!=NULL)
	{
		gotoxy(1,i+21);						 
		printf("%3.3d",i+1);
		gotoxy(9,i+21);
		printf("%s",temp->fname);
		gotoxy(27,i+21);
		printf("%s",temp->lname);
		gotoxy(44,i+21);
		printf("%s",temp->telep);
		gotoxy(60,i+21);
		printf("%s",temp->cellp);
		if(c==0)
		{
		temp=temp->_next_fname;
		}
		else if(c==1)
		{
		temp=temp->_next_lname;
		}
		else if(c==2)
		{
		temp=temp->_next_telep;
		}
		else
		{
		temp=temp->_next_cellp;
		}
		i++;
	}
	
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	printf("\n\t\t    **********End Of list!**********");	
}

void help(void)
{
	 clrscr();
	 gotoxy(26,1);
	 printf("--------------------------");
	 gotoxy(26,2);
	 printf("|Welcome To Phone Book12!|");
	 gotoxy(26,3);
	 printf("--------------------------");
	 gotoxy(1,5);
	 printf("PhoneBook12>>[Help & Instructions] \n");
	 printf("--------------------------------------------------------------------------------\n");
	 printf("\nAbout Phonebook12\n *Version: 2.5\n *Valence: 50 Contacts(MAX)\n  *By: Morteza Zakeri (2011-12)");
	 printf("\n\nThis program allows you to have a list of your contacts.\nIt also allows you to have your listing added or deleted from your list.\nOther features of this program include:\nSearch,edit,sort & list.\n\n   ::Press a key to return main page & continue program.|-->");
	 getc(stdin);
 }

 void clrscr()
 {
	 system("clear");
 }
 
 void gotoxy(int x, int y)
 {
	 printf("%c[%d;%df", 0x1B, y, x);
 }
 void update_node_lname(struct contact_node **new_node,struct contact_node **head)
{

struct contact_node *front,*rear,*temp;
char string[31];
char new_string[31];
strncpy(string,(*head)->lname,sizeof(string)-1);
strncpy(new_string,(*new_node)->lname,sizeof(new_string)-1);

if (head==NULL||strcmp((*new_node)->lname,(*head)->lname)<0)
{
(*new_node)->_next_lname=*head;
*head=*new_node;

}

else
{
rear=*head;
front=rear->_next_lname;
while(front!=NULL&&strcmp((*new_node)->lname,front->lname)>0)
{
rear=front;
front=front->_next_lname;
}
(*new_node)->_next_lname=front;
rear->_next_lname=(*new_node);

}

}
 void update_node_cellp(struct contact_node **new_node,struct contact_node **head)
{


char string[31];
char new_string[31];
strncpy(string,(*head)->cellp,sizeof(string)-1);
strncpy(new_string,(*new_node)->cellp,sizeof(new_string)-1);

if (head==NULL||strcmp((*new_node)->cellp,(*head)->cellp)<0)
{
(*new_node)->_next_cellp=*head;
*head=*new_node;

}

else
{
rear=*head;
front=rear->_next_cellp;
while(front!=NULL&&strcmp((*new_node)->cellp,front->cellp)>0)
{
rear=front;
front=front->_next_cellp;
}
(*new_node)->_next_cellp=front;
rear->_next_cellp=(*new_node);

}

}
 void update_node_telep(struct contact_node **new_node,struct contact_node **head)
{


char string[31];
char new_string[31];
strncpy(string,(*head)->telep,sizeof(string)-1);
strncpy(new_string,(*new_node)->telep,sizeof(new_string)-1);

if (head==NULL||strcmp((*new_node)->telep,(*head)->telep)<0)
{
(*new_node)->_next_telep=*head;
*head=*new_node;

}

else
{
rear=*head;
front=rear->_next_telep;
while(front!=NULL&&strcmp((*new_node)->telep,front->telep)>0)
{
rear=front;
front=front->_next_telep;
}
(*new_node)->_next_telep=front;
rear->_next_telep=(*new_node);

}

}
void delete_lname(char * fname,char * lname)
{
temp=lname_head;
prev=temp;
if (strcmp (fname, temp->fname) == 0 && strcmp (lname, temp->lname) == 0 )
{
	lname_head=lname_head->_next_lname;
	return ;
}
while(temp!=NULL)
{
if (strcmp (fname, temp->fname) == 0 && strcmp (lname, temp->lname) == 0 )
{
	prev->_next_lname=temp->_next_lname;

}
prev=temp;
temp=temp->_next_lname;

}
}
void delete_telep(char * fname,char * lname)
{
temp=telep_head;
prev=temp;
if (strcmp (fname, temp->fname) == 0 && strcmp (lname, temp->lname) == 0 )
{
	telep_head=telep_head->_next_telep;
	return ;
}
while(temp!=NULL)
{
if (strcmp (fname, temp->fname) == 0 && strcmp (lname, temp->lname) == 0 )
{
	prev->_next_telep=temp->_next_telep;

}
prev=temp;
temp=temp->_next_telep;

}
}
void delete_cellp(char * fname,char * lname)
{
temp=cellp_head;
prev=temp;
if (strcmp (fname, temp->fname) == 0 && strcmp (lname, temp->lname) == 0 )
{
	cellp_head=cellp_head->_next_cellp;
	return ;
}
while(temp!=NULL)
{
if (strcmp (fname, temp->fname) == 0 && strcmp (lname, temp->lname) == 0 )
{
	prev->_next_cellp=temp->_next_cellp;

}
prev=temp;
temp=temp->_next_cellp;

}

}
