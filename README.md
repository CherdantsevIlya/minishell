<h1 align="center">
    M I N I S H E L L
</h1>

___

## :memo: **About**

_The objective of this project is for you to create a simple shell._

### *Keywords*  
> + Unix logic

### *Skills*
> + Unix
> + Imperative programming
> + Rigor

For detailed information, refer to the [**subject of this project**](https://github.com/cherdantsevilya/minishell/blob/main/content/en.subject.pdf).

___

## 🚀 **Description**

This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors. This was a group project and I had the honor to do it with [@zhavzharik](https://github.com/zhavzharik) :)


Here is an example of what it looks like:

<p align="center">
    <img width="1017" alt="msh" src="https://user-images.githubusercontent.com/70847388/171484226-0d5269e5-0c50-4167-8b4d-79af06ac8ed1.png">
</p>

### *Shell should:*

+ Display a prompt when waiting for a new command.
+ Have a working history.
+ Search and launch the right executable (based on the `PATH` variable or using a relative or an absolute path). Not use more than one global variable. Think about it. You will have to explain its purpose.
+ Not interpret unclosed quotes or special characters which are not required by the subject such as `\` (backslash) or `;` (semicolon).
+ Handle `’` (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
+ Handle `"` (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for `$` (dollar sign).
+ Implement redirections:
    + `<` should redirect input.
    + `>` should redirect output.
    + `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
    + `>>` should redirect output in append mode.
+ Implement pipes (`|` character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
+ Handle environment variables (`$` followed by a sequence of characters) which should expand to their values.
+ Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline.
+ Handle `ctrl-C, ctrl-D and ctrl-\` which should behave like in bash.
+ In interactive mode:
    + `ctrl-C` displays a new prompt on a new line.
    + `ctrl-D` exits the shell.
    + `ctrl-\` does nothing.
+ Your shell must implement the following builtins:
    + **`echo`** with option -n
    + **`cd`** with only a relative or absolute path
    + **`pwd`** with no options
    + **`export`** with no options
    + **`unset`** with no options
    + **`env`** with no options or arguments
    + **`exit`** with no options

