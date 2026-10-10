# Tasbeeh Count

A digital tasbeeh (dhikr counter) built with the [iGraphics](#credits) library in C++, made as my Level 1 Term 1 project for CSE at BUET (2023).

![Main menu](docs/screenshot.png)

## Features

- **Count:** press <kbd>Space</kbd> to count, with an animated tasbeeh, a session timer, and **-1** / **Reset** buttons. Save a count under your name and the dua you were reading.
- **History:** every saved count, grouped by user. Right-click a user to rename or delete them, or a dua to continue counting where you left off, rename it or delete it.
- **Target:** set a **daily** or **weekly** goal for a dua with the purple **+**. Each goal shows its time left, a green tick when completed, or a red cross when missed. Right-click a goal to continue it; a missed goal can be **restarted** with the same duration from now, and a completed one can only be renamed or deleted.
- **Reminder:** the main menu shows "There is an unfinished goal!" while any goal is still in progress, until you open Target.
- **Scrolling:** long user and dua lists get a scrollbar on the right; drag it to scroll.
- **Themes:** green, purple and blue backgrounds.
- **Sound:** background music, a water-drop sound on every count, and a chime when you reach a goal. The speaker icon in the top-right corner of the main menu mutes the music; the one on the count page mutes the count sounds.

## Running it

### Linux

Install a compiler and freeglut (Ubuntu/Debian):

```sh
sudo apt install build-essential freeglut3-dev
```

Then, from the project folder:

```sh
make run
```

`make` builds into `build/`, and `make run` builds and starts the game. Run it from the project folder, because images, sounds and saved data are loaded by relative path.

### Windows

The original version was built with Code::Blocks and MinGW. Open `Tasbeeh Count.cbp`, add `miniaudio.c` and `iSound.h` to the project, and build. GLUT must be set up in MinGW as in the usual iGraphics setup, linking `opengl32`, `glu32` and `glut32`. The runtime DLLs (`glut32.dll`, `glu32.dll`, `opengl32.dll`, `glaux.dll`) are kept in `bin/Debug/`, and the built `.exe` must sit next to them. The current version has only been tested on Linux.

## Controls

| Input | Action |
|---|---|
| Left click | Buttons, menu items, list entries |
| Right click | Options menu on a list entry (continue / restart, rename, delete) |
| <kbd>Space</kbd> | Count +1 (on the count page) |
| <kbd>Enter</kbd> | Confirm text input / go back from messages |
| Drag the scrollbar | Scroll long lists |

## Project layout

```
iMain.cpp          the game: drawing, input and file handling
iGraphics.h        iGraphics library (ported to also build on Linux)
iSound.h           small sound helpers built on miniaudio
miniaudio.h/.c     audio library
stb_image.h        image loader used by iGraphics
pictures/          backgrounds, tasbeeh frames, icons, dialog boxes
music/             background music and sound effects
data_files/        saved data (not tracked by git)
  regular_reads/     history: participant_list.txt + one participantN.txt per user
  targetted_reads/   targets: same layout, plus deadline, completion and duration
```

A fresh clone starts with no saved data: the folders and empty participant lists are created on first run, and each user's file is created when that user is added.

Saved data is plain text, one entry per line, for example:

```
01. Bismillah - 17 - 3                       history:  dua - count - seconds spent
01. Darud - 45 - 54 1685987915 1 86400       target:   dua - target - count, deadline, done, duration (s)
```

## Known limitations

- Up to 15 users and 30 duas per user. Can be changed by editing `maxuser` and `maxdua` at the top of `iMain.cpp`. But intended design was to keep both limited, so the UI doesn't get too crowded.
- Durations are stored in seconds: `86400` for daily and `604800` for weekly. Target lines added by hand must include it.

## Credits

- **iGraphics:** S. M. Shahriar Nirjon; updated by Mohammad Saifur Rahman.
- **[stb_image](https://github.com/nothings/stb):** Sean Barrett (public domain / MIT).
- **[miniaudio](https://miniaud.io):** David Reid (public domain / MIT-0).
