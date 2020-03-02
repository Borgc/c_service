#include <string.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h> /* содержит объявления для errno */
#include <time.h>
#include <dirent.h>
#include <time.h>

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
        return NULL;
    }
   
    int a = strlen(path) + strlen("/password");
    char pass_path[a];
    pass_path[0] = '\x00';

    strcat(pass_path, path);
    strcat(pass_path, "/password");

    my_file = fopen(pass_path, "r");
    char check_pass[17];
    fgets(check_pass, 16, my_file);
    int equal = check_password(check_pass, password);
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
    int a = strlen(path) + strlen("/password") + 1;
    char pass_path[a];
    pass_path[0] = '\x00';
    strcat(pass_path, path);
    strcat(pass_path, "/password");
    my_file = fopen(pass_path, "w");
    printf("%s\n", pass_path);
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

void put_secret()
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

    printf("Enter planet password\n");
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
        perror("sorry your vault unavailable: ");
        return;
    } 

    fputs(sample_thing, my_file);
    fclose(my_file);
    printf("Planet under control now\n");
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
int planet_exist(char *coor)
{
    int n = strlen("planets/") + strlen(coor) + 1;
    char path[n];
    path[0] = '\x00';

    strcat(path, "planets/");
    strcat(path, coor);
    puts(path);

    struct stat buff;
    if(stat(path, &buff) == 0)
    {
        return 1;
    }
    return 0;
}

void create_planet(char *coor)
{
    srand(time(NULL));
    int a = strlen("planet/") + strlen("coor/") + strlen("description");
    char path[a];
    path[0] = '\x00';
    strcat(path, "planet/");
    strcat(path, "coor/");
    strcat(path, "description");
    FILE *my_file;
    my_file = fopen(path, "w");
    if(my_file == NULL)
    {
        perror("sorry your planet unavailable: ");
        return;
    } 

    int n = 0;          //CONTINUE HERE think about planet abilities and realization**watch "space.txt"**
    char desc; 
    char buffer_string[100];
    while(n <= 50){
    n = rand() % 101;      
    if(n <= 20){desc = 'e';} // empty space
    else if(n <= 40){desc = 'b';} // black hole
    else if(n <= 50){desc = 's';} // space pirates
    else if(n <= 60){desc = 'p';} // simple planet
    else if(n <= 80){desc = 'g';} // planet with a gun
    else if(n <= 99){desc = 'i';} // invisible planet with a gun
    else if(n == 100){desc = 'x';} //invisible + death star

    // #define GUN 0b100
    // #define INVIS 0b010
    // #define DEATHSTAR 0b001
    switch(desc){
        case 'e':
            printf("empty space\n");
            break;
        case 'b':
            printf("black hole\n");
            break;
        case 's':
            printf("space pirates\n");
        case 'p':
            printf("simple planet\n");
            printf("Give a name for your planet:");
            fgets(buffer_string, 99, stdin);
            janitor();
            fputs(buffer_string, my_file);
            printf("Give a password for your planet, don't forget it:");
            fgets(buffer_string, 99, stdin);
            janitor();
            fputs(buffer_string, my_file);
            printf("Give a description for your planet:");
            fgets(buffer_string, 99, stdin);
            janitor();
            fputs(buffer_string, my_file);
            //fputs("\n", my_file);
            break;
        case 'g':
            printf("planet with a gun\n");
            printf("Give a name for your planet:");
            fgets(buffer_string, 99, stdin);
            janitor();
            fputs(buffer_string, my_file);
            printf("Give a password for your planet, don't forget it:");
            fgets(buffer_string, 99, stdin);
            janitor();
            fputs(buffer_string, my_file);
            printf("Give a description for your planet:");
            fgets(buffer_string, 99, stdin);
            janitor();
            fputs(buffer_string, my_file);
            //fputs(GUN, my_file);
            break;
        case 'i':
            printf("invisible planet with a gun\n");
            printf("Give a name for your planet:");
            fgets(buffer_string, 99, stdin);
            janitor();
            fputs(buffer_string, my_file);
            printf("Give a password for your planet, don't forget it:");
            fgets(buffer_string, 99, stdin);
            janitor();
            fputs(buffer_string, my_file);
            printf("Give a description for your planet:");
            fgets(buffer_string, 99, stdin);
            janitor();
            fputs(buffer_string, my_file);
            // //fputs(GUN + INVIS, my_file);
            break;
        case 'x':
            printf("invisible + death star\n");
            printf("Give a name for your planet:");
            fgets(buffer_string, 99, stdin);
            janitor();
            fputs(buffer_string, my_file);
            printf("Give a password for your planet, don't forget it:");
            fgets(buffer_string, 99, stdin);
            janitor();
            fputs(buffer_string, my_file);
            printf("Give a description for your planet:");
            fgets(buffer_string, 99, stdin);
            janitor();
            fputs(buffer_string, my_file);
            // uint8_t opts = GUN | INVIS | DEATHSTAR;
            // //fputs(GUN + INVIS + DEATHSTAR, my_file);
            // fprintf(my_file, "%d", opts);
            break;
    }
    }
}

const char* leeters = "ABCDEFGHIJKLMNOPQRSTXYZ";

void teleport()
{
    srand(time(NULL));
    char coor[5];
    coor[4] = '\x00';
    coor[0] = leeters[rand() % 26];
    coor[1] = rand() % 10 + 48;
    coor[2] = leeters[rand() % 26];
    coor[3] = rand() % 10 + 48;
    printf("coor = %s\n", coor);
    if(planet_exist(coor)){
        return;
    } 
    create_planet(coor);
    return;

}
int status(char *path)
{
    printf("You're inside\n");
    int choice2;
    while(1)
    {
        printf("1 - teleport\n2 - visit my planet\n3 - watch my planets\n4 - help\n5 - exit\n");
    choice2 = getc(stdin);
    janitor();
    switch(choice2){
         case '1':
            teleport();
             break;
         case '2':
        //
             break;
        // case '3':
        //     break;
         case '4':
            printf("Teleport is a random jump to another planet or no, who knows\n");
            printf("Visit my planet - you are going to the planet on your spaceship\n");
            printf("Watch my planets ...\n");
         case '5':
            return 1;
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

        if(path[0] != '\x00')
        {
            if(status(path))
            {
                goto end;
            };
        }

    }
    
end: 
printf("bye\n");   
return 0;
}