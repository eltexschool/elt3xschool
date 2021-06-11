#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#define NAME_LENGTH 100
#define TEL_LENGTH 18 // +7 XXX XXX XX XX +2 служебных символа

struct subscriber {
    char lname[NAME_LENGTH];
    char fname[NAME_LENGTH];
    char tnumber[TEL_LENGTH];
};

struct telephone_book {
    struct subscriber *subs;
    int size;
};

struct telephone_book* create_tbook();
void free_tbook(struct telephone_book*);
void add_sub(struct telephone_book*, struct subscriber*);
void remove_sub(struct telephone_book*, char*);
void print_tbook(struct telephone_book*);

struct subscriber* input_sub();
void free_sub(struct subscriber*);
void copy_sub(struct subscriber*, struct subscriber*);
void swap_sub(struct subscriber*, struct subscriber*);
void print_sub(struct subscriber*);

int main()
{
    struct telephone_book *tbook = create_tbook();

    add_sub(tbook, input_sub());
    add_sub(tbook, input_sub());
    add_sub(tbook, input_sub());
    add_sub(tbook, input_sub());
    add_sub(tbook, input_sub());

    print_tbook(tbook);

    char rem_name[NAME_LENGTH];

    printf("Enter a subscriber's last name for removing: ");
    fgets(rem_name, NAME_LENGTH, stdin);
    rem_name[strcspn(rem_name, "\r\n")] = '\0';

    remove_sub(tbook, rem_name);

    print_tbook(tbook);

    free_tbook(tbook);

    return 0;
}

struct telephone_book* create_tbook()
{
    struct telephone_book *tbook = malloc(sizeof(struct telephone_book));

    tbook->subs = NULL;
    tbook->size = 0;

    return tbook;
}

void free_tbook(struct telephone_book *tbook)
{
    free(tbook->subs);
    free(tbook);
}

void add_sub(struct telephone_book *tbook, struct subscriber *sub)
{
    tbook->size += 1;
    tbook->subs = realloc(tbook->subs, tbook->size*sizeof(struct subscriber));
    copy_sub(tbook->subs+(tbook->size-1)*sizeof(struct subscriber), sub);
    free_sub(sub);
    /*if(tbook->size != 0) {
        tbook->size += 1;
        tbook->subs = realloc(tbook->subs, tbook->size*sizeof(struct subscriber));
        copy_sub(tbook->subs+(tbook->size-1)*sizeof(struct subscriber), sub);
        free_sub(sub);
    }
    else {
        tbook->size += 1;
        tbook->subs = sub;
    }*/
}

void remove_sub(struct telephone_book *tbook, char *lname)
{
    for(int i = 0; i < tbook->size; i++)
        if(strncmp(lname, (tbook->subs+i*sizeof(struct subscriber))->lname, NAME_LENGTH) == 0) {
            swap_sub(tbook->subs+(tbook->size-1)*sizeof(struct subscriber), tbook->subs+i*sizeof(struct subscriber));
            tbook->size -= 1;
            tbook->subs = (struct subscriber*) realloc(tbook->subs, tbook->size*sizeof(struct subscriber));
        }
}

void print_tbook(struct telephone_book *tbook)
{
    if(tbook->size != 0)
        for(int i = 0; i < tbook->size; i++)
            print_sub(tbook->subs+i*sizeof(struct subscriber));
    else
        printf("The telephone book is empty.\n");
}

/*struct subscriber* input_sub()
{
    struct subscriber *sub = malloc(sizeof(struct subscriber));

    printf("Last name: ");
    fgets(sub->lname, NAME_LENGTH, stdin);
    printf("First name: ");
    fgets(sub->fname, NAME_LENGTH, stdin);
    printf("Telephone number: ");
    fgets(sub->tnumber, TEL_LENGTH, stdin);

    return sub;
}*/

struct subscriber* input_sub()
{
    struct subscriber *sub = malloc(sizeof(struct subscriber));
    char buffer[NAME_LENGTH+2]; // +2 служебных, которые потом удаляются

    printf("Last name: ");
    fgets(buffer, NAME_LENGTH, stdin);
    buffer[strcspn(buffer, "\r\n")] = '\0';
    strncpy(sub->lname, buffer, NAME_LENGTH);

    printf("First name: ");
    fgets(buffer, NAME_LENGTH, stdin);
    buffer[strcspn(buffer, "\r\n")] = '\0';
    strncpy(sub->fname, buffer, NAME_LENGTH);

    printf("Telephone number: ");
    fgets(buffer, TEL_LENGTH, stdin);
    buffer[strcspn(buffer, "\r\n")] = '\0';
    strncpy(sub->tnumber, buffer, TEL_LENGTH);

    return sub;
}

void free_sub(struct subscriber *sub)
{
    free(sub);
}

void copy_sub(struct subscriber *dest, struct subscriber *src)
{
    strncpy(dest->lname, src->lname, NAME_LENGTH);
    strncpy(dest->fname, src->fname, NAME_LENGTH);
    strncpy(dest->tnumber, src->tnumber, TEL_LENGTH);
}

void swap_sub(struct subscriber *dest, struct subscriber *src)
{
    struct subscriber* temp_sub = malloc(sizeof(struct subscriber));
    copy_sub(temp_sub, src);
    copy_sub(src, dest);
    copy_sub(dest, temp_sub);
    free_sub(temp_sub);
}

void print_sub(struct subscriber *sub)
{
    printf("%s %s %s\n", sub->lname, sub->fname, sub->tnumber);
}
