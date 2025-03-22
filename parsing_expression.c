#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

#ifdef _WIN32
#include <conio.h>
#elif __linux__ || __unix__ || __APPLE__
#include <termios.h>
#include <unistd.h>
#else
#error "Sistem operasi tidak didukung"
#endif

char charTanpaBuffer()
{
    char input;
#ifdef _WIN32
    input = _getch();
#elif __linux__ || __unix__ || __APPLE__
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    input = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    return input;
}

void clearTerminal()
{
    printf("\033[2J\033[H");
}

typedef struct
{
    int top;
    char *items[MAX_SIZE];
} Stack;

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

int isFull(Stack *stack)
{
    return stack->top == MAX_SIZE - 1;
}

void push(Stack *stack, char *item)
{
    if (isFull(stack))
    {
        printf("Stack penuh\n");
        return;
    }
    stack->items[++stack->top] = item;
}

char *pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack kosong\n");
        return NULL;
    }
    return stack->items[stack->top--];
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

char *infixToPostfix(char *infix)
{
    Stack *stack = createStack();
    char *postfix = (char *)malloc((strlen(infix) + 1) * sizeof(char));
    int k = 0;

    for (int i = 0; i < strlen(infix); i++)
    {
        char ch = infix[i];

        if (isalnum(ch))
        {
            postfix[k++] = ch;
        }
        else if (ch == '(')
        {
            char *op = (char *)malloc(2 * sizeof(char));
            op[0] = ch;
            op[1] = '\0';
            push(stack, op);
        }
        else if (ch == ')')
        {
            while (!isEmpty(stack) && *(stack->items[stack->top]) != '(')
            {
                postfix[k++] = *(pop(stack));
            }
            free(pop(stack));
        }
        else if (isOperator(ch))
        {
            while (!isEmpty(stack) && precedence(*(stack->items[stack->top])) >= precedence(ch))
            {
                postfix[k++] = *(pop(stack));
            }
            char *op = (char *)malloc(2 * sizeof(char));
            op[0] = ch;
            op[1] = '\0';
            push(stack, op);
        }
    }

    while (!isEmpty(stack))
    {
        char *temp = pop(stack);
        postfix[k++] = *temp;
        free(temp);
    }

    postfix[k] = '\0';
    free(stack);
    return postfix;
}

char *postfixToInfix(char *postfix)
{
    Stack *stack = createStack();

    for (int i = 0; i < strlen(postfix); i++)
    {
        char ch = postfix[i];

        if (isalnum(ch))
        {
            char *operand = (char *)malloc(2 * sizeof(char));
            operand[0] = ch;
            operand[1] = '\0';
            push(stack, operand);
        }
        else if (isOperator(ch))
        {
            char *op2 = pop(stack);
            char *op1 = pop(stack);
            char *infix = (char *)malloc((strlen(op1) + strlen(op2) + 4) * sizeof(char));
            sprintf(infix, "(%s%c%s)", op1, ch, op2);
            push(stack, infix);
            free(op1);
            free(op2);
        }
    }

    char *result = pop(stack);
    free(stack);
    return result;
}

char *reverse(char *str)
{
    int len = strlen(str);
    char *rev = (char *)malloc((len + 1) * sizeof(char));
    for (int i = 0; i < len; i++)
    {
        rev[i] = str[len - i - 1];
    }
    rev[len] = '\0';
    return rev;
}

void replaceBrackets(char *expr)
{
    for (int i = 0; i < strlen(expr); i++)
    {
        if (expr[i] == '(')
            expr[i] = ')';
        else if (expr[i] == ')')
            expr[i] = '(';
    }
}

char *infixToPrefix(char *infix)
{
    char *rev = reverse(infix);
    replaceBrackets(rev);
    char *postfix = infixToPostfix(rev);
    char *prefix = reverse(postfix);
    free(rev);
    free(postfix);
    return prefix;
}

char *prefixToInfix(char *prefix)
{
    Stack *stack = createStack();
    int length = strlen(prefix);

    for (int i = length - 1; i >= 0; i--)
    {
        char ch = prefix[i];

        if (isalnum(ch))
        {
            char *operand = (char *)malloc(2 * sizeof(char));
            operand[0] = ch;
            operand[1] = '\0';
            push(stack, operand);
        }
        else if (isOperator(ch))
        {
            char *operand1 = pop(stack);
            char *operand2 = pop(stack);
            char *infix = (char *)malloc((strlen(operand1) + strlen(operand2) + 4) * sizeof(char));
            sprintf(infix, "(%s%c%s)", operand1, ch, operand2);
            push(stack, infix);
            free(operand1);
            free(operand2);
        }
    }

    char *result = pop(stack);
    free(stack);
    return result;
}

