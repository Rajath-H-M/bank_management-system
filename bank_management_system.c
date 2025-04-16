#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node{
	int acc;
	char name[50];
	int date,month,year;
	char number[12];
	char aadhar[15];
	char type[20];
	int passwd;
	float balance;
	struct node *llink;
	struct node *rlink;
};
typedef struct node *NODE;
NODE first =NULL;

void insert(NODE temp){

	if(first==NULL){
		first=temp;
		return;
	}
	NODE cur;
	cur=first;
	while(cur->rlink!=NULL){
		cur=cur->rlink;
	}
	
	temp->llink=cur;
	cur->rlink=temp;
	return; 
}

NODE search(){
	int key,pass;
	printf("Enter Account number\t:");
	scanf("%d",&key);
	printf("Enter password\t:");
	scanf("%d",&pass);
	NODE cur=first;
	if(cur==NULL){
		printf("ERROR\n");
	}
	while(cur!=NULL){
		if(cur->acc==key&&cur->passwd==pass){
			return cur;
		}
		cur=cur->rlink;
	}printf("ERROR\n");
}

//1.CREATE ACCOUNT
void newAcc(NODE first,int count){
	NODE temp;
	temp=(NODE)malloc(sizeof(NODE));
	temp->llink=NULL;
	temp->rlink=NULL;
	
	printf("***Enter Account holders details***\n");
	temp->acc=count;
	printf("NAME\t:");
	scanf("%s",temp->name);
	printf("DOB(DD MM YYYY)\t:");
	scanf("%d %d %d",&temp->date,&temp->month,&temp->year);
	printf("Mobile number\t:");
	scanf("%s",temp->number);
	printf("Aadhar number\t:");
	scanf("%s",temp->aadhar);
	printf("Type(Savings/Current)\t:");
	scanf("%s",temp->type);
	printf("Password(4 digit number)\t:");
	scanf("%d",&temp->passwd);
	temp->balance=0;
	printf("\nYOUR ACCOUNT NUMBER (remember)\t:%d\n",temp->acc);
	insert(temp);
	return;
}

//2.UPDATE ACCOUNT
void updateAcc(NODE first){
	int key,pass,date,month,year,option,passwd;
	char name[20],number[12];
	NODE cur=NULL;

		printf("Choose the deatils to edit\n");
		printf("1.NAME\n2.DOB\n3.MOBILE\n4.PASSWORD\n5.EDIT COMPLETE\n");
		printf("Enter opion\t:");
		scanf("%d",&option);
		switch(option){
		
			case 1:cur=search();
				   if(cur!=NULL){
				   		printf("Enter new name\n");
				   		scanf("%s",name);
				   		strcpy(cur->name,name);
				   		printf("Update successful\n");
				   }
				   break;
			case 2:cur=search();
				   if(cur!=NULL){
				   		printf("Enter new DOB\n");
				   		scanf("%d%d%d",&date,&month,&year);
				   		cur->date=date;
				   		cur->month=month;
				   		cur->year=year;
				   		printf("Update successful\n");
					}
			       break;
			case 3:cur=search();
				   if(cur!=NULL){
				   		printf("Enter new number\n");
				   		scanf("%s",number);
				   		strcpy(cur->number,number);
				   		printf("Update successful\n");
				   	}
			   	   break;
			case 4:cur=search();
			   	   if(cur!=NULL){
						printf("Enter new password\n");
				   		scanf("%d",passwd);
				   		cur->passwd=passwd;
				   		printf("Update successful\n");
				   }
			   	   break;
			default:break;
		}	
}

//3.TRANSACTIONS
void transaction(NODE first){
	int option;
	float amount;
	NODE cur=NULL;
	printf("Available services\n1.CREDIT\n2.DEBIT\n3.MAIN MENU\n");
	printf("Enter your option\n");
	scanf("%d",&option);
	switch(option){
		case 1:cur=search(first);
			   if(cur!=NULL){
			   		printf("ENTER THE CREDIT AMOUNT\n");
			   		scanf("%f",&amount);
			   		cur->balance+=amount;
			   		printf("Clear balance\t:%.2f",cur->balance);
			   		return;
			   }
			   break;
		case 2:cur=search(first);
			   if(cur!=NULL){
			   	
			   		printf("ENTER THE DEBIT AMOUNT\n");
			   		scanf("%f",&amount);
			   		if(cur->balance>=amount){
			   			cur->balance-=amount;
			   			printf("Clear balance\t:%.2f",cur->balance);
			   			return;
			   		}
			   		else{
			   			printf("Transaction failed(low balance)\n");
			   			return;
					}
			   	
			   }
			   break;
		default:break;
	}
}

