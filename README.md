A minimal embedded serial command-line interface for Arduino.
---
This project turns a simple Arduino into a lightweight interactive shell, allowing users to enter text-based commands via the serial port. It demonstrates core embedded programming concepts without relying on extra hardware, Bluetooth, or Wi-Fi.

Features
---
Non-blocking serial input handling

Command processing with basic parser

Internal system state management (mode, debug, uptime)

Core commands:

help → list available commands

uptime → show system uptime in milliseconds

status → display system status

reset → software reset of Arduino

Prompt-based interface (>) for interactive use

Why This Project Is Useful

Learn proper non-blocking I/O handling in embedded systems

Understand internal state management with structs

Practice command parsing and modular firmware design

Build a solid foundation for more advanced Arduino projects or microcontroller programming

Usage
---
Upload the sketch to your Arduino.

Open the Serial Monitor at 9600 baud.

Type commands and press ENTER.

Interact with the mini-OS via the available commands.

Next Steps / Extensions
---
Add more commands (version, echo, set mode)

Implement command history

Extend with persistent storage using EEPROM

Split code into multiple files for better modularity
