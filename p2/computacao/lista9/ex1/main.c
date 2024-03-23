#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int day, month;
} Birthday;

typedef struct {
    char *name, *telefone;
    Birthday birthday;
} ContactInfo;

typedef struct {
    int size, cap;
    ContactInfo *contacts;
} ContactList;

ContactList *init_contact_list(int cap) {
    ContactList *list = malloc(sizeof(ContactList));
    list->cap = cap;
    list->size = 0;
    list->contacts = calloc(cap, sizeof(ContactInfo));

    return list;
}

void add_contact(ContactList *list) {
    ContactInfo info;

    printf("Enter contact name: ");
    scanf("%s", info.name);

    printf("Enter contact telefone: ");
    scanf("%s", info.telefone);

    printf("Enter contact day of birth: ");
    scanf("%d", &info.birthday.day);

    printf("Enter contact month of birth: ");
    scanf("%d", &info.birthday.month);

    if (list->size >= list->cap) {
        ContactInfo *ptr =
            realloc(list->contacts, (list->cap + 32) * sizeof(ContactInfo));

        if (ptr == NULL) {
            printf("Error: malloc failure\n");
            exit(1);
        } else {
            list->contacts = ptr;
        }

        list->cap += 32;
    }
}

void remove_contact(ContactList *list);
void print_contacts(ContactList *list);
void print_contacts_with_starting_letter(ContactList *list);
void print_birthday_person_of_this_month(ContactList *list);
int search_contact_by_name(ContactList *list);

/* ContactList *read_contact_list_from_file(FILE *f); */
/* void write_contactlist_to_file(ContactList *list, FILE *f); */

int main(int argc, char *argv[]) {
    int option;
    /* FILE *f = fopen("contats.txt", "a"); */
    /* ContactList *list = read_contact_list_from_file(f); */
    ContactList *list = init_contact_list(1);

    /*     printf("(1) inserir contato:"); */
    /*     printf("(2) remover contato:"); */
    /*     printf("(3) pesquisar um contato pelo nome:"); */
    /*     printf("(4) listar todos os contatos:"); */
    /*     printf("(5) listar os contatos cujo nome inicia com uma dada
     * letra:"); */
    /*     printf("(6) imprimir os aniversariantes do mês:"); */

    /*     printf(":"); */
    /*     scanf("%d", &option); */

    /*     switch (option) { */
    /*     case 1: */
    /*         add_contact(&list); */
    /*         break; */
    /*     case 2: */
    /*         remove_contact(&list); */
    /*         break; */
    /*     case 3: */
    /*         search_contact_by_name(list); */
    /*         break; */
    /*     case 4: */
    /*         print_contacts(list); */
    /*         break; */
    /*     case 5: */
    /*         print_contacts_with_starting_letter(list); */
    /*         break; */
    /*     case 6: */
    /*         print_birthday_person_of_this_month(list); */
    /*         break; */
    /*     default: */
    /*         break; */
    /*     } */
    /*     return 0; */

    /* write_contactlist_to_file(list, f); */
}
