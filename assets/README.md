# assets

Put the UI font here.

The application loads `assets/DejaVuSans.ttf` at runtime. Download a free/open
font and place it in this folder with that exact name, for example:

- **DejaVu Sans** — https://dejavu-fonts.github.io/  (file: `DejaVuSans.ttf`)
- or **Roboto** — https://fonts.google.com/specimen/Roboto (rename to `DejaVuSans.ttf`,
  or change the path in `src/aplicatie.cpp`).

> Avoid shipping proprietary fonts like Arial; use an open-licensed font instead.

At build time, CMake copies this whole `assets/` folder next to the compiled
executable, so the relative path resolves when you run the program.
