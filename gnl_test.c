#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
    int fd;
    char *line;

	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);

    // Test avec un fichier contenant plusieurs lignes de texte
    fd = open("test_file.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
    printf("Reading test_file.txt:\n");
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);

    // Test avec un fichier vide
    fd = open("empty_file.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
    printf("\nReading empty_file.txt:\n");
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);

    // Test avec un fichier ayant une seule ligne sans '\n'
    fd = open("single_line.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error opening file");
        return (1);
    }
    printf("\nReading single_line.txt:\n");
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);

    return (0);
}