char *postfixToPrefix(char *postfix)
{
    Stack *stack = createStack();
    int length = strlen(postfix);

    for (int i = 0; i < length; i++)
    {
        char ch = postfix[i];

        if (isalnum(ch))
        {
            char *operand = (char *)malloc(2 * sizeof(char));
            operand[0] = ch;
            operand[1] = '\0';
            push(stack, operand);
        }
        else if (isOperator(ch))
        {
            char *operand2 = pop(stack);
            char *operand1 = pop(stack);
            char *prefix = (char *)malloc((strlen(operand1) + strlen(operand2) + 2) * sizeof(char));
            sprintf(prefix, "%c%s%s", ch, operand1, operand2);
            push(stack, prefix);
            free(operand1);
            free(operand2);
        }
    }

    char *result = pop(stack);
    free(stack);
    return result;
}

char *prefixToPostfix(char *prefix)
{
    Stack *stack = createStack();
    int length = strlen(prefix);

    for (int i = length - 1; i >= 0; i--)
    {
        char ch = prefix[i];

        if (isalnum(ch))
        {
            char *operand = (char *)malloc(2 * sizeof(char));
            operand[0] = ch;
            operand[1] = '\0';
            push(stack, operand);
        }
        else if (isOperator(ch))
        {
            char *operand1 = pop(stack);
            char *operand2 = pop(stack);
            char *postfix = (char *)malloc((strlen(operand1) + strlen(operand2) + 2) * sizeof(char));
            sprintf(postfix, "%s%s%c", operand1, operand2, ch);
            push(stack, postfix);
            free(operand1);
            free(operand2);
        }
    }

    char *result = pop(stack);
    free(stack);
    return result;
}

