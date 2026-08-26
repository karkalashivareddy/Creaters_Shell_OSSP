# Linux Process Monitoring and Control System

## Team Members

| Name | Roll No. | Branch |
|---|---|---|
| KARKALA SHIVA REDDY | 2520030105 | CSE |
| DAKUR MANOJ KUMAR | 2520030040 | CSE |

## Project Title

**Linux Process Monitoring and Control System**

## Problem Statement

Managing and monitoring running processes is an important Operating Systems task. Users need a system-programming tool to inspect process information and perform controlled process-management operations.

## Objectives

- Monitor running Linux processes.
- Display process information using the /proc filesystem.
- Demonstrate Linux process creation and execution.
- Implement signal-based process control.
- Monitor CPU and memory-related process information.
- Analyze Linux system calls using strace.
- Debug the application using GDB.

## Linux/POSIX Technologies

- C
- Linux/POSIX system calls
- /proc filesystem
- Processes and PIDs
- Signals
- File descriptors
- ork()
- exec()
- waitpid()
- kill()
- open()
- ead()
- close()
- GDB
- strace
- GCC
- Makefile

## Expected Outcome

A functional command-line Linux application capable of monitoring running processes and performing controlled process-management operations while demonstrating practical Operating Systems and Linux/POSIX system-programming concepts.

## Repository Structure

`	ext
src/          - Source code
include/      - Header files
tests/        - Test cases
screenshots/  - Execution evidence
output/       - Program outputs

### 4. Create the abstract as a Markdown file

`powershell
@"
# Linux Process Monitoring and Control System

## Problem Statement

Managing multiple processes is an important Operating System responsibility. Users need a reliable mechanism to inspect process information and perform controlled operations such as termination and signal-based management.

## Objectives

1. Monitor running Linux processes.
2. Display process information such as PID, state, parent process and resource information.
3. Implement process-control operations using Linux signals.
4. Demonstrate Linux process creation and execution concepts.
5. Analyze system calls using Linux debugging and tracing tools.

## Proposed Methodology

The project will be implemented as a command-line Linux application using C. Process information will be obtained through the /proc filesystem and Linux file I/O mechanisms. The application will provide process-monitoring and process-control operations. Linux signals will be used for controlled process management. Process creation and execution concepts will be demonstrated using appropriate POSIX APIs.

## OS Concepts / Linux APIs

- /proc filesystem
- Linux processes and PIDs
- Process creation and management
- Signals
- File descriptors
- ork()
- exec()
- waitpid()
- kill()
- open()
- ead()
- close()
- GDB
- strace

## Individual Contribution

### KARKALA SHIVA REDDY - 2520030105 - CSE

- System architecture
- /proc based process monitoring
- Process information extraction
- CPU and memory monitoring
- Testing and performance analysis
- GitHub documentation

### DAKUR MANOJ KUMAR - 2520030040 - CSE

- Process-control functionality
- Signal handling
- Process creation and execution
- ork(), exec(), waitpid() and kill()
- Test cases and output evidence
- GDB and strace analysis

## Tools / Platforms

- Ubuntu/Linux
- C
- GCC
- Makefile
- GDB
- strace
- Git
- GitHub

## Expected Outcome

The expected outcome is a functional Linux command-line application capable of displaying process information and performing controlled process-management operations while demonstrating practical Operating Systems and Linux/POSIX system-programming concepts.
