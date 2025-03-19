#include <stdio.h>

//memastikan input berupa angka
int inputAngka(int* alamatVariabel){
    int flag = 0;

    if (scanf("%d", alamatVariabel ) == 1 || getchar() == '\n')
        flag = 1;

    return flag;
}

int main()
{
    int pilihan;
    while (1)
    {
        printf("\033[2J\033[H");
        
        printf("-----------------------------------------------------------\n");
        printf("\033[1m~ Selamat datang di Kalkulator Infix, Postfix, dan Prefix ~ \033[0m\n");
        printf("-----------------------------------------------------------\n");
        
        char *main_menu[4] = {"Infix dan Postfix", "Infix dan Prefix", "Postfix dan Prefix", "Exit"};
        
        for (int i = 0; i < 4; i++)
        {
            printf("%d. %s\n", i + 1, main_menu[i]);
        }
        
        printf("\nPilihlah : ");
        if (!inputAngka(&pilihan))
        {
            printf("\033[2J\033[H");
            continue;
        }
        
        if (pilihan == 4)
        {
            printf("\n\033[1mTerimakasih telah menggunakan Kalkulator Infix, Postfix, dan Prefix.\033[0m\n");
            break;
        }
        
        printf("\033[2J\033[H");
        
        switch (pilihan)
        {
            case 1:
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
                if (!inputAngka(&pilihan))
                {
                    printf("\033[2J\033[H");
                    continue;
                }
                
                switch (pilihan)
                {
                    case 1:
                        // kode untuk Infix ke Postfix
                        break;
                    
                    case 2:
                    // kode untuk Postfix ke Infix
                        break;
                    
                    default:
                        break;
                }
                printf("\033[2J\033[H");
            } while(pilihan != 3);
            break;

            case 2:
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
                    if (!inputAngka(&pilihan))
                    {
                        printf("\033[2J\033[H");
                        continue;
                    }
                    
                    switch (pilihan)
                    {
                        case 1:
                            // kode untuk Infix ke prefix
                            break;
                        
                        case 2:
                        // kode untuk prefix ke Infix
                            break;
                        
                        default:
                            break;
                    }
                    printf("\033[2J\033[H");
                } while(pilihan != 3);
                break;
            
            case 3:
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
                    if (!inputAngka(&pilihan))
                    {
                        printf("\033[2J\033[H");
                        continue;
                    }
                    
                    switch (pilihan)
                    {
                        case 1:
                            // kode untuk postfix ke prefix
                            break;
                        
                        case 2:
                        // kode untuk prefix ke postfix
                            break;
                        
                        default:
                            break;
                    }
                    printf("\033[2J\033[H");
                } while(pilihan != 3);
                break;
            
            default:
                break;
        }
    }
}
