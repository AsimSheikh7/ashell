# AShell – A Custom Shell in C

This is a basic Unix-style shell implemented in **pure C** as part of my journey to learn the C programming language by building real projects.
Attempting this challenge from this blog: https://brennan.io/2015/01/16/write-a-shell-in-c/

## ✅ Features

- Manually implemented built-in commands:
  - `cd` – Change current directory
  - `pwd` – Print working directory
  - `ls` – List directory contents
  - `man` – Display help for supported commands
- Supports running external programs via `fork()` and `execvp()`
- Graceful handling of unknown commands
- Basic command parsing with arguments

## 🛠️ How to Build

```bash
make
./shell
