#ifndef BIGINTEGER_H
#define BIGINTEGER_H
struct node
{
    int data;
    struct node *next;
};

struct BigInteger
{
    struct node *head;
    int len, sign;
};
struct node* addNodeAtHead(struct node *head, int val);
void addNodeAtEnd(struct node** head, int data);
struct BigInteger initialize(char *ch);
void print(struct node* head);
void display(struct BigInteger big);
int compare(const struct BigInteger ori_big1,const struct BigInteger ori_big2);
struct BigInteger divideBy2(struct BigInteger num);
struct node* reverse(struct node* head);
struct BigInteger deleteZeroes(struct BigInteger big);
struct BigInteger add(struct BigInteger big1,struct BigInteger big2);
struct BigInteger sub(struct BigInteger big1,struct BigInteger big2);
void destroy(struct BigInteger *big);
struct BigInteger mul(struct BigInteger big1,struct BigInteger big2);
struct BigInteger div1(struct BigInteger big1,struct BigInteger big2);
struct BigInteger mod(struct BigInteger big1,struct BigInteger big2);

#endif