#include <stdio.h>
#include <string.h>
#include <malloc.h>

#define LENGTH 100
#define COMPONENTS_NUMBER 3

typedef enum enum_menu {ADD = 1, FIND, SHOW, REMOVE, QUIT} menu;

typedef struct struct_subscriber {
    char lname[LENGTH];
    char fname[LENGTH];
    char tnumber[LENGTH];
} subscriber;

typedef void (*pset_function) (subscriber *const , const char *const, const unsigned);

void set_lname(subscriber *const, const char *const, const unsigned);
void set_fname(subscriber *const , const char *const, const unsigned);
void set_tnumber(subscriber *const, const char *const, const unsigned);
void copy_sub(subscriber *const, const subscriber *const);
void swap_sub(subscriber *const, subscriber *const);
void remove_rn(char *const);
void clear_buf();

int main()
{
    subscriber *pbook = NULL;
    unsigned book_size = 0;
    unsigned menu_choice = QUIT;

    do {
        printf("Enter the number: add(1), find(2), show(3), remove(4), quit(5)\n> ");
        if(scanf("%u", &menu_choice) == 0)
            menu_choice = QUIT;
        clear_buf();
        switch(menu_choice) {
            case ADD:
                book_size++;
                pbook = (subscriber *) realloc((void *) pbook, book_size * sizeof(subscriber));

                char input[LENGTH+2];
                char *messages[COMPONENTS_NUMBER] = {"Enter a last name\n> ", "Enter a first name\n> ", "Enter a telephone number\n> "};
                pset_function pset_functions[COMPONENTS_NUMBER] = {set_lname, set_fname, set_tnumber};

                for(int i = 0; i < COMPONENTS_NUMBER; i++) {
                    printf("%s", messages[i]);
                    fgets(input, LENGTH+2, stdin); //remove_rn(fgets(input, LENGTH+2, stdin));
                    remove_rn(input);
                    pset_functions[i](&pbook[book_size-1], input, LENGTH);
                }
            break;
            case FIND:
                printf("Enter a subscriber's last name for the search\n> ");
                char found_lname[LENGTH+2];
                fgets(found_lname, LENGTH+2, stdin);
                remove_rn(found_lname);
                for(int i = 0; i < book_size; i++)
                    if(strcmp(found_lname, pbook[i].lname) == 0)
                        printf("%s %s %s\n", pbook[i].lname, pbook[i].fname, pbook[i].tnumber);
            break;
            case SHOW:
                for(int i = 0; i < book_size; i++) {
                    printf("%s %s %s\n", pbook[i].lname, pbook[i].fname, pbook[i].tnumber);
                }
            break;
            case REMOVE:
                printf("Enter a subscriber's last name for removing\n> ");
                char removed_lname[LENGTH+2];
                fgets(removed_lname, LENGTH+2, stdin);
                remove_rn(removed_lname);
                for(int i = 0; i < book_size; i++)
                    if(strcmp(removed_lname, pbook[i].lname) == 0) {
                        swap_sub(&pbook[book_size-1], &pbook[i]);
                        book_size--;
                        pbook = (subscriber *) realloc((void *) pbook, book_size * sizeof(subscriber));
                    }
            break;
        }

    } while(menu_choice <= REMOVE);

    free(pbook);

    return 0;
}

void set_lname(subscriber *const sub, const char *const lname, const unsigned limit)
{
    strncpy(sub->lname, lname, (size_t) limit);
}

void set_fname(subscriber *const sub, const char *const fname, const unsigned limit)
{
    strncpy(sub->fname, fname, (size_t) limit);
}
void set_tnumber(subscriber *const sub, const char *const tnumber, const unsigned limit)
{
    strncpy(sub->tnumber, tnumber, (size_t) limit);
}

void copy_sub(subscriber *const dest, const subscriber *const src)
{
    strcpy(dest->lname, src->lname);
    strcpy(dest->fname, src->fname);
    strcpy(dest->tnumber, src->tnumber);
}

void swap_sub(subscriber *const dest, subscriber *const src)
{
    subscriber temp_sub;
    copy_sub(&temp_sub, src);
    copy_sub(src, dest);
    copy_sub(dest, &temp_sub);
}

void remove_rn(char *const str)
{
    str[strcspn(str, "\r\n")] = '\0';
}

void clear_buf()
{
    while((getchar()) != '\n');
}
