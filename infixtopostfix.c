#include <stdio.h>
#include <string.h>
#define SIZE 100
char stack[100];
int top=-1;
void push(char c)
{
    if(top==SIZE-1)
    {
        printf("Overflow");
        return;
    }
    stack[++top]=c;
}

char pop()
{
    if(top==-1)
    {
        printf("Underflow");
        return;
    }
    return stack[top--];
}

int pred(char c)
{
    switch(c)
    {
        case '^':return 3;
        case '/':
        case '*':return 2;
        case '-':
        case '+':return 1;
        default: return 0;
    }
}

void main()
{
    char infix[20],postfix[20];
    int pos=0,index=0;
    printf("Enter infix expression ");
    scanf("%s",infix);
    strcat(infix,")");
    push('(');
    while(infix[index]!='\0')
    {
        char character=infix[index];
        switch(character)
        {
            case '(':push('(');
                     break;
            case ')':while(stack[top]!='(')
                        postfix[pos++]=pop();
                      pop();
                      break;
            case '+':
            case '-':
            case '/':
            case '*':
            case '^':while(pred(top)>=pred(character))
                        postfix[pos++]=pop();
                     push(character);
                     break;
            default:postfix[pos++]=character;
        }
        index++;
    }
    postfix[pos]='\0';
    printf("Postfix expression:%s",postfix);
}
