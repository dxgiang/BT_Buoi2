/**
*Thuật toán chuyển từ trung tố sang hậu tố
    *Khởi tạo Stack rỗng.
    *Khởi tạo 2 chuỗi x và token; i, j lần lượt là index của Infix và Postfix.
    *Duyệt vòng lặp for từ i = 1 cho đến cuối chuỗi Infix:
        *Nếu Infix[i] là toán hạng thì đưa vào Postfix.
        *Nếu Infix[i] là toán tử thì push vào ngăn xếp s.
        *Nếu Infix[i] là “)” thì pop vào ngăn xếp s (lấy giá trị trên đỉnh của s) sau đó đưa vào Postfix.
    *Output: Postfix là biểu thức hậu tố.

*Tính giá trị biểu thức hậu tố
*Duyệt biểu thức dạng chuỗi từ trái sang phải:

*Dùng hàm isdigit để kiểm tra:
    *Nếu là toán hạng thì dùng push() đưa vào ngăn xếp s.
    *Nếu là toán tử thì pop() 2 toán hạng trong ngăn xếp s ra, sau đó tính toán giá trị của chúng dựa vào toán tử này, sau đó push() lại vào s.
    *Thực hiện cho đến khi gặp kí tự \0 kết thúc chuỗi.
    *Kết quả của biểu thức chính là phần tử còn lại cuối cùng trong ngăn xếp s.
*/
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

#define size 200

// Khai báo
struct Stack
{
    float stack[size];
    int top;
};

void init(Stack* s)
{
    s->top = -1;
}

int isEmpty(Stack* s)
{
    return s->top == -1 ? 1 : 0;
}

// push operation
void push(struct Stack* s, float item)
{
    if (s->top == (size - 1))
    {
        printf("\nStack Overflow.");
    }
    else
    {
        ++s->top;
        s->stack[s->top] = item;
    }
}

int top(Stack* s)
{
    return (s->stack[s->top]);
}

// pop operation
float pop(struct Stack* s)
{
    float ret = -1;
    if (s->top == -1)
        printf("\nStack Underflow.");
    else
    {
        ret = s->stack[s->top];
        --s->top;
    }
    return ret;
}
//Gán quyền ưu tiên cho toán tử
int Precedence(char x)
{
    if (x == '(')
        return 0;
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/' || x == '%')
        return 2;
    return 3;
}
//Chuyển từ trung tố sang hậu tố
void Infixtopostfix(char infix_exp[], char postfix_exp[])
{
    Stack s;
    char x, token;
    int i = 0, j = 0; // i - index of infix, j - index of postfix
    init(&s);
    for (i = 0; infix_exp[i] != '\0'; i++)
    {
        token = infix_exp[i];
        if (isalnum(token))
            postfix_exp[j++] = token;
        else if (token == '(')
            push(&s, '(');
        else if (token == ')')
            while ((x = pop(&s)) != '(')
                postfix_exp[j++] = x;
        else
        {
            while (Precedence(token) <= Precedence(top(&s)) && !isEmpty(&s))
            {
                x = pop(&s);
                postfix_exp[j++] = x;
            }
            push(&s, token);
        }
    }

    while (!isEmpty(&s))
    {
        x = pop(&s);
        postfix_exp[j++] = x;
    }

    postfix_exp[j] = '\0';
}
//Tính giá trị biểu thức hậu tố
float Evaluate(char* Postfix)
{
    struct Stack s;
    char* p;
    float op1, op2, result;
    s.top = -1;
    p = &Postfix[0];

    while (*p != '\0')
    {
        while (*p == ' ' || *p == '\t')
        {
            p++;
        }
        if (isdigit(*p))
        {
            int num = 0;
            while (isdigit(*p))
            {
                num = num * 10 + *p - 48;
                *p++;
            }
            push(&s, num);
        }
        else
        {
            op1 = pop(&s);
            op2 = pop(&s);
            switch (*p)
            {
            case '+':
                result = op2 + op1;
                break;
            case '-':
                result = op2 - op1;
                break;
            case '/':
                result = op2 / op1;
                break;
            case '*':
                result = op2 * op1;
                break;
            default:
                printf("\nInvalid Operator");
                return 0;
            }
            push(&s, result);
        }
        p++;
    }

    result = pop(&s);
    return result;
}

//Hàm main
int main()
{
    // Khai báo infix chuỗi và chuỗi prefix
    char infix[size], postfix[size];
    printf("Nhap bieu thuc Infix: ");
    gets(infix);
    // Hàm gọi convert
    Infixtopostfix(infix, postfix);
    // In ra biểu thức Prefix
    printf("Postfix: %s\n", postfix);
    printf(" = %f\n", Evaluate(&postfix[0]));
    gets(infix);
    return 0;
}