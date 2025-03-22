#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Platform Windows
#ifdef _WIN32
    #include <conio.h>
// Platform UNIX, Linux, dan Mac
#elif __linux__ || __unix__ || __APPLE__
    #include <termios.h>
    #include <unistd.h>
#else
    #error "Sistem operasi tidak didukung"
#endif

/* Fungsi untuk input char tanpa buffer 
   Berguna untuk buat opsi pilihan kepada user*/
char charTanpaBuffer()
{
    char input;
    #ifdef _WIN32
        input = _getch(); // input char tanpa buffer dan echo
    #elif __linux__ || __unix__ || __APPLE__
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);           // Simpan pengaturan terminal saat ini
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);         // Nonaktifkan mode kanonik dan echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Terapkan pengaturan baru

        input = getchar();                        // Ambil karakter dari input
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Kembalikan pengaturan terminal lama
    #endif
    
    return input;
}

// Membersihkan terminal
void clearTerminal(){
    printf("\033[2J\033[H");
}


// Struktur untuk stack
typedef struct {
    int top;
    char* items[MAX_SIZE];
} Stack;

// Fungsi untuk membuat stack baru
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

// Fungsi untuk mengecek apakah stack kosong
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Fungsi untuk mengecek apakah stack penuh
int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// Fungsi untuk menambahkan elemen ke stack
void push(Stack* stack, char* item) {
    if (isFull(stack)) {
        printf("Stack penuh\n");
        return;
    }
    stack->items[++stack->top] = item;
}

// Fungsi untuk menghapus elemen dari stack
char* pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack kosong\n");
        return NULL;
    }
    return stack->items[stack->top--];
}

// Fungsi untuk mengecek apakah karakter adalah operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

// Fungsi untuk mengkonversi ekspresi prefix ke infix
char* prefixToInfix(char* prefix) {
    Stack* stack = createStack();
    int length = strlen(prefix);

    // Membaca ekspresi prefix dari kanan ke kiri
    for (int i = length - 1; i >= 0; i--) {
        char ch = prefix[i];

        // Jika karakter adalah operand, push ke stack
        if (isalnum(ch)) {
            char* operand = (char*)malloc(2 * sizeof(char));
            operand[0] = ch;
            operand[1] = '\0';
            push(stack, operand);
        }
        // Jika karakter adalah operator, pop dua operand dari stack dan gabungkan dengan operator
        else if (isOperator(ch)) {
            char* operand1 = pop(stack);
            char* operand2 = pop(stack);
            char* infix = (char*)malloc((strlen(operand1) + strlen(operand2) + 4) * sizeof(char));
            sprintf(infix, "(%s%c%s)", operand1, ch, operand2);
            push(stack, infix);
            free(operand1);
            free(operand2);
        }
    }

    // Hasil akhir ada di top stack
    char* result = pop(stack);
    free(stack);
    return result;
}

// Fungsi untuk mengkonversi postfix ke prefix
char* postfixToPrefix(char* postfix) {
    Stack* stack = createStack();
    int length = strlen(postfix);

    // Baca postfix dari kiri ke kanan
    for (int i = 0; i < length; i++) {
        char ch = postfix[i];

        // Jika karakter adalah operand, push ke stack
        if (isalnum(ch)) {
            char* operand = (char*)malloc(2 * sizeof(char));
            operand[0] = ch;
            operand[1] = '\0';
            push(stack, operand);
        }
        // Jika karakter adalah operator, pop dua operand dan gabungkan dengan operator
        else if (isOperator(ch)) {
            char* operand2 = pop(stack);
            char* operand1 = pop(stack);
            char* prefix = (char*)malloc((strlen(operand1) + strlen(operand2) + 2) * sizeof(char));
            sprintf(prefix, "%c%s%s", ch, operand1, operand2);
            push(stack, prefix);
            free(operand1);
            free(operand2);
        }
    }

    // Hasil akhir ada di top stack
    char* result = pop(stack);
    free(stack);
    return result;
}

