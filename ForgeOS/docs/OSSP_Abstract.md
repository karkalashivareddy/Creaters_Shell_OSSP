# OSSP Project Abstract

## Project Title

Linux Process Monitoring and Control System

## Abstract

Linux Process Monitoring and Control System is a Linux-based system programming application designed to monitor and control running processes in a user-space environment. Managing multiple processes is an important Operating Systems task because processes consume system resources and may need to be inspected, paused, resumed, or terminated in a controlled manner.

The proposed system will provide a terminal-based interface for viewing running processes and retrieving information such as process ID, process name, process state, parent process ID, CPU-related information, and memory-related information. The system will obtain process information primarily through the Linux `/proc` filesystem and perform process-control operations using Linux signals and POSIX system calls. Users will be able to select a process using its PID and perform operations such as pausing, resuming, graceful termination, and forced termination.

The implementation will use C on Ubuntu/Linux and demonstrate Linux/POSIX concepts including process management, `/proc` interfaces, file descriptors, file I/O, system calls, and signals such as `SIGSTOP`, `SIGCONT`, `SIGTERM`, and `SIGKILL`. Tools such as GDB and strace may be used for debugging and system-call analysis.

The expected outcome is a functional command-line process monitoring and control system that demonstrates practical Operating Systems and Linux system-programming concepts.

## Problem Statement

Linux systems may run many processes simultaneously, making it difficult for users to monitor process information and perform process-control operations efficiently through basic command-line utilities. A system-programming solution is required to provide process information in a structured manner and allow controlled operations such as pausing, resuming, and terminating processes. The project addresses this problem by developing a Linux-based process monitoring and control system using the `/proc` filesystem, Linux system calls, POSIX interfaces, and signals.

## Objectives

1. To monitor and display information about running Linux processes, including process ID, process name, process state, parent process ID, CPU-related information, and memory-related information.

2. To retrieve process information from the Linux `/proc` filesystem using appropriate Linux file and directory interfaces.

3. To provide controlled process-management operations such as pausing, resuming, and terminating processes using Linux signals and system calls.

4. To demonstrate practical Operating Systems and Linux/POSIX system-programming concepts through a functional command-line application and analyze its behavior using appropriate testing and system-analysis tools.

## Tools / Platforms / Software Used

- Ubuntu/Linux
- C programming language
- GCC compiler
- GNU Make
- Visual Studio Code
- GDB debugger
- strace system-call analysis tool
- Git and GitHub

## Expected Outcome

The expected outcome is a functional command-line Linux process monitoring and control system that can retrieve information about running processes through the `/proc` filesystem and provide controlled process-management operations using Linux signals and system calls. The project will demonstrate practical understanding of process management, Linux/POSIX system interfaces, file I/O, file descriptors, signals, debugging, and system-call analysis. The completed system will be tested on Ubuntu/Linux and supported by source code, documentation, test results, screenshots, and demonstration evidence.
