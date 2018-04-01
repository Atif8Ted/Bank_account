#include <stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>
#define MAX_NAME_LENGTH 25
#define MAX_ACC_NUM_LEN 20
#define MAX_ADDRESS_LEN 100
#define MAX_NID_LEN 20 
#define MAX_DATE_LEN 10
#define MAX_EMAIL_LEN 30
//#define MAX_CARD_LEN 16
//#define MAX_CVV_LEN 4
#define MAX 4

typedef struct card_database{
    char dob[MAX_DATE_LEN];
    char address[MAX_ADDRESS_LEN];
    char fullname[MAX_NAME_LENGTH];
    char NID[MAX_NAME_LENGTH]; // stores social security number or drivers license /pan /addhar 
    char email[MAX_EMAIL_LEN];
    long long int card_num;
    char expiry_date[MAX_DATE_LEN];
    char issue_date[MAX_DATE_LEN];
    int cvv_no;
}data;
typedef struct card_node_struct {
    data key[MAX];
    struct B_tree_type* branches[MAX];
    struct B_tree_type* parent;
    int count;
    int leaf;
}B_node;

//Dislpay_function
void display(B_node *ptr, int blanks)
{
	if (ptr)
	{
		int i;
		for(i=1;i<=blanks;i++)
			printf(" ");
		for (i=0; i < ptr->count; i++)
		{
			if(i<ptr->count)
			{
				printf("\n");
				printf("----------------------------------------------------");
				printf("\nCustomer Name:%s",ptr->key[i].fullname);
				printf("\nAddress:%s",ptr->key[i].address);
				printf("\nDOB:%d",ptr->key[i].dob);
				printf("\nNational Identity Number:%s",ptr->key[i].NID);
				printf("\nE-mail id:%s",ptr->key[i].email);
                printf("\nCredit Card No:%lld",ptr->key[i].card_num);
                printf("\nIssue Date:%s",ptr->key[i].issue_date);
                printf("\nExpiry Date:%s",ptr->key[i].expiry_date);
                printf("\nCVV NO:%d",ptr->key[i].cvv_no);
				printf("\n");
			//	printf("----------------------------------------------------");
			}
			
		}
		printf("\n");
		for (i=0; i <= ptr->count; i++)
			display(ptr->branches[i], blanks+10);
	}
}//END_DISPLAY_FUNCTION

//splitting function
data split(B_node* sptr,data k,B_node* nn2){
    int i=0,p,j;
    data temp[MAX],t;
    for(i=0;i<sptr->count;i++){
        temp[i]=sptr->key[i];
    }
    temp[sptr->count]=k;
    for(i=sptr->count;i>0;i--){
        if(temp[i].card_num<temp[i-1].card_num){
            t=temp[i];
            temp[i]=temp[i-1];
            temp[i-1]=t;
        }
    }//end_for_loop

    p=2; // for index promotion
	for(i=0;i<p;i++)
	{
		sptr->key[i]=temp[i];
	}
	for(i=p+1, j=0;i<=sptr->count;i++, j++)
	{
		nn2->key[j]=temp[i];
	}
	
	nn2->leaf=sptr->leaf;
	nn2->count=1;
	sptr->count=2;
    return temp[2];
}//split function ends


//insertion function starts
B_node* Insertion(data k, B_node* root){

	int done=0, visit=0, found_place=0, f=0, i, j;
	B_node *ptr, *nn1, *nn2, *nn3,  *temp2[MAX] ;
	data temp1;
	
	
	if(root==NULL){
		nn1=(B_node*)malloc(sizeof(B_node));
		nn1->key[0]=k;
		nn1->count=1;
		nn1->leaf=1;
		root=nn1;
		nn1->parent=NULL;		
	}

    //root!=null
	else{
		ptr=root;
		int check=0;
		visit=0;
		if(ptr->leaf!=1){
			
			while(ptr->leaf!=1){	//check for right node to insert element
				check=0;
				for(i=0;i<ptr->count && check==0;i++){
					if(ptr->key[i].card_num==k.card_num){
						check=1;
					}
				}
				if(check==0){
					if(k.card_num<ptr->key[0].card_num)
					{
						found_place=1;
						f=0;	
					}
					else if(k.card_num>ptr->key[ptr->count-1].card_num)
					{
						found_place=1;
						f=ptr->count;	
					}	
					else{
						f=1;
						while((f<ptr->count)&&(found_place=0))
						{
							if((k.card_num>ptr->key[f-1].card_num)&&(k.card_num<ptr->key[f].card_num))
							{
								found_place=1;
							}						
							else
							{
								f++;
							}
						}
					}
					ptr=ptr->branches[f];
				}
				else{
					ptr->key[i]=k;
				}
			
				
			}
		}
		while(done==0)
		{	//check for count
		
				if(visit!=0)
				{
					for(i=0,j=0;j<ptr->count+1;j++)
					{
						if(i==f)
						{
							temp2[i]=ptr->branches[j];
							i++;
							temp2[i]=nn2;
							i++;
													
						}
						else
						{
							temp2[i]=ptr->branches[j];
							i++;
						}
					}
					for(i=0;i<ptr->count+2;i++)
					{
						ptr->branches[i]=temp2[i];
					
					}
				
				}
		
			if(ptr->count<MAX-1)
			{
				check=0;
				for(i=0;i<ptr->count&&check==0;i++)
				{
					if(ptr->key[i].card_num==k.card_num)
					{
						duplicate=1;
					}
				}
				if(duplicate==0)
				{				
					ptr->key[ptr->count]=k;
					for(i=ptr->count;i>0;i--)
					{
						if(ptr->key[i].lib_num<ptr->key[i-1].lib_num)
						{
									
							temp1=ptr->key[i];
							ptr->key[i]=ptr->key[i-1];
							ptr->key[i-1]=temp1;
						}
					}
					ptr->count=ptr->count+1;
				}
				else	//if duplicate==1
				{
					printf("purana");
					ptr->key[i]=k;
				}
				done=1;
			}	
			
			else 	//if(ptr->count==MAX-1)
			{
				nn2=(B_node*)malloc(sizeof(B_node));
				k=split(ptr, k, nn2);
				//to adjust branches if ptr is not leaf node
				if(ptr->leaf!=1)
				{
					nn2->branches[0]=ptr->branches[ptr->count+1];
					ptr->branches[ptr->count+1]=NULL;	
				}
				//to adjust branches if ptr is not leaf node
				if(ptr->parent!=NULL)
				{
					
					nn2->parent=ptr->parent;
					ptr=ptr->parent;
					visit++;
					
				}
				else 	//ptr->parent==NULL
				{
					nn3=(B_node*)malloc(sizeof(B_node));
					nn3->leaf=0;
					nn3->key[0]=k;
					nn3->key[0]=k;
					nn3->count=1;
					nn3->branches[0]=ptr;
					nn3->branches[1]=nn2;
					nn3->parent=NULL;
					root=nn3;
					ptr->parent=nn3;
					nn2->parent=nn3;
					done=1;
				}
			}
			
		}
		
		
	}

	return root;
}//end of insertion



int main()
{
    
    
}
