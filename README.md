# Minishell

A simple shell implementation written in C, inspired by bash. This project is part of the 42 School curriculum, focusing on understanding how shells work by implementing basic shell functionalities.

## Features

- Command execution
- Built-in commands implementation
- Environment variable handling
- Signal handling
- Input/output redirection
- Pipes
- Command history
- Error handling

## Project Structure

```
.
├── includes/    # Header files
├── libft/       # Custom C library
├── src/         # Source files
└── Makefile     # Build configuration
```

## Building the Project

To compile the project, run:

```bash
make
```

This will generate the `minishell` executable.

## Usage

```bash
./minishell
```

## Built-in Commands

The shell implements several built-in commands:
- `echo`: Display a line of text
- `cd`: Change directory
- `pwd`: Print working directory
- `export`: Set environment variables
- `unset`: Remove environment variables
- `env`: Display environment variables
- `exit`: Exit the shell

## Implementation Details

This shell implementation includes:
- Command line parsing
- Environment variable expansion
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)
- Command execution using execve
- Pipe handling for command chaining
- Input/output redirection
- Error handling and appropriate return values

## Author

- ajbermudezh22

## License

This project is part of the 42 School curriculum.