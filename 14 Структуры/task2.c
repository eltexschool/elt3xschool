#include <stdio.h>
#include <string.h>

#define N 10
#define N_MENU 3
#define N_TEMP_STR N+1 // на байт больше из-за считывания fgets-ом перехода на новую строку

typedef enum Menu {QUIT, ADD, SHOW, FIND, REMOVE} Menu;

typedef struct Subscriber {
	char lname[N];
	char fname[N];
	char tnumber[N];
} Subscriber;

int main() {

	//Menu menu;

	Subscriber phonebook[N];

	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			char c = (j < N-1) ? '0' : '\0';
			phonebook[i].lname[j] = c;
			phonebook[i].fname[j] = c;
			phonebook[i].tnumber[j] = c;
		}
	}

	char menu = 1;
	while(menu) {
		printf("The phonebook's menu: 0 - quit, 1 - add, 2 - show, 3 - find, 4 - remove\n> ");

		char tempMenu[N_MENU]; // fgets считывает минимум 3 символа; не понятно, как обрабатывать ввод пользователя более 1 (+2 служебных) символа...
		fgets(tempMenu, N_MENU, stdin);
		menu = tempMenu[0] - '0';

		switch(menu) {
			case ADD:
				for(int i = 0; i < N; i++) {
					char slotFound = 1;
					for(int j = 0; j < N-1; j++) { // '\0' не учитываем при поиске свободного слота
						if (phonebook[i].lname[j] != '0') {
							slotFound = 0;
							j = N; // прекращение сканирования на нули текущего имени
						}
					}
					if(slotFound) {
						char tempStr[N_TEMP_STR]; // временная строка для удаления перехода на новую строку; сделать через функцию?
						printf("Last name: ");
						fgets(tempStr, N, stdin);
						for(int j = 0; j < N_TEMP_STR-1; j++) {
							phonebook[i].lname[j] = (tempStr[j] != 10) ? tempStr[j] : '\0';
						}
						printf("First name: ");
						fgets(tempStr, N, stdin);
						for(int j = 0; j < N_TEMP_STR-1; j++) {
							phonebook[i].fname[j] = (tempStr[j] != 10) ? tempStr[j] : '\0';
						}
						printf("Telephone number: ");
						fgets(tempStr, N, stdin);
						for(int j = 0; j < N_TEMP_STR-1; j++) {
							phonebook[i].tnumber[j] = (tempStr[j] != 10) ? tempStr[j] : '\0';
						}
						i = N; // прекращение поиска нового слота
					}
				}
			break;
			case SHOW:
				for(int i = 0; i < N; i++) {
					printf("%d\t%s\t%s\t%s\n", i+1, phonebook[i].lname, phonebook[i].fname, phonebook[i].tnumber);
				}
			break;
			case FIND:
				printf("find\n");
			break;
			case REMOVE:
				printf("Subscriber's last name to remove: ");
				char lnameToRemove[N_TEMP_STR];
				fgets(lnameToRemove, N_TEMP_STR, stdin);

				for(int i = 0; i < N_TEMP_STR; i++) {
					lnameToRemove[i] = (lnameToRemove[i] != 10) ? lnameToRemove[i] : '\0';
				}

				for(int i = 0; i < N; i++) {
					char subscFound = 1;
					for(int j = 0; j < N-1; j++) {
						if(phonebook[i].lname[j] != lnameToRemove[j]) {
							subscFound = 0;
							j = N; // прекращение сравнения имени
						}
						else if((phonebook[i].lname[j] == '\0') && (lnameToRemove[j] == '\0')) {
							//printf("%d %d %c %c", i, j, phonebook[i].lname[j], lnameToRemove[j]);
							j = N;
						}
					}
					if(subscFound) {
						for(int j = 0; j < N; j++) {
							char c = (j < N-1) ? '0' : '\0';
							phonebook[i].lname[j] = c;
							phonebook[i].fname[j] = c;
							phonebook[i].tnumber[j] = c;
						}
						i = N; // прекращение поиска абонента для удаления
					}
				}
			break;
		}
	}

	return 0;
};