#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h> /* содержит объявления для errno */

#define USERS_FOLDER "users/"

int user_exist(char *name)// check user
{
    int n = strlen(USERS_FOLDER) + strlen(name) + 1;
    char path[n];
    path[0] = '\x00';

    strcat(path, USERS_FOLDER);
    strcat(path, name);
    puts(path);

    struct stat buff;
    if(stat(path, &buff) == 0)
    {
        return 1;
    }
    return 0;
}

int sign_in()
{
    char name[17];
    char password[17];

    printf("enter <login>\n");
    fgets(name, 16, stdin);

    printf("enter <password>\n");
    fgets(password, 16, stdin);

    int n = strlen(name);
    name[n-1]='\x00';
    n = strlen(password);
    password[n-1]='\x00';

    n = strlen(USERS_FOLDER) + strlen(name) + 1;
    char path[n];
    path[0] = '\x00';
    strcat(path, USERS_FOLDER);
    strcat(path, name);
    FILE *my_file;
    
    if(user_exist(name) == 0)
    {
        printf("No such user\n");
        return 0;
    }
   
    int a = strlen(path) + strlen("/password");
    char pass_path[a];
    pass_path[0] = '\x00';

    strcat(pass_path, path);
    strcat(pass_path, "/password");

    my_file = fopen(pass_path, "r");
    char check_pass[17];
    fgets(check_pass, 16, my_file);
    int i = 0;
    int equal = 1;
    while(check_pass[i] != 0x0 || password[i] != 0x0){
        if(check_pass[i] != password[i])equal = 0;
        i++;
    }
    if(equal){
        printf("Welcome home\n");
        return 1; // сделать папку с планетками (x, y) матрицаб на каждой там бункеры с паролями, рандомная генерация ролла с пушками для убийства других плане
                // можно прыгать рандомно, можно по координатам, которые знаешь, занять плнету можно, если ты прилетел на нее первый и поставил свой пароль
                // взрывая чужую планету можнон получить секрет взорвавшегося(пароль от планеты) ++сделать планету pooper++
                // 
    }
    printf("Wrong password\n");
    return 0;


}

int registration()
{   
    char name[17];
    char password[17];

    printf("enter <login>\n");
    fgets(name, 16, stdin);

    printf("enter <password>\n");
    fgets(password, 16, stdin);

    int n = strlen(name);
    name[n-1]='\x00';
    n = strlen(password);
    password[n-1]='\x00';

    if(user_exist(name) == 1)
    {   

        printf("Choose another login\n");
        return 0;
    } 
 
    n = strlen(USERS_FOLDER) + strlen(name) + 1;
    char path[n];
    path[0] = '\x00';

    strcat(path, USERS_FOLDER);
    strcat(path, name);
    FILE *my_file;
    mkdir(path, 0700);
    int a = strlen(path) + strlen("/password");
    char pass_path[a];
    pass_path[0] = '\x00';
    strcat(pass_path, path);
    strcat(pass_path, "/password");
    my_file = fopen(pass_path, "w");
    if(my_file == NULL)
    {
        perror("sorry your file cant't be opened:");
        return 0 ;
    } 

    fputs(password, my_file);
    fclose(my_file);
    printf("Success");
    
    return 1;
    
}

// void status()
// {
//     printf("You're inside\nNow you can continue your adventure(press h for help)\n");
//     int choice2;
//     choice2 = getc(stdin);
//     switch(choice2){
//         case 'h':
//             printf("1 - random jump\n2 - jump in coordinates\n3 - weapon\n4 - exit");
//             break;
//         case '1':
//             jump_random()
//              break;
//         // case '2':
//         //     break;
//         // case '3':
//         //     break;
//         // case '4':
//         //     break;
//     }
// }


int main(void)
{  
    int choice1;
    int trash;
    int status_reg = 0;
    while(1)
    {
        if(status_reg == 0){
            printf("sign in / regisration / exit? 1/2/0\n");
            choice1 = getc(stdin);
            while(trash != 0xa){
                trash = getc(stdin);
            }
            while(choice1 != '1' && choice1 != '2' && choice1 != '0'){
                printf("Wrong input, try 1 or 2 maybe??\n");
                choice1 = getc(stdin);
            }
            switch(choice1)
            {
                case '1': 
                    status_reg = sign_in();
                    break;
                case '2': 
                    status_reg = registration();
                    break;
                case '0':
                    goto end;
            }
        }

        //if(status_reg == 1)status();
    }
    
end: 
printf("bye\n");   
return 0;
}