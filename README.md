# minishell
<p style="text-align:center;">As beautiful as a shell.</p>

The goal of this project is to create a simpler version of a shell, adhering to the Goals and Rules below.

## Documentation
## Project Goals and Rules
- Display a prompt while waiting for a new command;
- Have a working history;
- Search and launch the right executable based on the PATH variable;
- Avoid using more than one global variable to indicate received signal (e.g. CTRL-C);
- Handle single quotes and double quotes;
- Implement redirections:
      - < redirects input
      - > redirects output
      - << expects a delimiter, then reads input until line containing delimiter. Doesn't update history.
      - >> redirects output in append mode;
- Handle pipes `|`;
- Handle environment variables, which expand to their values;
- Handle `$?` which expands to exit status of the most recently executed foreground pipeline;
- Handle `ctrl-C`, `ctrl-D`, `ctrl-\`;
- In interactive mode: `ctrl-C` displays a new prompt on a new line, `ctrl-D` exits the shell, `ctrl-\` does nothing;
- Handle the following built-ins:


| Built-in    | Description |
| ----------- | ----------- |
|`echo [-n]`|Displays a line of text\nOptional flag `-n` does not output trailing line|
|`cd [path]`| Changes working directory, updating `PWD` and `OLDPWD` <br> Without arguments it changes to Home Directory|
|`pwd`|Shows the current directory as an absolute path.|
|`export`|Accepts arguments name[=value] <br> Adds name to the environment. Set's value of name to value. <br> If no argument is given, displays list of exported variables.|
|`unset`|Accepts argument `name` removing it from the environment|
|`env`|Displays the env variables|
|`exit`| Terminates the shell|


## Installing and Using
To download, clone the repository into your device and navigate inside using `cd pipex`, then typing  `make` to compile all the functions and generate the executable pipex, which you can run as follows:

## Theory
### Bash vs Terminal vs Command Line vs Prompt
A terminal emulator is the the terminal window which is a program that runs Bash, zsh,...
```
jsobreir$ echo $0
/bin/zsh <----- The terminal is running zsh
```
The command line is part of the terminal and it refers to the actual interfacce that interprets the commands you write.
Bash and zsh are similar but zsh is more costumizable, interactive,... generally has more features.

## Basic program
```
while
{
  print_prompt();
  read_line();
  parse();
  exec();
}
```
## Project Implementation
### Parser
The Parser is the software component that reads the command line such as “ls ­al” and puts it 
into a data structure called Command Table that will store the commands that will be 
executed.
#### Tokens
The characters in the arguments are converted into words (tokens).
#### Command Table
This is a table of commands containing all the tokens.

### Executor
The executor will take the command table generated by the parser and for every 
SimpleCommand in the array it will create a new process. It will also if necessary create pipes 
to communicate the output of one process to the input of the next one. Additionally, it will 
redirect the standard input, standard output, and standard error if there are any redirections

### Shell subsystems
These are the subsystems that make executing commands possible:
- Environment variables: expressions of the forms ${VAR} are expandend with the corresponding environment variables.
- Wildcards: Arguments of the form `*` are expanded to all the files that match them, in the local directory or multiple directories.
- Subshells: Arguments between `` are executed and it's output is sent to the input of the shell.
  
## Task List
- [ ] **Shell Features**
  - [ ] **Prompt**: Display a shell prompt and await user input.
  - [ ] **Command History**: Implement a command history using `readline()`.
  - [ ] **Signal Handling**: Properly handle signals (e.g., `ctrl-C`, `ctrl-D`, `ctrl-\`).

- [ ] **Parser**
  - [ ] Implement a **Lexer** (tokenizer) to separate the input into tokens (commands and arguments).
  - [ ] Build the **Command Table** to store commands and arguments.
  - [ ] Implement rules for handling builtins (`echo`, `cd`, `pwd`, etc.) and external commands.
  - [ ] Implement error handling for invalid input.

- [ ] **Built-ins**
  - [ ] **echo**: Implement with `-n` option.
  - [ ] **cd**: Implement with relative or absolute path.
  - [ ] **pwd**: Print the current directory.
  - [ ] **export**: Handle environment variable exportation.
  - [ ] **unset**: Remove environment variables.
  - [ ] **env**: Print all environment variables.
  - [ ] **exit**: Exit the shell with a status.

- [ ] **Expanders**
  - [ ] **Environment Variables**: Expand `$VAR` expressions.
  - [ ] **Handle brackets**: single and double and both.
  - [ ] **Exit Status**: Implement `$?` to hold the exit status of the last executed command.
      
// fazer um grafico antes de comecar esta parte
- [ ] **Executor**
  - [ ] Create child processes using `fork()` for each command.
  - [ ] Use `execve()` to execute external commands.
  - [ ] Implement builtins in the parent process where applicable (`cd`, `export`, etc.).
  - [ ] Ensure the last child process waits to complete using `waitpid()`.

- [ ] **Redirections**
  - [ ] Implement input redirection (`< infile`).
  - [ ] Implement output redirection (`> outfile`).
  - [ ] Implement append output redirection (`>> outfile`).
  - [ ] Implement heredoc (`<< delimiter`).

- [ ] **Pipes**
  - [ ] Implement pipes (`|`) to connect commands in a pipeline.
  - [ ] Redirect stdout of one command to stdin of the next using `pipe()` and `dup2()`.

- [ ] **Testing**
  - [ ] Create test cases for all possible scenarios, including edge cases.
  - [ ] Validate memory management using `valgrind` or similar tools to ensure no memory leaks.

## Links
- https://www.markdownguide.org/extended-syntax/

## Disclaimer
At 42 School our projects have to adhere to the 42 Norm of coding standards and good practices. These include:
- Maximum 25 lines per function and 5 functions per file;
- No variable declarations and assignments in the same line;
- Forbiden structures: `for`, `switch`, `goto` and `case`;
- No more than 5 variables per function.

All of my projects strictly adhere to this Norm, that promotes code simplicity and readability.
