# Minishell

## 📘 Description

Minishell is a simplified shell implementation written in C. It aims to replicate a subset of the behavior of common UNIX shells (like bash), while deepening the understanding of process management, parsing, and signal handling at the system level.

This project is part of the 42 curriculum, and this implementation includes **only the mandatory part**, following the subject's requirements strictly.

---

## ✅ Mandatory Features

- Display a prompt and wait for user input
- Handle command lines and execute programs using `PATH` environment variable
- Builtin commands:
  - `echo` with option `-n`
  - `cd` with only a relative or absolute path
  - `pwd` with no options
  - `export` with no options
  - `unset` with no options
  - `env` with no options or arguments
  - `exit` with no options
- Redirections:
  - `<`, `>`
  - `<<` (heredoc)
  - `>>`
- Pipes: `|` (multiple pipes supported)
- Environment variable expansion (`$VAR`)
- Handle quotes (`'` and `"`) properly
- Signal handling (`ctrl+C`, `ctrl+\`, `ctrl+D`)
- Exit status (`$?`) support

---

## 🧠 What I Learned

- Lexical analysis and parsing user input
- Implementing a custom tokenizer for shell commands
- File descriptor manipulation and redirection logic
- Process creation with `fork()`, `execve()`, and `waitpid()`
- Managing signal handlers using `signal()` and `sigaction()`
- Building a minimal garbage collector for memory management
- Handling edge cases like quoting, escaping, and invalid input

---

## ⚙️ Requirements

   - No memory leaks or file descriptor leaks

   - Code follows Norminette standards

   - Must work on bash-like behavior for the features above

----

## 🚫 Limitations (as per mandatory part)

   - No support for wildcards (e.g. *, ?)

   - No support for logical operators (&&, ||)

   - No support for advanced line editing (no arrow keys)

   - Only mandatory builtins are implemented

-----

## 🛠️ How to Use

### 1. Clone the Repository
```bash
git clone https://github.com/yourusername/minishell.git
cd minishell
```
- `make`
- `./minishell`
```
$ echo Hello World
Hello World

$ export NAME=John
$ echo $NAME
John

$ ls | grep minishell | wc -l

$ cat << EOF
> line1
> line2
> EOF
line1
line2
```
