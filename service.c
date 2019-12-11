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

void sign_in()
{
    char name[255];
    char password[255];

    printf("enter <login> <password>\n");
    fgets(name, 255, stdin);
    fgets(password, 255, stdin);

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
    

    if(user_exist(name) == 1)
    {   
        int a = strlen(path) + strlen("/password");
        char pass_path[a];
        pass_path[0] = '\x00';
        strcat(pass_path, path);
        strcat(pass_path, "/password");
        my_file = fopen(pass_path, "r");
        char check_pass[255];
        fgets(check_pass, 255, my_file);
        if(check_pass == password){
            return; // need to do smth with existance in your service, some menu or hero page
        }
        printf("Wrong password");
    } 

   /* n = strlen(USERS_FOLDER) + strlen(name) + 1;
    char path[n];
    path[0] = '\x00';
    strcat(path, USERS_FOLDER);
    strcat(path, name);*/


}
void registration()
{   
    char name[255];
    char password[255];

    printf("enter <login> <password>\n");
    fgets(name, 255, stdin);
    fgets(password, 255, stdin);

    int n = strlen(name);
    name[n-1]='\x00';
    n = strlen(password);
    password[n-1]='\x00';

    if(user_exist(name) == 1)
    {   

        printf("Choose another login");
        return;
    } 
    else {
        int n = strlen(USERS_FOLDER) + strlen(name) + 1;
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
            return;
        } 

        fprintf(my_file, "%s", password);
        printf("Success");
        
        return;
    }
}


int main(void)
{   

    printf("sign in / regisration? 1/2\n");
    char choice1;
    scanf("%c", &choice1);
    while(choice1 != '1' && choice1 != '2'){
        printf("Wrong input, try 1 or 2 maybe??\n");
        scanf("%c", &choice1);
    }
    switch(choice1)
    {
        case '1': 
            sign_in();
            break;
        case '2': 
            registration();
            break;
    }

return 0;
}