#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h> /* содержит объявления для errno */
#include <time.h>
#include <dirent.h>

#define USERS_FOLDER "users/"

void janitor()
{
    int trash;
    while(trash != 0xa)
    {
        trash = getc(stdin);
    }
}
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
int check_password(char *check_pass, char *password)
{   
    int i = 0;
    while(check_pass[i] != 0x0 || password[i] != 0x0){
        if(check_pass[i] != password[i])return 0;
        i++;
    }
    return 1;
}
char *sign_in()
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
        return '\x00';
    }
   
    int a = strlen(path) + strlen("/password");
    char pass_path[a];
    pass_path[0] = '\x00';

    strcat(pass_path, path);
    strcat(pass_path, "/password");

    my_file = fopen(pass_path, "r");
    char check_pass[17];
    fgets(check_pass, 16, my_file);
    int equal = 1;
    equal = check_password(check_pass, password);
    if(equal){
        printf("Welcome\n");
        char *str = (char *)malloc(sizeof(path));
        strcat(str, path);
    return str; 
    }
    printf("Wrong password\n");
    return '\x00';


}

char *registration()
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
        return '\x00';
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
        perror("sorry your file can't be opened:");
        return '\x00';
    } 

    fputs(password, my_file);
    fclose(my_file);
    printf("Success\n");
    
    char *str = (char *)malloc(sizeof(path));
    strcat(str, path);
    return str;
    
}

void put_in_the_cell()
{
    printf("Enter your login\n");
    char name[17];
    janitor();
    fgets(name, 16, stdin);
    int n = strlen(name);
    name[n-1]='\x00';
    if(user_exist(name) == 0)
    {   
        printf("No such user\n");
        return;
    } 
    n = strlen(USERS_FOLDER) + strlen(name) + strlen("/cells/") + 1;
    char path[n];
    path[0] = '\x00';

    strcat(path, USERS_FOLDER);
    strcat(path, name);
    strcat(path, "/cells/");
    mkdir(path, 0700);
    FILE *my_file;

    printf("what would you like to put in a bank cell?\n");
    char sample_thing[17];
    fgets(sample_thing, 16, stdin);
    sample_thing[16] = '\x00';
    int a = strlen(path) + strlen(sample_thing);

    char cell_path[a];
    cell_path[0] = '\x00';
    strcat(cell_path, path);
    strcat(cell_path, sample_thing);
    my_file = fopen(cell_path, "w");
    if(my_file == NULL)
    {
        perror("sorry your cell unavailable: ");
        return;
    } 

    fputs(sample_thing, my_file);
    fclose(my_file);
    printf("your property is in a cell and is completely safe\n");
    return;
}
void visit_bank_vault(char *path)
{
    int n = sizeof(path) + sizeof("/cells") + 1;
    char cell_path[n];
    strcat(cell_path, path);
    strcat(cell_path, "/cells");
    DIR *dir;
    struct dirent *entry;

    dir = opendir(cell_path);
    if (!dir) {
        perror("diropen");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return;
}

int status(char *path)
{
    printf("You're inside\n(press h for help)\n");
    int choice2;
    while(1)
    {
        printf("1 - put something in the bank cell\n2 - visit bank vault\n4 - exit\n");
    choice2 = getc(stdin);
    switch(choice2){
         case '1':
            put_in_the_cell();
             break;
         case '2':
            visit_bank_vault(path);
             break;
        // case '3':
        //     break;
         case '4':
            return 0;
             break;
    }
    }
}

int main(void)
{  
    int choice1;
    char path[128];
    path[0] = '\x00';
    while(1)
    {
        if(path[0] == '\x00'){
            printf("sign in / regisration / exit? 1/2/0\n");
            choice1 = getc(stdin);
            janitor();
            while(choice1 != '1' && choice1 != '2' && choice1 != '0'){
                printf("Wrong input, try 1 or 2 maybe??\n");
                janitor();
                choice1 = getc(stdin);
            }
            switch(choice1)
            {
                case '1': 
                    strcat(path, sign_in());
                    break;
                case '2': 
                    strcat(path, registration());
                    break;
                case '0':
                    goto end;
            }
        }

        if(path[0] != '\x00')status(path);

    }
    
end: 
printf("bye\n");   
return 0;
}