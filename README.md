# Smart Parking Controller

Smart Parking Controller is a terminal-based parking management simulation written in C. It models the core components of a parking entrance, including access control, traffic lights, a barrier, capacity tracking, and an alarm system.

The project is designed to practice bitwise operations, modular C programming, state management, dynamic memory, and automated testing.

## Planned Features

- Vehicle entry and exit operations
- PIN-based access control
- Parking capacity and occupancy tracking
- Red, yellow, and green traffic-light control
- Barrier opening and closing
- Alarm activation after repeated invalid attempts
- Emergency mode
- Vehicle record management
- System status display

## System State Register

The controller stores its main states in a single 8-bit register. Each bit represents one component or operating condition.

| Bit |   Mask   | State          | Set (`1`) means        |
| --: | :------: | -------------- | ------------------------ |
|   0 | `0x01` | Red light      | Red light is on          |
|   1 | `0x02` | Yellow light   | Yellow light is on       |
|   2 | `0x04` | Green light    | Green light is on        |
|   3 | `0x08` | Barrier        | Barrier is open          |
|   4 | `0x10` | Alarm          | Alarm is active          |
|   5 | `0x20` | Parking full   | No spaces are available  |
|   6 | `0x40` | Emergency mode | Emergency mode is active |
|   7 | `0x80` | System enabled | Controller is enabled    |

Example:

```text
Register: 10000101 (0x85)
Active bits: 7, 2, and 0
State: system enabled, green light on, red light on
```

## Target Project Structure

The implementation will follow this layout as the project is developed:

```text
smart-parking-controller/
|-- include/               # Public header files
|-- src/                   # Application source files
|-- tests/                 # Automated tests
|-- Makefile               # Build and test commands
|-- README.md              # Project documentation
`-- .gitignore
```

## Requirements

- A C11-compatible compiler such as GCC or Clang
- GNU Make (optional, once the Makefile is available)

## Build

Compile directly with GCC:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude src/*.c -o parking_controller
```

## Run

On Linux or macOS:

```bash
./parking_controller
```

On Windows PowerShell:

```powershell
.\parking_controller.exe
```

## Roadmap

### Phase 1 — Project Foundation

- [X] Create the `include`, `src`, and `tests` directories
- [ ] Add the initial application entry point
- [X] Define register masks and bitwise state helpers
- [ ] Add a Makefile with build, run, test, and clean targets

### Phase 2 — Controller Components

- [X] Implement traffic-light states and valid transitions
- [X] Implement barrier open and close operations
- [X] Implement system enable and disable states
- [X] Implement emergency mode and safe component behavior

### Phase 3 — Access and Capacity

- [X] Add PIN creation and verification
- [X] Track consecutive invalid PIN attempts
- [X] Activate and reset the alarm
- [X] Configure parking capacity
- [X] Handle vehicle entry, exit, and full-lot conditions

### Phase 4 — Vehicle Records

- [ ] Define the vehicle record structure
- [ ] Store vehicle records using dynamic memory
- [ ] Search, list, and remove vehicle records
- [ ] Release all allocated memory safely

### Phase 5 — User Interface and Quality

- [ ] Add an interactive terminal menu
- [ ] Display register, component, and occupancy status
- [ ] Validate user input and handle errors gracefully
- [ ] Add unit and integration tests
- [ ] Run builds with strict compiler warnings enabled
- [ ] Add memory and undefined-behavior checks

## Contributing

Keep modules focused, expose public interfaces through header files, and compile with all warning flags enabled. New behavior should include corresponding tests whenever possible.

## License

No license has been selected yet.
