#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> /* system calls: defs & decls essencials */
#define MAX_BUFF 1024

typedef struct pessoas {
    char nome[100];
    int idade;

} PESSOAS;

// Retorna o ídice onde inseriu a struct
int add_pessoa(int fd, int age, char *name){
    PESSOAS p;
    p.idade = age;
    strcpy((p.nome), name);

    int index = 0;
    off_t off = lseek(fd, 0, SEEK_END);
    index = off / sizeof(struct pessoas);

    write(fd, &p, sizeof(struct pessoas));

    return index;
}

int new_age(int fd, int age, char *name){
    PESSOAS p;
    int index = -1;
    int i = 0;
    ssize_t bytes;

    while ((bytes = read(fd, &p, sizeof(struct pessoas))) > 0){
        if (!strcmp(p.nome, name)) {
            p.idade = age;
            lseek(fd, -sizeof(struct pessoas), SEEK_CUR);
            write(fd, &p, sizeof(struct pessoas));
            index = i;
        } 
        i++;
    } 

    return index;
}

int new_age_reg(int fd, int age, int reg){
    PESSOAS p;
    int index = reg * sizeof(struct pessoas);
    lseek(fd, index, SEEK_SET);
    read(fd, &p, sizeof(struct pessoas));
    lseek(fd, -sizeof(struct pessoas), SEEK_CUR);
    p.idade = age;
    write(fd, &p, sizeof(struct pessoas));
    return reg;
}

void print_pessoas(int fd) {
    PESSOAS p;
    ssize_t bytes;
    while((bytes = read(fd, &p, sizeof(struct pessoas))) > 0)
        printf("\tname: %s\tage: %d\n", p.nome, p.idade);
}

int test_reg(char c){
    if (c == '0' || c == '1' || c == '2' ||
        c == '3' || c == '4' || c == '5' || 
        c == '6' || c == '7' || c == '8' || c == '9'){
        return 1;
    }
    else return 0;
}

int main(int argc, char **argv) {
    ssize_t fd = open(argv[1], O_RDWR | O_CREAT, 0600);
    if (fd == -1) {
        perror("Error: ");
    }

    if (argc == 2) {
        print_pessoas(fd);
        return 0;
    }

    int index;
    int age = strtol(argv[4], NULL, 10);
    if (argv[2][1] == 'i') {
        index = add_pessoa(fd, age, argv[3]);
        printf("\tregisto: %d\n", index);
    }

    if (argv[2][1] == 'u') {
        if (test_reg(argv[3][0]))
            index = new_age_reg(fd, age, atoi(argv[3]));
        else
            index = new_age(fd, age, argv[3]);
        if (index == -1) 
            printf("Não encontramos a pessoa que procura.\n");   
        else 
            printf("\tregisto: %d\n", index);     
    }

    return 0;
}