#include "../include/minishell.h"

int redirect_right(const char *filename)
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

/*int main(void)
{
    const char *file = "input.txt";
	char buffer[256];
    if (redirect_right(file) == -1)
    {
        fprintf(stderr, "Failed to redirect input\n");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        printf("Read line: %s", buffer);
    }

    return 0;
}*/