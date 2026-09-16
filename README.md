# OSSP Systems Programming Collection

`Creaters_Shell_OSSP` is a Linux systems-programming coursework repository focused on processes, signals, terminal I/O, `/proc`, files, and inter-process communication. It contains practical exercises from more than one module and a small interactive shell implementation.

The repository should be read as a systems-programming collection, not as a single production shell or operating-system distribution.

## Featured implementation: mini shell

[`2520030105_Skill/Skill-02/src/mini_shell.c`](2520030105_Skill/Skill-02/src/mini_shell.c) implements a terminal-aware mini shell in C. It currently provides:

- raw terminal mode when attached to a TTY, with a line-mode fallback;
- `help`, `pwd`, `echo`, `clear`, `exit`, and `quit` built-ins;
- whitespace tokenization with a bounded argument array;
- external command execution using `fork()` and `execvp()`;
- parent/child synchronization through `wait()`;
- SIGINT/SIGTERM handling and terminal restoration.

It does not currently claim pipelines, job control, or shell quoting/escaping.

## Related systems exercises

The repository also includes C examples for:

- `fork()` and `exec()` process creation;
- process states and `/proc` observations;
- zombie processes;
- signal handling;
- FIFO/named-pipe communication;
- file-copy and file-descriptor exercises;
- `strace`, `ps`, `top`, and other Linux observation outputs.

## Build and run the mini shell

Use a Linux environment, WSL, or another POSIX-compatible toolchain with `gcc`:

```bash
cd 2520030105_Skill/Skill-02
gcc -Wall -Wextra -std=c11 src/mini_shell.c -o mini_shell
./mini_shell
```

Try `help`, `pwd`, `echo hello`, or an installed external command. Press `Ctrl+C` to exercise the signal handler and `exit` to leave the shell.

Other exercises have their own `Makefile` or documentation under the corresponding `Practical-*`/`Skill-*` directory; compile them from that directory rather than assuming one repository-wide build.

## Repository layout

```text
2520030105_Skill/       Shiva's skill work, including the featured mini shell
2520030105_Practical/   Shiva's OS practicals and captured observations
2520030040_Skill/       teammate skill work
2520030040_Practical/   teammate practical work
ForgeOS/                project notes and team documentation
ForgeOS_Backup/         existing backup material; not the primary build target
```

Screenshots and command outputs are retained beside the exercise that produced them. They are evidence for the coursework, not a substitute for running the programs.

## Engineering notes

- The shell uses a bounded input buffer and argument array, but it is intentionally educational and does not implement a full POSIX shell grammar.
- Terminal settings are restored on normal exit and in the signal handler.
- The practicals demonstrate low-level OS behavior through executable C programs and Linux inspection tools.

## Contributors

- **Karkala Shiva Reddy**
- Dakur Manoj Kumar

## Author

**Karkala Shiva Reddy** — [GitHub](https://github.com/karkalashivareddy)
