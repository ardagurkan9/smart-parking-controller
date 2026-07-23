# Smart Parking Controller

A modular parking management simulation written in C11.

The project models the core behavior of a smart parking entrance: access
control, traffic lights, a barrier, capacity tracking, alarms, emergency
behavior, and vehicle records. Future phases will extend the system with an
event-driven state machine, parking sessions, pricing, and persistence.

## Project Goals

This project is designed to practice:

- Modular C programming with separate header and source files
- Bitwise operations and register-style state management
- Dynamic memory allocation and cleanup
- State machines and event-driven design
- Defensive input validation and detailed error handling
- Unit and integration testing

## Current Features

- [x] Eight-bit controller state register
- [x] Red, yellow, and green traffic-light control
- [x] Barrier open and close operations
- [x] System enable and disable behavior
- [x] Alarm and emergency behavior
- [x] PIN validation and failed-attempt tracking
- [x] Parking capacity and occupancy tracking
- [x] Vehicle entry, exit, and full-lot handling
- [x] Dynamic vehicle record storage
- [x] Vehicle add, search, list, and remove operations
- [x] Safe cleanup of dynamically allocated vehicle records

## Planned Features

- Finite state machine for the main parking workflow
- Fixed-capacity circular event queue
- Detailed and readable result codes
- Parking sessions and ticket management
- Configurable fee calculation using integer cents
- Save and load support for sessions and system settings
- Expanded unit and integration tests
- Strict warning, memory, and undefined-behavior checks

## Architecture

The project is split into focused modules:

| Module | Responsibility |
| --- | --- |
| `controller` | Component states, lights, barrier, alarm, emergency, and capacity |
| `access` | PIN validation, failed attempts, and access lock state |
| `vehicle` | Dynamic vehicle records, lookup, insertion, removal, and cleanup |
| `state_machine` | Planned main workflow and valid state transitions |
| `event_queue` | Planned FIFO event delivery using a circular queue |
| `session` | Planned parking tickets and active session tracking |
| `pricing` | Planned fee policies and integer-based charge calculation |
| `persistence` | Planned safe file save and load operations |

## Controller State Register

The controller stores its component states in a single eight-bit register.
Each bit represents one independent on/off condition.

| Bit | Mask | State | Set (`1`) means |
| ---: | :---: | --- | --- |
| 0 | `0x01` | Red light | Red light is on |
| 1 | `0x02` | Yellow light | Yellow light is on |
| 2 | `0x04` | Green light | Green light is on |
| 3 | `0x08` | Barrier | Barrier is open |
| 4 | `0x10` | Alarm | Alarm is active |
| 5 | `0x20` | Parking full | No spaces are available |
| 6 | `0x40` | Emergency mode | Emergency mode is active |
| 7 | `0x80` | System enabled | Controller is enabled |

Example:

```text
Register: 10001001 (0x89)
Active: system enabled, barrier open, red light on
```

The register represents component states. The planned finite state machine
will separately represent workflow states such as PIN validation, barrier
opening, vehicle passage, alarm, and emergency handling.

## Project Structure

```text
smart-parking-controller/
|-- include/
|   |-- access.h
|   |-- controller.h
|   `-- vehicle.h
|-- src/
|   |-- access.c
|   |-- controller.c
|   |-- main.c
|   `-- vehicle.c
|-- tests/
|   |-- test_access.c
|   |-- test_controller.c
|   `-- test_vehicle.c
|-- README.md
`-- Makefile                 # Planned
```

## Requirements

- A C11-compatible compiler such as GCC or Clang
- GNU Make once the Makefile phase is complete

## Building the Tests

Until a Makefile is added, each test can be compiled separately.

Controller tests:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude \
    tests/test_controller.c src/controller.c \
    -o test_controller
```

Access and alarm tests:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude \
    tests/test_access.c src/access.c src/controller.c \
    -o test_access
```

Vehicle record tests:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -Iinclude \
    tests/test_vehicle.c src/vehicle.c \
    -o test_vehicle
```

## Roadmap

### Phase 1 — Foundation

- [x] Create the project directory structure
- [x] Define register masks and bitwise state helpers
- [ ] Complete the application entry point
- [ ] Add a Makefile with build, test, and clean targets

### Phase 2 — Controller Components

- [x] Implement traffic-light behavior
- [x] Implement barrier operations
- [x] Implement system enable and disable behavior
- [x] Implement alarm and emergency behavior

### Phase 3 — Access and Capacity

- [x] Add PIN creation and validation
- [x] Track consecutive invalid PIN attempts
- [x] Activate and reset the alarm
- [x] Configure parking capacity
- [x] Handle entry, exit, and full-lot conditions

### Phase 4 — Vehicle Records

- [x] Define vehicle records
- [x] Store records using dynamic memory
- [x] Add, search, list, and remove records
- [x] Release allocated memory safely

### Phase 5 — State and Event Architecture

- [ ] Define finite state machine states and events
- [ ] Allow only valid state transitions
- [ ] Return detailed errors for invalid transitions
- [ ] Implement a fixed-capacity circular event queue
- [ ] Support `O(1)` push, pop, and peek operations
- [ ] Handle full, empty, and wrap-around queue states

### Phase 6 — Parking Sessions and Pricing

- [ ] Track tickets, plates, vehicle types, and timestamps
- [ ] Store sessions in a safely growing dynamic array
- [ ] Prevent duplicate active sessions
- [ ] Search sessions by plate or ticket
- [ ] Close active sessions during vehicle exit
- [ ] Calculate fees using integer cents
- [ ] Support free time, hourly rounding, daily limits, and lost tickets
- [ ] Support category-specific pricing policies

### Phase 7 — Errors and Persistence

- [ ] Introduce shared detailed result codes
- [ ] Convert result codes to readable messages
- [ ] Save sessions and required settings
- [ ] Load and validate saved data safely
- [ ] Reject missing, empty, corrupt, or duplicate records
- [ ] Handle file and allocation failures

### Phase 8 — Quality

- [ ] Validate all public module inputs
- [ ] Expand unit and integration tests
- [ ] Test state transitions and queue wrap-around
- [ ] Test session and pricing boundaries
- [ ] Test persistence round trips and corrupt files
- [ ] Build with strict compiler warnings
- [ ] Run memory and undefined-behavior checks

## Development Guidelines

- Keep each module focused on one responsibility.
- Expose public interfaces through header files.
- Keep private helpers inside their source modules.
- Avoid floating-point values for money.
- Check every memory allocation and file operation.
- Add tests for new behavior and failure paths.

## License

This project is licensed under the [MIT License](LICENSE).
