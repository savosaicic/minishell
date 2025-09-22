# minishell
A small, interactive **Unix shell** written in C. Implements a Bash-like prompt, parsing, pipelines, redirections, environment expansion, signals, and core built-ins.
## Features
- **Interactive prompt** with command **history** (via `readline`).
- **Program search & exec** via `$PATH`, plus absolute/relative paths.
- **Quoting rules:**
	- single quotes `'...'` disable all expansions,
	- double quotes `"..."` keep `$VAR` expansion.
- **Redirections:** `<`, `>`, `>>`, and **heredoc** `<< DELIM`.
- **Pipelines:** `cmd1 | cmd2 | cmd3`.
- **Expansions:** `$VAR` and `$?` (last pipeline exit status).
- **Signals:** in interactive mode
	- **Ctrl-C** → new prompt on a new line,
	- **Ctrl-D** → exit,
	- **Ctrl-\** → no effect.
- **Built-ins:** `echo -n`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
## Build & Run
The project provides a `Makefile` with standard rules (`all`, `clean`, `fclean`, `re`), compiles with **`cc -Wall -Wextra -Werror`**, and can use **libft**. Link `readline` (and your system’s termcap/terminfo if needed).
```bash
# Build
make

# Run
./minishell
```
## Usage
Use **minishell** like a normal shell:
```bash
minishell$> echo Hello
Hello
minishell$>
```
