/**
Tính giá trị biểu thức tiền tố
Đảo biểu thức tiền tố.
Duyệt từ trái sang phải và dùng hàm isdigit() kiểm tra nếu là toán hạng thì đưa vào trong chuỗi.
Đổi chuỗi thành số và đưa vào trong Stack.
Tiếp tục duyệt nếu là toán tử thì lấy lần lượt 2 phần tử trên nhất của Stack ra tính toán và đưa kết quả tính được vào lại Stack.
Thực hiện cho đến khi gặp kí tự \0 kết thúc chuỗi.
Kết quả của biểu thức chính là phần tử còn lại cuối cùng trong Stack.
*/

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
using namespace std;

#define size 200

// Khai báo
char stack[size];
int top = -1;

// Push operation
void push(char c)
{
	if (top >= size - 1)
		printf("\n Stack Overflow.");
	else
	{
		top++;
		stack[top] = c;
	}
}

// Pop operation
char pop()
{
	char c;
	c = '\0';
	if (top < 0)
		printf("\n Stack Underflow.");
	else
	{
		c = stack[top];
		top--;
	}
	return c;
}

// Xác định ký tự có phải là toán tử hay không
int isOperator(char symbol)
{
	if (symbol == '^' || symbol == '*' || symbol == '/' || symbol == '+' || symbol == '-')
		return 1;
	else
		return 0;
}

/*Gán quyền ưu tiên cho toán tử*/
// Giả sử số cao hon thì độ ưu tiên cao hơn
int Precedence(char symbol)
{
	if (symbol == '^')
		return(5);
	else if (symbol == '/')
		return(4);
	else if (symbol == '*')
		return(3);
	else if (symbol == '+')
		return(2);
	else if (symbol == '-')
		return(1);
	else
		return(0);
}


//Khai báo hàm
void push(char c);
char pop();
int isOperator(char symbol);
int Precedence(char symbol);
void InfixToPrefix(char infix_exp[], char prefix_exp[]);


/*Chuyển từ Infix sang Prefix*/
void InfixToPrefix(char infix_exp[], char prefix_exp[])
{
	int i, j, k, pos, len;
	char item, x, rev[size];
	// Ðảo ngượcc biểu thức Infix
	pos = 0;
	len = strlen(infix_exp);
	for (k = len - 1; k >= 0; k--)
	{
		rev[pos] = infix_exp[k];
		pos++;
	}
	rev[pos] = '\0';
	strcpy(infix_exp, rev);
	// Thay đổi các dấu “(” thành “)” và “)” thành “(”
	for (i = 0; infix_exp[i] != '\0'; i++)
	{
		if (infix_exp[i] == ')')
			infix_exp[i] = '(';
		else if (infix_exp[i] == '(')
			infix_exp[i] = ')';
	}
	//Convert biểu thức thành dạng Postfix
	// Ðẩy '(' lên stack
	push('(');
	// Thêm ')' vào biểu thức Infix
	strcat(infix_exp, ")");
	i = 0;
	j = 0;
	// Khai báo trước vòng lặp
	item = infix_exp[i];
	// Chạy vòng lặp cho đến khi kết thúc biểu thức Infix
	while (item != '\0')
	{
		if (item == '(')
		{
			push(item);
		}
		else if (isdigit(item) || isalpha(item))
		{
			// Thêm ký hiệu toán hạng cho biểu thức postfix
			prefix_exp[j] = item;
			j++;
		}
		else if (isOperator(item) == 1)
		{
			// Pop tất cả toán tử Precendence (có độ ưu tiên) cao hơn và thêm chúng vào biểu thức Postfix
			x = pop();
			while (isOperator(x) == 1 && Precedence(x) >= Precedence(item))
			{
				prefix_exp[j] = x;
				j++;
				x = pop();
			}
			// Push ký tự toán tử cuối cùng của Pop lên Stack
			push(x);
			// Push ký tự toán tử hiện tại lên Stack
			push(item);
		}
		// Nếu ký tự hiện tại là ')' thì tiếp tục Pop cho đến khi gặp '('
		else if (item == ')')
		{
			x = pop();
			while (x != '(')
			{
				prefix_exp[j] = x;
				j++;
				x = pop();
			}
		}
		else
		{
			// Kiểm tra nếu ký tự hiện tại không phải là toán hạng mà không có '(' và ')' hoặc không phải là toán tử
			printf("\nInvalid infix Expression.\n");
			break;
		}
		i++;
		// Chuyển đén ký tự tiếp theo của biểu thức Infix
		item = infix_exp[i];
	} //Kết thúc vòng lặp while
	if (top > 0)
		printf("\n Invalid infix Expression.");
	prefix_exp[j] = '\0';
	// Ðảo ngược biểu thức prefix
	pos = 0;
	len = strlen(prefix_exp);
	for (k = len - 1; k >= 0; k--)
	{
		rev[pos] = prefix_exp[k];
		pos++;
	}
	rev[pos] = '\0';
	strcpy(prefix_exp, rev);
}

//Hàm main
int main()
{
	// Khai báo chuỗi Infix và chuỗi prefix
	char infix[size], prefix[size];
	printf("Nhap bieu thuc Infix: ");
	gets(infix);
	// Hàm gọi convert
	InfixToPrefix(infix, prefix);
	printf("Bieu thuc Prefix la: ");
	// In ra biểu thức Prefix
	puts(prefix);
}