// Fungsi untuk mengkonversi prefix ke postfix
char* prefixToPostfix(char* prefix) {
    Stack* stack = createStack();
    int length = strlen(prefix);

    // Baca prefix dari kanan ke kiri
    for (int i = length - 1; i >= 0; i--) {
        char ch = prefix[i];

        // Jika karakter adalah operand, push ke stack
        if (isalnum(ch)) {
            char* operand = (char*)malloc(2 * sizeof(char));
            operand[0] = ch;
            operand[1] = '\0';
            push(stack, operand);
        }
        // Jika karakter adalah operator, pop dua operand dan gabungkan dengan operator
        else if (isOperator(ch)) {
            char* operand1 = pop(stack);
            char* operand2 = pop(stack);
            char* postfix = (char*)malloc((strlen(operand1) + strlen(operand2) + 2) * sizeof(char));
            sprintf(postfix, "%s%s%c", operand1, operand2, ch);
            push(stack, postfix);
            free(operand1);
            free(operand2);
        }
    }

    // Hasil akhir ada di top stack
    char* result = pop(stack);
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
        
        printf("\nPlihlah : ");
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
            do{
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
                    // kode untuk Infix ke Postfix
                    break;
                    
                    case '2':
                    // kode untuk Postfix ke Infix
                    break;
                }
                clearTerminal();
            } while(pilihan != '3');
            break;
            
            case '2':
            do{
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
                    // kode untuk Infix ke prefix
                    break;
                    
                    // Prefix ke Infix
                    case '2':
                    do{
                        clearTerminal();
                        printf("--------------------------------\n");
                        printf("\033[1m~ Kalkulator Prefix ke Infix ~\033[0m\n");
                        printf("--------------------------------\n");
                        
                        char prefix[MAX_SIZE];
                        printf("\nEkspresi Prefix: ");
                        scanf("%s", prefix);
                        char* infix = prefixToInfix(prefix);
                        printf("Ekspresi Infix: %s\n", infix);
                        printf("\n1. Lanjut");
                        printf("\n2. Kembali\n");
                        printf("\nPilihlah : ");
                        free(infix);
                        
                        pilihan = 0;
                        while (pilihan != '1' && pilihan != '2') pilihan = charTanpaBuffer();
                        } while(pilihan != '2');
                        
                    break;
                }
                clearTerminal();
            } while(pilihan != '3');
            break;
                
            case '3':
            do{
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
                    // Postfix ke Prefix
                    case '1':
                    do{
                        clearTerminal();
                        printf("----------------------------------\n");
                        printf("\033[1m~ Kalkulator Postfix ke Prefix ~\033[0m\n");
                        printf("----------------------------------\n");
                        
                        char postfix[MAX_SIZE];
                        printf("\nEkspresi Postfix: ");
                        scanf("%s", postfix);
                        char* prefix = postfixToPrefix(postfix);
                        printf("Ekspresi Prefix: %s\n", prefix);
                        printf("\n1. Lanjut");
                        printf("\n2. Kembali\n");
                        printf("\nPilihlah : ");
                        free(prefix);
                        
                        pilihan = 0;
                        while (pilihan != '1' && pilihan != '2') pilihan = charTanpaBuffer();
                        } while(pilihan != '2');
                    
                    break;
                    
                    // Prefix ke Postfix
                    case '2':
                    do{
                        clearTerminal();
                        printf("----------------------------------\n");
                        printf("\033[1m~ Kalkulator Prefix ke Postfix ~\033[0m\n");
                        printf("----------------------------------\n");
                        
                        char prefix[MAX_SIZE];
                        printf("\nEkspresi Prefix: ");
                        scanf("%s", prefix);
                        char* postfix = prefixToPostfix(prefix);
                        printf("Ekspresi Postfix: %s\n", postfix);
                        printf("\n1. Lanjut");
                        printf("\n2. Kembali\n");
                        printf("\nPilihlah : ");
                        free(postfix);
                        
                        pilihan = 0;
                        while (pilihan != '1' && pilihan != '2') pilihan = charTanpaBuffer();
                        } while(pilihan != '2');
                    
                    break;
                }
                clearTerminal();
            } while(pilihan != '3');
            break;
        }
    }
}
