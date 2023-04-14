#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <elf.h>

void print_magic(unsigned char *magic);
void print_class(unsigned char class);
void print_data(unsigned char data);
void print_version(unsigned char version);
void print_osabi(unsigned char osabi);
void print_abi(unsigned char abi);
void print_type(unsigned int type, unsigned char class);
void print_entry(unsigned long int entry, unsigned char class);
void close_elf(int fd);

int main(int argc, char **argv)
{
    int fd;
    struct stat st;
    unsigned char *header = NULL;
    Elf64_Ehdr *ehdr = NULL;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s elf_file\n", argv[0]);
        return (EXIT_FAILURE);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1)
    {
        perror("open");
        return (EXIT_FAILURE);
    }

    if (fstat(fd, &st) == -1)
    {
        perror("fstat");
        close_elf(fd);
        return (EXIT_FAILURE);
    }

    if ((header = malloc(st.st_size)) == NULL)
    {
        perror("malloc");
        close_elf(fd);
        return (EXIT_FAILURE);
    }

    if (read(fd, header, st.st_size) != st.st_size)
    {
        perror("read");
        close_elf(fd);
        free(header);
        return (EXIT_FAILURE);
    }

    ehdr = (Elf64_Ehdr *)header;

    print_magic(ehdr->e_ident);
    print_class(ehdr->e_ident[EI_CLASS]);
    print_data(ehdr->e_ident[EI_DATA]);
    print_version(ehdr->e_ident[EI_VERSION]);
    print_abi(ehdr->e_ident[EI_ABIVERSION]);
    print_osabi(ehdr->e_ident[EI_OSABI]);
    print_type(ehdr->e_type, ehdr->e_ident[EI_CLASS]);
    print_entry(ehdr->e_entry, ehdr->e_ident[EI_CLASS]);

    free(header);
    close_elf(fd);

    return (EXIT_SUCCESS);
}

void print_magic(unsigned char *magic)
{
    printf("Magic:   ");
    for (int i = 0; i < EI_NIDENT; ++i)
        printf("%02x ", magic[i]);
    printf("\n");
}

void print_class(unsigned char class)
{
    printf("Class:                             ");
    switch (class)
    {
        case ELFCLASSNONE:
            printf("none\n");
            break;
        case ELFCLASS32:
            printf("ELF32\n");
            break;
        case ELFCLASS64:
            printf("ELF64\n");
            break;
        default:
            printf("<unknown: %x>\n", class);
            break;
    }
}

void print_data(unsigned char data)
{
    printf("Data:                              ");
    switch (data)
    {
        case ELFDATANONE:
            printf("none\n");
            break;
        case ELFDATA2LSB:
            printf("2's complement, little endian\n");
            break;
        case ELFDATA2MSB:
            printf("2's complement, big endian\n");
            break;
        default:
            printf("<unknown: %x>\n", data);
            break;
    }
}

void print_version(unsigned char version)
{
    printf("Version:                           %d", version);
    switch (version

