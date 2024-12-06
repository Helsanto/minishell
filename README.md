# minishell


# Fabio
Quote Handling:

Prevent interpretation of metacharacters within single (') and double (") quotes.
Handle special cases like $ expansion inside double quotes.
Redirections:

< for input redirection.
> for output redirection.
<< (heredoc) until a specified delimiter.
>> for output redirection in append mode.
Pipes:

Implement | to connect command outputs to subsequent command inputs.
Environment Variables:

Expand $ followed by a variable name to its value.
Handle $? for the last exit status.
Signal Handling:

Ctrl-C: Display a new prompt.
Ctrl-D: Exit the shell.
**Ctrl-**: Do nothing in interactive mode.

# Miseal
Built-in Commands:
echo with -n option.
cd with relative or absolute paths.
pwd (print working directory).
export (export environment variables).
unset (unset environment variables).
env (display environment variables).
exit (exit the shell).
