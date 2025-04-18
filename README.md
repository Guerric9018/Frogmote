# Frogmote

**Frogmote** is a Windows desktop application that transforms a smartphone into a gesture‑based remote control. It streams real‑time sensor (gyroscope) data over WebSockets, recognizes swipe gestures, and maps them to system or media actions on the desktop.

---

## Table of Contents
1. [Features](#features)
2. [Prerequisites](#prerequisites)
3. [Installation & Build](#installation--build)
4. [Running the App](#running-the-app)
5. [Configuration & Presets](#configuration--presets)
6. [Code Structure](#code-structure)
7. [Core Components](#core-components)
8. [Extending Frogmote](#extending-frogmote)
9. [Known Issues](#known-issues)

---

## Features

- 🎛️ **Gesture‑driven Control**: Detects four swipes (left/right/up/down) via gyroscope data.
- 🔌 **WebSocket Communication**: Phone runs the Sensor Server app and streams data to the desktop client.
- 🗂️ **Dynamic Presets & Cards**: Organize gesture–action mappings into up to 4 preset panels.
- 💾 **Persistent Storage**: Saves and loads configurations automatically from `presets.dat`.
- 💡 **Immediate Feedback**: System tray notifications confirm connection status and actions taken.
- 📸 **Screenshot Support**: Capture screen via gesture, saved with timestamped filename.

---

## Prerequisites

- Qt 6 (Core, Widgets, WebSockets modules)
- C++17‑compatible compiler (MinGW, MSVC, Clang)
- Sensor Server app installed on your smartphone (Android or iOS)
- CMake ≥ 3.16 or qmake (Qt) for build system

---

## Installation & Build

### Using qmake
1. Clone the repository:
    ```bash
    git clone https://github.com/yourname/frogmote.git
    cd frogmote
    ```
2. Generate Makefile and build:
    ```bash
    qmake Frogmote.pro
    make          # or mingw32-make on Windows
    ```

### Using CMake
```bash
mkdir build && cd build
cmake .. -G "MinGW Makefiles"  # or your preferred generator
cmake --build .
```

---

## Running the App
1. Start the Sensor Server app on your phone, note its IP:port (e.g., `192.168.1.50:8000`).
2. Launch Frogmote:
    ```bash
    ./Frogmote   # or Frogmote.exe on Windows
    ```
3. In the URL bar, enter `ws://<IP>:<port>` and press Enter.
4. Select one of the 4 presets and configure gesture cards by clicking the **+** button.
5. Perform swipes on your phone; mapped actions will execute on the desktop.

---

## Configuration & Presets

- **`presets.dat`**: Located in the application working directory. First line lists card counts for each preset, followed by lines of `gesture action` pairs per card:

    ```text
    2 3 0 1   ← preset counts (e.g. 2 cards in preset 1, 3 in 2, etc.)
    1 4       ← card1: Gesture=1 (LEFTWARD_SWIPE), Action=4 (FORWARD)
    2 1       ← card2: Gesture=2, Action=1
    ...
    ```
- The file is loaded at startup and saved on exit via `LoadPresets`.

---

## Code Structure
```
│
├─ Remote/
   ├─ mainwindow.*        # Builds main window, layouts, preset-switch logic
   ├─ preset.*            # Manages one preset panel: Card widgets + Add button
   ├─ card.*              # Individual gesture→action UI element
   ├─ loadpresets.*       # Loads/saves `presets.dat` data model
   ├─ client.*            # WebSocket client, parses incoming JSON
   ├─ gesturehandler.*    # Gesture detection state machine
   ├─ actioncontroller.*  # Abstract interface + Windows implementation
   ├─ urlbar.*, urltextedit.*, urlcheckmark.*  # Validated URL input widget
   ├─ notifiable.*        # System tray notifications
   ├─ res/                # PNG/SVG assets: icons, frames, backgrounds
   └─ build/...
      └─ presets.dat      # Generated on first run or on exit
```

---

## Core Components

### 1. `MainWindow`
- Sets up top URL/settings bar and bottom split: preset selector and scrollable card area.
- Instantiates 4 `Preset` objects, each with its own `std::vector<Card::data>`.
- Calls `enable()`/`disable()` on presets when the user switches tabs.

### 2. `Preset`
- Derives from `QPushButton` for the preset tab. Contains:  
  - A QGridLayout displaying `Card` widgets.  
  - A reusable **Add Card** button that spans both columns.
- `enable()`: populates cards from data vector and displays the “+” at the bottom center.
- `disable()`: hides “+” and deletes card widgets, preserving `addCardButton` itself.
- Slot `onAddCardClicked()`: appends default entry to data vector, creates new `Card`, repositions “+”, and calls `updateData()`.

### 3. `Card`
- A custom `QWidget` showing:  
  - Two `QComboBox` dropdowns for gesture and action selection.  
  - Icons previewing the selected gesture/action.  
  - Painted card frame via `paintEvent()`.
- Signals trigger updates to internal `Card::data` pointer.

### 4. `LoadPresets`
- Reads/writes `presets.dat` in text format.  
- Maintains a `std::vector<std::vector<Card::data>>` for up to 4 presets.

### 5. `Client`
- Wraps `QWebSocket` to connect to the phone’s sensor server.  
- Parses incoming JSON, forwards numeric arrays to `GestureHandler`.

### 6. `GestureHandler`
- State machine with phases: `STANDBY`, `GESTURING`, etc.  
- Computes vector deltas over time to detect swipe direction.  
- Emits `gestureDetected(Gesture)` when a motion completes.

### 7. `ActionController` & `ActionControllerWindows`
- Abstract interface defines methods: `play()`, `mute()`, `next()`, etc.
- Windows implementation uses `keybd_event()` and Qt notifications.
- `updateData()` points the controller at the current preset’s vector, used by `actionDispatch(Gesture)`.

### 8. `UrlBar`, `UrlTextEdit`, `UrlCheckMark`
- Composite widget for WebSocket URL input.  
- `UrlTextEdit`: masked input & custom `QValidator` to restrict invalid IP/port.  
- `UrlCheckMark`: shows connection status via a toggled checkmark icon.

---

## Extending Frogmote

- **New Gestures**:  
  - In `GestureHandler.cpp`, analyze the diff vector to detect new patterns.   
  - Add enum in `gestures.h`. 
  - Update dropdown in `Card` to include new gesture names.
- **New Actions**:  
  - Add enum in `actions.h`. 
  - Implement behavior in `ActionControllerWindows` (or create other platform subclass).  
  - Update dropdown in `Card` to include new action names.

---

## Known Issues

- Gestures can be sensitive to small jitters. Tuning thresholds may be required.
- macOS/Linux action implementations are not yet provided (Windows only).
- It is currently impossible to delete a card without modifying the `presets.dat` file manually.