//4.VIEW ACCOUNT DETAILS
void detailsAcc(NODE first){
	int acc,pass;
	NODE cur;
	printf("Enter Account number:\t");
	scanf("%d",&acc);
	printf("Enter password\t:");
	scanf("%d",&pass);
	cur=first;
	if(first==NULL){
		printf("No accounts found\n");
		return ;
	}
	while(cur!=NULL){
		if(cur->acc==acc&&cur->passwd==pass){
			printf("USER DETAILS\n");
			printf("ACCOUNT NUMBER\t:%d\n",cur->acc);
			printf("NAME\t:%s\n",cur->name);
			printf("DOB\t:%d/%d/%d\n",cur->date,cur->month,cur->year);
			printf("MOBILE\t:%s\n",cur->number);
			printf("AADHAR\t:%s\n",cur->aadhar);
			printf("TYPE\t:%s\n",cur->type);
			printf("BALANCE\t:%.2f\n",cur->balance);
			return ;
		}
		cur=cur->rlink;
	}
	printf("Account not found or invalid password\n");
	return ;
}

//5.REMOVE ACCOUNT
void removeAcc(NODE first){
	int pass,key;
	NODE cur;
	NODE prev,next;
	printf("Enter Account number\t:");
	scanf("%d",&key);
	printf("Enter password\t:");
	scanf("%d",&pass);
	if(first==NULL){
		printf("ACCOUNT NOT FOUND\n");
		return;
	}
	if(first->acc==key&&first->rlink==NULL){
		if(first->passwd==pass){
			cur =first;
			free(cur);
			printf("Account no %d deleted",key);
			return;
		}
	}
			
	if(first->acc==key){
		if(first->passwd==pass){
			cur=first;
			first=first->rlink;
			first->llink=NULL;
			free(cur);
			printf("Account no %d deleted",key);
			return;
		}
		else{
			printf("Wrong password\n");
			return;
		}
	}
	cur=first;
	prev=NULL;
	next=cur->rlink;
	while(cur!=NULL){
		if(cur->acc==key&&cur->rlink!=NULL){
			if(cur->passwd==pass){
				prev->rlink=next;
				next->llink=prev;
				free(cur);
				printf("Account no %d deleted",key);
				return;
			}
			else{
				printf("Wrong password\n");
				return;
			}
		}
		if(cur->acc==key&&cur->rlink==NULL){
			if(cur->passwd==pass){
				prev->rlink=NULL;
				free(cur);
				printf("Account no %d deleted",key);
				return;
			}
			else{
				printf("Wrong password\n");
				return;
			}
		}
		prev=cur;
		cur=cur->rlink;
		next=next->rlink;
	}
	printf("Error try again\n");
	return;
}

//6.CUSTOMERS LIST
void viewList(NODE first){
	NODE cur=first;
	printf("\nAc.no\tNAME\n\n");
	if(cur==NULL)
		return;
	while(cur->rlink!=NULL){
		printf("%d\t\%s\n",cur->acc,cur->name);
		cur=cur->rlink;
	}
	printf("\n");
	return;
}

int main(){
	int option=0,count=0,key=0;
	do{
		printf("\n\t\t**********BANK MANAGEMENT SYSTEM**********\n ");
		printf("____________________________________________________________________________________________________\n");
		printf("Available services\n");
		printf("1.CREATE ACCOUNT\n2.UPDATE ACCOUNT\n");
		printf("3.TRANSACTIONS\n4.VIEW ACCOUNT DETAILS\n");
		printf("5.REMOVE ACCOUNT\n6.CUSTOMERS LIST\n7.Exit\n");
		printf("Enter your option\t:");
		scanf("%d",&option);
	
		switch(option){
		
			case 1:count++;
				   newAcc(first,count);
			   	   break;
			case 2:updateAcc(first);
			       break;
			case 3:transaction(first);
			   	   break;
			case 4:detailsAcc(first);
			   	   break;
			case 5:removeAcc(first);
			   	   break;
			case 6:viewList(first);
			   	   break;
			default:exit(0);
		}	
	}while(option!=7);
}