int main()
{
    int pilihan;
    while (1)
    {
        clearTerminal();

        printf("-----------------------------------------------------------\n");
        printf("\033[1m~ Selamat datang di Kalkulator Infix, Postfix, dan Prefix ~ \033[0m\n");
        printf("-----------------------------------------------------------\n");

        char *main_menu[4] = {"Infix dan Postfix", "Infix dan Prefix", "Postfix dan Prefix", "Exit"};

        for (int i = 0; i < 4; i++)
        {
            printf("%d. %s\n", i + 1, main_menu[i]);
        }

        printf("\nPilihlah : ");
        pilihan = charTanpaBuffer();

        if (pilihan == '4')
        {
            clearTerminal();
            printf("--------------------------------------------------------------------\n");
            printf("\033[1mTerimakasih telah menggunakan Kalkulator Infix, Postfix, dan Prefix.\033[0m\n");
            printf("--------------------------------------------------------------------\n");
            break;
        }

        clearTerminal();

        switch (pilihan)
        {
        case '1':
            do
            {
                clearTerminal();
                printf("---------------------------------\n");
                printf("\033[1m~ Kalkulator Infix dan Postfix ~\033[0m\n");
                printf("---------------------------------\n");

                char *postpre_menu[3] = {"Infix ke Postfix", "Postfix ke Infix", "Kembali"};
                for (int i = 0; i < 3; i++)
                    printf("%d. %s\n", i + 1, postpre_menu[i]);

                printf("\nPilihlah : ");
                pilihan = charTanpaBuffer();

                switch (pilihan)
                {
                case '1':
                    clearTerminal();
                    printf("--------------------------------\n");
                    printf("\033[1m~ Kalkulator Infix ke Postfix ~\033[0m\n");
                    printf("--------------------------------\n");

                    char infix[MAX_SIZE];
                    printf("\nEkspresi Infix: ");
                    scanf("%[^\n]", infix);
                    getchar();
                    char *postfixResult = infixToPostfix(infix);
                    printf("Ekspresi Postfix: %s\n", postfixResult);
                    free(postfixResult);

                    printf("\n\n\033[1mTekan tombol apapun untuk kembali\033[1m");
                    charTanpaBuffer();
                    break;

                case '2':
                    clearTerminal();
                    printf("--------------------------------\n");
                    printf("\033[1m~ Kalkulator Postfix ke Infix ~\033[0m\n");
                    printf("--------------------------------\n");

                    char postfix[MAX_SIZE];
                    printf("\nEkspresi Postfix: ");
                    scanf("%[^\n]", postfix);
                    getchar();
                    char *infixResult = postfixToInfix(postfix);
                    printf("Ekspresi Infix: %s\n", infixResult);
                    free(infixResult);

                    printf("\n\n\033[1mTekan tombol apapun untuk kembali\033[1m");
                    charTanpaBuffer();
                    break;
                case '3':
                    break;
                default:
                    printf("\n\nPilihan tidak valid. Tekan tombol apapun untuk coba lagi.");
                    charTanpaBuffer();
                    break;
                }
            } while (pilihan != '3');
            break;

        case '2':
            do
            {
                clearTerminal();
                printf("---------------------------------\n");
                printf("\033[1m~ Kalkulator Infix dan Prefix ~\033[0m\n");
                printf("---------------------------------\n");

                char *postpre_menu[3] = {"Infix ke Prefix", "Prefix ke Infix", "Kembali"};
                for (int i = 0; i < 3; i++)
                    printf("%d. %s\n", i + 1, postpre_menu[i]);

                printf("\nPilihlah : ");
                pilihan = charTanpaBuffer();

                switch (pilihan)
                {
                case '1':
                    clearTerminal();
                    printf("--------------------------------\n");
                    printf("\033[1m~ Kalkulator Infix ke Prefix ~\033[0m\n");
                    printf("--------------------------------\n");

                    char infix[MAX_SIZE];
                    printf("\nEkspresi Infix: ");
                    scanf("%[^\n]", infix);
                    getchar();
                    char *prefixResult = infixToPrefix(infix);
                    printf("Ekspresi Prefix: %s\n", prefixResult);
                    free(prefixResult);

                    printf("\n\n\033[1mTekan tombol apapun untuk kembali\033[1m");
                    charTanpaBuffer();
                    break;

                case '2':
                    clearTerminal();
                    printf("--------------------------------\n");
                    printf("\033[1m~ Kalkulator Prefix ke Infix ~\033[0m\n");
                    printf("--------------------------------\n");

                    char prefix[MAX_SIZE];
                    printf("\nEkspresi Prefix: ");
                    scanf("%[^\n]", prefix);
                    getchar();
                    char *infixResult = prefixToInfix(prefix);
                    printf("Ekspresi Infix: %s\n", infixResult);
                    free(infixResult);

                    printf("\n\n\033[1mTekan tombol apapun untuk kembali\033[1m");
                    charTanpaBuffer();
                    break;
                case '3':
                    break;
                default:
                    printf("\n\nPilihan tidak valid. Tekan tombol apapun untuk coba lagi.");
                    charTanpaBuffer();
                    break;
                }
            } while (pilihan != '3');
            break;

        case '3':
            do
            {
                clearTerminal();
                printf("---------------------------------\n");
                printf("\033[1m~ Kalkulator Postfix dan Prefix ~\033[0m\n");
                printf("---------------------------------\n");

                char *postpre_menu[3] = {"Postfix ke Prefix", "Prefix ke Postfix", "Kembali"};
                for (int i = 0; i < 3; i++)
                    printf("%d. %s\n", i + 1, postpre_menu[i]);

                printf("\nPilihlah : ");
                pilihan = charTanpaBuffer();

                switch (pilihan)
                {
                case '1':
                    clearTerminal();
                    printf("----------------------------------\n");
                    printf("\033[1m~ Kalkulator Postfix ke Prefix ~\033[0m\n");
                    printf("----------------------------------\n");

                    char postfix[MAX_SIZE];
                    printf("\nEkspresi Postfix: ");
                    scanf("%[^\n]", postfix);
                    getchar();
                    char *prefixResult = postfixToPrefix(postfix);
                    printf("Ekspresi Prefix: %s\n", prefixResult);
                    free(prefixResult);

                    printf("\n\n\033[1mTekan tombol apapun untuk kembali\033[1m");
                    charTanpaBuffer();
                    break;

                case '2':
                    clearTerminal();
                    printf("----------------------------------\n");
                    printf("\033[1m~ Kalkulator Prefix ke Postfix ~\033[0m\n");
                    printf("----------------------------------\n");

                    char prefix[MAX_SIZE];
                    printf("\nEkspresi Prefix: ");
                    scanf("%[^\n]", prefix);
                    getchar();
                    char *postfixResult = prefixToPostfix(prefix);
                    printf("Ekspresi Postfix: %s\n", postfixResult);
                    free(postfixResult);

                    printf("\n\n\033[1mTekan tombol apapun untuk kembali\033[1m");
                    charTanpaBuffer();
                    break;
                case '3':
                    break;
                default:
                    printf("\n\nPilihan tidak valid. Tekan tombol apapun untuk coba lagi.");
                    charTanpaBuffer();
                    break;
                }
            } while (pilihan != '3');
            break;
        default:
            printf("\n\nPilihan tidak valid. Tekan tombol apapun untuk coba lagi.");
            charTanpaBuffer();
            break;
        }
    }
}
