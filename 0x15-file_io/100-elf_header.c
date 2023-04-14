#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void print_magic(unsigned char *e_ident);
void print_class(unsigned char *e_ident);
void print_data(unsigned char *e_ident);
void print_version(unsigned char *e_ident);
void print_abi(unsigned char *e_ident);
void print_osabi(unsigned char *e_ident);
void print_type(unsigned int e_type, unsigned char *e_ident);
void print_entry(unsigned long int e_entry, unsigned char *e_ident);
void close_elf(int elf);

/**

check_elf - Vérifie si un fichier est un fichier ELF.
@e_ident: Un pointeur vers un tableau contenant les nombres magiques ELF.
Description: Si le fichier n'est pas un fichier ELF, le code de sortie sera 98.
*/
void check_elf(unsigned char *e_ident)
{
int index;
for (index = 0; index < 4; index++)
{
if (e_ident[index] != 127 && e_ident[index] != 'E' && e_ident[index] != 'L' && e_ident[index] != 'F')
{
fprintf(stderr, "Erreur: Ce n'est pas un fichier ELF\n");
exit(98);
}
}
}
/**

print_magic - Imprime les nombres magiques d'un en-tête ELF.
@e_ident: Un pointeur vers un tableau contenant les nombres magiques ELF.
Description: Les nombres magiques sont séparés par des espaces.
*/
void print_magic(unsigned char *e_ident)
{
int index;
printf(" Magic: ");
for (index = 0; index < EI_NIDENT; index++)
{
printf("%02x", e_ident[index]);
if (index == EI_NIDENT - 1)
printf("\n");
else
printf(" ");
}
}
/**

print_class - Imprime la classe d'un en-tête ELF.
@e_ident: Un pointeur vers un tableau contenant la classe ELF.
*/
void print_class(unsigned char *e_ident)
{
printf(" Class: ");
switch (e_ident[EI_CLASS])
{
case ELFCLASSNONE:
printf("Aucune\n");
break;
case ELFCLASS32:
printf("ELF32\n");
break;
case ELFCLASS64:
printf("ELF64\n");
break;
default:
printf("<inconnu: %x>\n", e_ident[EI_CLASS]);
}
}
/**

print_data - Imprime les données d'un en-tête ELF.
@e_ident: Un pointeur vers un tableau contenant la classe ELF.
*/
void print_data(unsigned char *e_ident)
{
printf(" Data: ");
switch (e_ident[EI_DATA])
{
case ELFDATANONE:
printf("Aucune\n");
break;
case ELFDATA2LSB:
printf("2's complément, little endian\n");
break;
case ELFDATA2MSB:
printf("2's complément, big endian\n");
break;
default:
printf("<inconnu: %x>\n", e_ident[EI_CLASS]);
}
}
/**

print_entry - Prints the entry point of an ELF header.

@e_entry: The entry point of an ELF header.

@e_ident: A pointer to an array containing the ELF class.
*/
void print_entry(unsigned long int e_entry, unsigned char *e_ident)
{
printf(" Entry point address: ");

if (e_ident[EI_CLASS] == ELFCLASS32)
printf("0x%x\n", (unsigned int) e_entry);
else
printf("0x%lx\n", e_entry);
}

/**

close_elf - Closes the file descriptor associated with an ELF file.
@elf: The file descriptor associated with the ELF file.
Description: If the file cannot be closed - exit code 100.
*/
void close_elf(int elf)
{
if (close(elf) == -1)
{
dprintf(STDERR_FILENO, "Error: Cannot close file descriptor %d\n", elf);
exit(100);
}
}
/**

main - Displays the information contained in an ELF header.

@argc: The number of arguments passed to the program.

@argv: An array of pointers to the arguments passed to the program.

Description: If the file cannot be opened or read - exit code 98.
*/
int main(int argc, char **argv)
{
int elf, read_result;
unsigned char e_ident[EI_NIDENT];

if (argc != 2)
{
dprintf(STDERR_FILENO, "Usage: %s <ELF_FILE>\n", argv[0]);
exit(98);
}

elf = open(argv[1], O_RDONLY);

if (elf == -1)
{
dprintf(STDERR_FILENO, "Error: Cannot read file %s\n", argv[1]);
exit(98);
}

read_result = read(elf, e_ident, EI_NIDENT);

if (read_result == -1)
{
dprintf(STDERR_FILENO, "Error: Cannot read file %s\n", argv[1]);
exit(98);
}

check_elf(e_ident);
print_magic(e_ident);
print_class(e_ident);
print_data(e_ident);
print_version(e_ident);
print_osabi(e_ident);
print_abi(e_ident);

if (lseek(elf, 16, SEEK_SET) == -1)
{
dprintf(STDERR_FILENO, "Error: Cannot read file %s\n", argv[1]);
exit(98);
}

read_result = read(elf, &e_ident[EI_VERSION], 1);

if (read_result == -1)
{
dprintf(STDERR_FILENO, "Error: Cannot read file %s\n", argv[1]);
exit(98);
}

print_type(*((unsigned int *) &e_ident[16]), e_ident);

if (lseek(elf, 24, SEEK_SET) == -1)
{
dprintf(STDERR_FILENO, "Error: Cannot read file %s\n", argv[1]);
exit(98);
}

read_result = read(elf, &e_ident[EI_ENTRY], 8);

if (read_result == -1)
{
dprintf(STDERR_FILENO, "Error: Cannot read file %s\n", argv[1]);
exit(98);
}

print_entry(*((unsigned long int *) &e_ident[24]), e_ident);

close_elf(elf);

return (0);
}
