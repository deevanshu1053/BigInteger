#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"


struct node* addNodeAtHead(struct node *head, int val)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->data = val;
    temp->next = head;
    head = temp;
    return head;
}

void addNodeAtEnd(struct node** head, int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        struct node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

struct BigInteger initialize(char *ch)
{
    struct BigInteger big;
    big.head = NULL;
    big.sign = 1;
    big.len = 0;
    int i = 0;
    if (ch == NULL)
    {
        return big;
    }
    if (ch[0] == '-')
    {
        big.sign = -1;
        i++;
    }
    for (; ch[i] != '\0'; i++)
    {
        big.head=addNodeAtHead(big.head, ch[i]-'0');
        big.len++;
    }
    big=deleteZeroes(big);
    return big;
}

void print(struct node* head){
    if(head==NULL)
        return;
    print(head->next);
    printf("%d",head->data);
}

void display(struct BigInteger big)
{
    if(big.sign==-1)
        printf("-");
    print(big.head);
    printf("\n");
}


int compare(const struct BigInteger ori_big1,const struct BigInteger ori_big2){
    struct BigInteger big1=ori_big1,big2=ori_big2;
    if(big1.len>big2.len){
        return 0;             //return 0 if big1 > big2
    }
    if(big1.len<big2.len){
        return 1;            //return 1 if big1 < big2
    }
    struct node *l1,*l2;
    int flag=-1;
    l1=reverse(big1.head);
    l2=reverse(big2.head);
    struct node *head1=l1,*head2=l2;
    while(l1!=NULL){
        if(l1->data == l2->data){
            l1=l1->next;
            l2=l2->next;
            flag=-1;
            continue;
        }
        else if((l1->data) > (l2->data)){
            flag = 0;         //set flag 0 if big1 > big2
            break;
        }
        else if((l1->data)<(l2->data)){
            flag = 1;          //set flag 1 if big1 < big2
            break;
        }
    }
    l1=reverse(head1);      //reverse to original number
    l2=reverse(head2);      
    return flag;                //flag will be -1 if number are equal
}

struct node* reverse(struct node* head)
{
    if(head==NULL)
        return head;
    struct node *prev=NULL,*current=head,*next=NULL;
    while(current!=NULL){
        next=current->next;
        current->next=prev;
        prev=current;
        current=next;
    }
    return prev;
}

struct BigInteger deleteZeroes(struct BigInteger big){
    if(big.head==NULL)
        return big;
    struct node *itr=big.head;
    itr=reverse(big.head);
    while(itr!=NULL){
        if(itr->data==0 && itr->next==NULL){
            break;
        }
        if(itr->data==0 ){
            struct node *temp=itr;
            itr=itr->next;
            big.len--;
            free(temp);
        }
        else
            break;
    }
    itr=reverse(itr);
    big.head=itr;
    return big;
}

struct BigInteger add(struct BigInteger big1,struct BigInteger big2){
    struct BigInteger res=initialize("");
    struct node *l1=big1.head,*l2=big2.head;
    int flag;
    if(compare(big1,big2)==1){
        l1=big2.head;
        l2=big1.head;
    }
    int carry=0,sum;
    if(big1.sign == big2.sign){
        while(l1!=NULL || l2!=NULL || carry){
	        sum=carry;
	        if(l1!=NULL){
	            sum+=l1->data;
	            l1=l1->next;
	        }
            if(l2!=NULL){
                sum+=l2->data;
                l2=l2->next;
            }
            if(sum>=10){
            	carry=sum/10;
            	sum=sum%10;
            }
            else{
            	carry=0;
            }
            res.head=addNodeAtHead(res.head,sum);
            res.len++;
        }
        res.head=reverse(res.head);
        res.sign=big1.sign;
        return res;
    }
    else if(big1.sign!=big2.sign){
        big2.sign=big1.sign;
        res=sub(big1,big2);
        return res;
    }
    return res;
}

struct BigInteger sub(struct BigInteger big1,struct BigInteger big2){
	struct node *l1=big1.head,*l2=big2.head;
	int diff,borrow=0,flag=1;
	if(compare(big1,big2)==1){
        l1=big2.head;
        l2=big1.head;
        flag=-1;
    }
    struct BigInteger res=initialize("");
    if(big1.sign==big2.sign){
    	while(l1!=NULL || l2!=NULL || borrow){
    		if(l1!=NULL){
    			diff=l1->data-borrow;
    			l1=l1->next;
    		}
    		if(l2!=NULL){
    			diff-=l2->data;
    			l2=l2->next;
    		}
    		if(diff<0){
    			borrow=1;
    			diff+=10;
    		}
    		else
    			borrow=0;
    		res.head=addNodeAtHead(res.head,diff);
    		res.len++;
    	}
    	res.head=reverse(res.head);
    	res.sign=flag*big1.sign;
        res=deleteZeroes(res);
        return res;
    }
    else if(big1.sign!=big2.sign){
    	big2.sign=big1.sign;
    	return add(big1,big2); 
    }
    res=deleteZeroes(res);
    return res;
}
void destroy(struct BigInteger *big){
    struct node *temp;
    if(big->head==NULL){
        return;
    }
    while(big->head!=NULL){
        temp=big->head;
        big->head=big->head->next;
        free(temp);
    }
    big->len=0;
    big->sign=0;
    return;
}

struct BigInteger mul(struct BigInteger big1,struct BigInteger big2){
    struct node* list=NULL,*itr1=big2.head;
    int cnt=0;
    struct BigInteger temp=initialize("1"),ans=initialize("0");
    if(compare(big1,temp)==-1){
        big2.sign*=big1.sign;
        return big2;
    }
    if(compare(big2,temp)==-1){
        big1.sign*=big2.sign;
        return big1;
    }
    while(itr1!=NULL){
        struct node *itr2=big1.head;
        struct BigInteger temp=initialize("");
        int digit,product,carry=0;
        for(int i=0;i<cnt;i++){
            temp.head=addNodeAtHead(temp.head,0);
        }
        while(itr2!=NULL){
            product=(itr2->data*itr1->data)+carry;
            carry=product/10;
            digit=product%10;
            addNodeAtEnd(&temp.head,digit);
            itr2=itr2->next;
        }
        if(carry!=0){
            addNodeAtEnd(&temp.head,carry);
        }
        cnt++;
        ans=add(ans,temp);
        itr1=itr1->next;
        destroy(&temp);
    } 
    ans.sign=big1.sign*big2.sign;
    return ans;   
}

struct BigInteger div1(struct BigInteger big1,struct BigInteger big2){
    struct BigInteger ans=initialize(""),res=initialize("0"),temp=initialize("1");
    int flag=1;
    if(big1.sign!=big2.sign){
        flag=-1;
    }
    big1.sign=big2.sign=1;
    if(compare(big2,temp)==-1){
        big1.sign=flag;
        return big1;
    }
    if(compare(big1,res)==-1){
        return res;
    }
    if(compare(big2,res)==-1){
        return ans;
    }
    if(compare(big1,big2)==1)
        return res;
    if(compare(big1,big2)==-1){
        return temp;
    }
    ans=big1;
    int cnt;
    while(compare(ans,big2)!=1){
        ans=sub(ans,big2);
        res=add(res,temp);
    }
    res.sign=flag;
    return res;
}

struct BigInteger mod(struct BigInteger big1,struct BigInteger big2){
    struct BigInteger ans=initialize(""),res=initialize("0"),one=initialize("1");
    if(compare(big1,big2)==1){
        return big1;
    }
    if(compare(big2,one)==-1){
        return res;
    }
    if((compare(big1,res)==-1) || (compare(big1,big2)==-1)){
        return res;
    }
    if(compare(big2,res)==-1){
        return ans;
    }
    ans=div1(big1,big2);
    ans=sub(big1,mul(ans,big2));
    ans.sign=big1.sign;
    return ans;
}

struct BigInteger divideBy2(struct BigInteger num)
{
    struct BigInteger result;
    result.head= NULL;
    result.len = 0;
    result.sign = num.sign;
    int carry = 0;
    struct node *current = num.head;
    current=reverse(num.head);
    while (current)
    {
        int value = current->data + carry * 10;
        int quotient = value / 2;
        carry = value % 2;
        result.head=addNodeAtHead(result.head, quotient);
        current = current->next;
    }
    // Remove leading zeros in the result
    result=deleteZeroes(result);
    return result;
}


