# 42 Minishell Project

Welcome to the 42 Minishell Project repository! This project is part of the 42 curriculum and is focused on creating a simple shell that mimics the behavior of the Unix shell. The goal is to understand how a shell works, including process creation, signal handling, and execution of commands.

## Table of Contents
- [Introduction](#introduction)
- [Project Objectives](#project-objectives)
- [Requirements](#requirements)
- [Project Structure](#project-structure)
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Contributing](#contributing)
- [Acknowledgments](#acknowledgments)
- [Grade](#grade)

## Introduction

The Minishell project aims to provide a deeper understanding of how a shell operates. By building a simple shell, you will learn about process creation, command execution, signal handling, and other key concepts in Unix-like operating systems.

## Project Objectives

- Implement a simple shell that can execute commands.
- Handle various shell built-in commands.
- Manage processes and signals.
- Implement basic features such as input/output redirection and pipes.

## Requirements

- A Unix-based operating system (Linux or macOS).
- GCC compiler.
- Basic understanding of C programming and Unix system calls.

## Project Structure

Here's a brief overview of the project structure:

```
.
├── libft
│ ├── ft_atoi.c
│ ├── ft_bzero.c
│ ├── ft_calloc.c
│ ├── ft_isalnum.c
│ ├── ft_isalpha.c
│ ├── ft_isascii.c
│ ├── ft_isdigit.c
│ ├── ft_isprint.c
│ ├── ft_itoa.c
│ ├── ft_lstadd_back.c
│ ├── ft_lstadd_front.c
│ ├── ft_lstclear.c
│ ├── ft_lstdelone.c
│ ├── ft_lstiter.c
│ ├── ft_lstlast.c
│ ├── ft_lstmap.c
│ ├── ft_lstnew.c
│ ├── ft_lstsize.c
│ ├── ft_memchr.c
│ ├── ft_memcmp.c
│ ├── ft_memcpy.c
│ ├── ft_memmove.c
│ ├── ft_memset.c
│ ├── ft_printf.c
│ ├── ft_printf.h
│ ├── ft_printf_formats.c
│ ├── ft_printfhex.c
│ ├── ft_printf_ptrunin.c
│ ├── ft_putchar_fd.c
│ ├── ft_putendl_fd.c
│ ├──ft_putnbr_fd.c
│ ├── ft_putstr_fd.c
│ ├── ft_split.c
│ ├── ft_strcat.c
│ ├── ft_strchr.c
│ ├── ft_strcmp.c
│ ├── ft_strcpy.c
│ ├── ft_strdup.c
│ ├── ft_striteri.c
│ ├── ft_strjoin.c
│ ├── ft_strlcat.c
│ ├── ft_strlcpy.c
│ ├── ft_strlen.c
│ ├── ft_strmapi.c
│ ├── ft_strncmp.c
│ ├── ft_strncpy.c
│ ├── ft_strnstr.c
│ ├── ft_strpbrk.c
│ ├── ft_strrchr.c
│ ├── ft_strstr.c
│ ├── ft_strtok_r.c
│ ├── ft_strtrim.c
│ ├── ft_substr.c
│ ├── ft_tolower.c
│ ├── ft_toupper.c
│ ├── get_next_line_bonus.c
│ ├── get_next_line_bonus.h
│ ├── libft.h
| └── Makefile
├── src
| ├── cleaner
│ | ├── cleaner.c
│ | └── cleaner2.c
│ ├── commands
│ | ├── cd.c
│ | ├── cd_utils.c
│ | ├── echo.c
│ | ├── echo_checker.c
│ | ├── echo_utils.c
│ | ├── export.c
│ | ├── export_utils.c
│ | ├── export_utils2.c
│ | ├── export_utils3.c
│ | ├── pwd.c
│ | ├── unset.c
│ | └── unset_utils.c
│ ├── Handler
│ | ├── expander.c
│ | ├── expander_utils.c
│ | ├── handler.c
│ | ├── handler_utils.c
│ | ├── handler_utils2.c
│ | ├── handler_utils3.c
│ | ├── handler_utils4.c
│ | ├── handler_utils5.c
│ | ├── handler_utils6.c
│ | ├── pipes.c
│ | ├── pipes_utils.c
│ | ├── pipes_utils2.c
│ | ├── pipes_utils3.c
│ | ├── tokens.c
│ | ├── tokens2.c
│ | ├── tokens3.c
│ | └── tokens4.c
│ ├── includes
│ | └── minishell.h
│ ├── init_and_checker
│ | ├── checker.c
│ | ├── init.c
│ | ├── init_utils.c
│ | ├── redir.c
│ | └── utils.c
│ ├── main.c
│ ├── main_utils.c
│ ├── main_utils2.c
│ ├── main_utils3.c
| ├── signals
│ | └── signals.c
├── Makefile
└── README.md
```

## Installation

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/joaoped2-42PORTO/42-Minishell.git
    cd 42-Minishell
    ```

2. **Compile the Project**:
    ```bash
    make
    ```

    This will create the necessary executable file (e.g., `minishell`).

## Usage

To run the `minishell` program, use the following command:

```bash
./minishell
```

Once running, you can type commands as you would in a standard shell. The minishell supports a subset of common shell commands and features.

## Features
- Built-in Commands: Implement basic built-in commands such as echo, cd, pwd, export, unset, env, and exit.
- Command Execution: Execute external commands found in the system's PATH.
- Pipes: Support for piping commands (e.g., ls | grep minishell).
- Redirection: Support for input and output redirection (e.g., cat < file, echo hello > file).
- Signal Handling: Properly handle signals like Ctrl-C, Ctrl-D, and Ctrl-\.


## Contributing
Contributions are welcome! If you have any suggestions or improvements, feel free to create an issue or submit a pull request. Please ensure that your contributions adhere to the coding standards and guidelines of the project.


## Acknowledgments
- To my partner who helped me a lot throughout the challanges of this project.
- The 42 Network for providing the inspiration and resources for this project.
- The C programming community for their excellent documentation and support.
- All contributors who have helped improve this project.

## Grade
- Norminette: Ok!
- Grade: 101/100

---

Happy coding!
