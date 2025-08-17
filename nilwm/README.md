# nilwm

**nilwm** is my personal fork of [suckless dwm](https://dwm.suckless.org/), customized into a lightweight, minimalist window manager tailored for my workflow. The name comes from a play on words. I sometimes go by **nilptr** as a developer, so the window manager became **nilwm**.

This project integrates a curated set of patches, personalized keybindings, and system integration scripts to create a balance between tiling efficiency and modern usability.

## Philosophy

* Minimal core, functional patches only.
* Aesthetic but not bloated.
* Keyboard-driven workflow.
* Hackable and extendable 

---

## Features

* **Patched DWM base** with:

  * `cyclelayouts` – Cycle between layouts.
  * `vanitygaps (tile only)` – Control inner/outer gaps dynamically.
  * `systray` – Embedded system tray with widget support.
  * `autostart` – Run a custom shellscript automatically at startup.
  * `viewontag` – Switch view when tagging windows.
  * `warp` – Moves the cursor to the center of the currently focused window when focus shifts.
  * `fixborders` – Corrects border alpha behavior with picom.

* **Custom keybindings & scripts**

  * Browser switching (`librewolf`, `chromium`, `qutebrowser`).
  * Quick access to apps (`obsidian`, `spotify-tray`, `guvcview`, `thunar`, etc).
  * Screenshot utilities with `scrot`.
  * Volume and brightness control via `pamixer` + `brightnessctl`.
  * Keyboard layout switcher and monitor restore scripts.
  * Multi-language support (Latin + Cyrillic bindings).

* **Look & Feel**

  * Gruvbox-inspired theme.
  * Gap controls (inner + outer, smart gaps support).
  * Noto Sans Mono + JoyPixels fonts.
  * Custom colors for bar, borders, and workspace states.

---

## Configuration Highlights

* **Tags**: Binary scheme (`1, 10, 11, 100...`) for unique workspace labeling.
* **Rules**: Predefined behaviors (floating, monitors) for apps like `Gimp`, `xfce4-terminal`, `librewolf`.
* **Layouts**: Defaults to `tile`, with `floating` and `monocle` available.

---

## Installation

Clone and build:

```bash
git clone https://github.com/pedro-git-projects/nilwm.git
cd nilwm
make clean install
```

> ⚠️ Requires **X11**, `libX11`, and development headers. Check [dwm build requirements](https://dwm.suckless.org/).

---

## Arch Auto Setup

I provide an additional tool — [`arch-auto-setup`](https://github.com/pedro-git-projects/arch-auto-setup) — that automates much of the post-install environment setup for Arch Linux.

### Highlights:

* Adds user to wheel + sudo configuration.
* Creates default user folders (`xdg-user-dirs`).
* Sets Gruvbox Material Dark GTK theme + oomox icons.
* Builds and links apps like `spotify-tray` and `vesktop`.
* Written in Go, with package installation support.

Usage:

```bash
git clone https://github.com/pedro-git-projects/arch-auto-setup.git
cd arch-auto-setup
go build .
./arch-auto-setup pkg
```
