#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
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
void display(B_node *ptr,int blanks){
    if (ptr)
    {
        int i;
        for(i=1;i<=blanks;i++)
        printf(" ");
        for(i=0;i<ptr->count;i++){
            if(i<ptr->count){
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
            }

        }
        printf("\n");
        for(i=0;i<=ptr->count;i++){
            display(ptr->branches[i],blanks+10);
        }
    }
}//END_DISPLAY_FUNCTION

//splitting function
data split(B_node* sptr,data k,B_node* nn2){
    int
}


int main()
{
    
    
}
