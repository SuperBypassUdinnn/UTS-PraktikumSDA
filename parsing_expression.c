#include <stdio.h>

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
            printf("\n\033[1mTerimakasih telah menggunakan Kalkulator Infix, Postfix, dan Prefix.\033[0m\n");
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
                {
                    printf("%d. %s\n", i + 1, postpre_menu[i]);
                }
    
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
                {
                    printf("%d. %s\n", i + 1, postpre_menu[i]);
                }

                printf("\nPilihlah : ");
                pilihan = charTanpaBuffer();
                
                switch (pilihan)
                {
                    case '1':
                    // kode untuk Infix ke prefix
                    break;
                    
                    case '2':
                    // kode untuk prefix ke Infix
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
                {
                    printf("%d. %s\n", i + 1, postpre_menu[i]);
                }

                printf("\nPilihlah : ");
                pilihan + charTanpaBuffer();
                
                switch (pilihan)
                {
                    case '1':
                    // kode untuk Postfix ke prefix
                    break;
                    
                    case '2':
                    // kode untuk prefix ke Postfix
                    break;
                }
                clearTerminal();
            } while(pilihan != '3');
            break;
        }
    }
}
