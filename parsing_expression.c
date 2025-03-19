#include <stdio.h>

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
        if (scanf("%d", &pilihan) != 1)
        {
            printf("Pilihan harus berupa angka.\n");
            while (getchar() != '\n')
                ;
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
            printf("--------------------------------\n");
            printf("\033[1m~ Kalkulator Infix dan Postfix ~\033[0m\n");
            printf("--------------------------------\n");

            char *inpost_menu[3] = {"Infix ke Postfix", "Postfix ke Infix", "Kembali"};
            for (int i = 0; i < 3; i++)
            {
                printf("%d. %s\n", i + 1, inpost_menu[i]);
            }

            int pilihmode1;
            printf("\nPilihlah : ");
            scanf("%d", &pilihmode1);

            switch (pilihmode1)
            {
            case 1:
                // kode untuk infix ke postfix
                break;

            case 2:
                // kode untuk postfix ke infix
                break;

            case 3:
                break;

            default:
                printf("Pilihan Tidak valid");
                break;
            }

            break;

        case 2:
            printf("-------------------------------\n");
            printf("\033[1m~ Kalkulator Infix dan Prefix ~\033[0m\n");
            printf("-------------------------------\n");

            char *inpre_menu[3] = {"Infix ke Prefix", "Prefix ke Infix", "Kembali"};
            for (int i = 0; i < 3; i++)
            {
                printf("%d. %s\n", i + 1, inpre_menu[i]);
            }

            int pilihmode2;
            printf("\nPilihlah : ");
            scanf("%d", &pilihmode2);

            switch (pilihmode2)
            {
            case 1:
                // kode untuk infix ke prefix
                break;

            case 2:
                // kode untuk prefix ke infix
                break;

            case 3:
                break;

            default:
                printf("Pilihan Tidak valid");
                break;
            }

            break;

        case 3:
            printf("---------------------------------\n");
            printf("\033[1m~ Kalkulator Postfix dan Prefix ~\033[0m\n");
            printf("---------------------------------\n");

            char *postpre_menu[3] = {"Postfix ke Prefix", "Prefix ke Postfix", "Kembali"};
            for (int i = 0; i < 3; i++)
            {
                printf("%d. %s\n", i + 1, postpre_menu[i]);
            }

            int pilihmode3;
            printf("\nPilihlah : ");
            scanf("%d", &pilihmode3);

            switch (pilihmode3)
            {
            case 1:
                // kode untuk postfix ke prefix
                break;

            case 2:
                // kode untuk prefix ke postfix
                break;

            case 3:
                break;

            default:
                printf("Pilihan Tidak valid");
                break;
            }

            break;

        default:
            printf("Pilihan Tidak valid");
            break;
        }
    }
}

