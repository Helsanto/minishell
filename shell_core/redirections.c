#include "../include/minishell.h"

int redirect_input(const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error Opening File\n");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error redirecting input");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int redirect_output(const char *filename)
{
	int fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error Opening File\n");
		close(fd);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error redirecting output");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

/*int main(void)
{
	char buffer[256];
    if (redirect_output("output.txt") == -1)
    {
        fprintf(stderr, "Failed to redirect output\n");
        return 1;
    }
	if (redirect_input("input.txt") == -1)
    {
        fprintf(stderr, "Failed to redirect input\n");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        printf("Read from input: %s", buffer);
    }
    return 0;
}*/