<h1 align="center">
    M I N I S H E L L
</h1>

___

## 🚀 **Description**

This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors. This was a group project and I had the honor to do it with [@zhavzharik](https://github.com/zhavzharik) :)


Here is an example of what it looks like:

<p align="center">
    <img width="1017" alt="msh" src="https://user-images.githubusercontent.com/70847388/171484226-0d5269e5-0c50-4167-8b4d-79af06ac8ed1.png">
</p>

### *What is shell?*

In computing, a shell is a computer program which exposes an operating system's services to a human user or other programs. In general, operating system shells use either a command-line interface (CLI) or graphical user interface (GUI), depending on a computer's role and particular operation. It is named a shell because it is the outermost layer around the operating system.

Command-line shells require the user to be familiar with commands and their calling syntax, and to understand concepts about the shell-specific scripting language (for example, bash).

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
    
###### *For detailed information, refer to the [**subject of this project**](https://github.com/cherdantsevilya/minishell/blob/main/content/en.subject.pdf).*

___

## 📌 **Useful links**

+ [minishell docs](https://harm-smits.github.io/42docs/projects/minishell)
+ [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
+ [Writing Your Own Shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
+ [Minishell Materials](https://www.notion.so/Minishell-Materials-7bbd45a806e04395ab578ca3f805806c)
+ [minishell - Лекция от @imicah](https://misty-anglerfish-277.notion.site/minishell-imicah-af096f1006ea4f2f8ec364d708a068b0)
+ [minishell - Мануал от @avivien & @wpersimm](https://misty-anglerfish-277.notion.site/minishell-avivien-wpersimm-cb026bed394d42118302fd427bfb0b3e)
