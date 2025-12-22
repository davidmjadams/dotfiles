# Dotfiles (macOS, zsh, Node/TypeScript)

This repository contains my personal dotfiles, rebuilt and modernised in 2025.

They are:
- **macOS-only**
- **zsh-only**
- Focused on **Node.js / TypeScript**
- Managed declaratively with **Dotbot**
- Explicit, minimal, and safe to re-run

The goal is a setup that:
- Scales across machines
- Survives macOS upgrades
- Avoids hidden magic or shell frameworks
- Is easy to understand months (or years) later

---

## Installation

## Bootstrap (first-time setup)

This repository is intentionally cloned over **HTTPS** on first install to avoid
a chicken-and-egg problem with SSH keys.

SSH configuration is installed by these dotfiles, but SSH keys themselves must be
created manually and cannot exist before cloning the repo.

### First-time install on a new machine

1. Clone the dotfiles repo via HTTPS:
   ```bash
   git clone https://github.com/davidmjadams/dotfiles.git ~/dotfiles
   cd ~/dotfiles
   chmod +x install
   ```

2. Run the installer:
   ```bash
   ./install
   ```

3. Set up SSH keys (once per machine):
   ```bash
   ssh-keygen -t ed25519 -C "your@email.com"
   ssh-add --apple-use-keychain ~/.ssh/id_ed25519
   pbcopy < ~/.ssh/id_ed25519.pub
   ```
   Add the copied public key to GitHub.

4. Switch this repo to use SSH (recommended):
   ```bash
   git remote set-url origin git@github.com:davidmjadams/dotfiles.git
   ```

5. Install 1password browser
   ```bash
   https://chromewebstore.google.com/detail/1password-%E2%80%93-password-mana/aeblfdkhhhdcdjpifhhbdiojplfjncoa?pli=1
   ```

From this point on, all GitHub access will use SSH.


---

## High-level structure

```
dotfiles/
├── install
├── install.conf.yaml
├── zsh/
│   ├── zshrc
│   ├── exports.zsh
│   ├── aliases.zsh
│   └── functions.zsh
├── macos/
│   ├── core.macos
│   ├── input.macos
│   └── dock.macos
├── config/
│   └── nvim/
├── git/
│   ├── gitconfig
│   └── gitignore_global
├── Brewfile
├── inputrc
├── .extra.example
└── README.md
```

---

## Dotbot

### `install`
Entry point for setup. Runs Dotbot and applies the configuration.

### `install.conf.yaml`
Declarative description of:
- Which files are symlinked into `$HOME`
- Which macOS scripts are run
- Which Homebrew packages are installed

This file is the **source of truth** for machine setup.

---

## Shell (zsh)

### `zsh/zshrc`
Main zsh entry point. Responsible for:
- Loading exports, aliases, and functions
- History behaviour (shared history, substring search)
- Autocomplete (`compinit`)
- Node environment (`fnm`)
- pnpm path setup
- Editor defaults (Cursor)
- Autosuggestions (history-based, inline)

Notably **does not** use:
- oh-my-zsh
- prezto
- any shell framework

Everything is explicit.

### `zsh/exports.zsh`
Environment variables and PATH setup.

Includes:
- Locale settings
- Homebrew paths
- Telemetry opt-outs

Anything that affects *process environment* lives here.

### `zsh/aliases.zsh`
Pure command aliases only.

Examples:
- Safer defaults (`rm -i`, `mv -i`)
- Tool replacements (`ls → eza`, `cat → bat`)
- pnpm shortcuts

No functions, no logic.

### `zsh/functions.zsh`
Small, reusable shell functions.

Examples:
- `mkcd` – create & cd
- `git-root` – jump to repo root
- Lightweight helpers only

If it needs arguments or logic, it goes here (not in aliases).

---

## Command-line UX helpers

### `inputrc`
Readline configuration shared across:
- bash
- Node REPL
- Python REPL
- psql
- any readline-based tool

Provides:
- History substring search
- Case-insensitive completion
- Consistent arrow-key behaviour

This complements zsh rather than replacing it.

### Zsh autosuggestions
Installed via Homebrew (`zsh-autosuggestions`) and sourced explicitly.

Provides:
- Inline grey suggestions from **command history only**
- Accept with → or Alt+→

This restores the “predictive typing” experience without a framework.

---

## macOS defaults

macOS configuration is intentionally split by intent, not by Apple app.

### `macos/core.macos`
Safe, universal defaults that are auto-applied.

Includes:
- Prompted computer name (once)
- Highlight colour (pink)
- Keyboard repeat rate
- Finder usability (hidden files, extensions, path bar)
- Save / print panel expansion
- Screenshot defaults
- Disable smart quotes & dashes
- Prevent `.DS_Store` on network volumes

Avoids:
- Deprecated defaults
- Security-sensitive hacks
- UI tweaks that break across versions

### `macos/input.macos`
Input-device behaviour.

Includes:
- Mouse right-click
- Trackpad tap-to-click
- Trackpad secondary click
- Full keyboard access (Tab everywhere)
- Disable press-and-hold for fast key repeat

These still work reliably on modern macOS.

### `macos/dock.macos`
Dock behaviour only.

Includes:
- Icon size
- Running app indicators
- Disable launch animation
- Disable space reordering
- Auto-hide

Explicitly does **not**:
- Wipe Dock contents
- Rebuild app lists
- Touch Launchpad databases

This avoids destructive surprises.

---

## Neovim

### `config/nvim/`
Neovim is configured as a terminal / SSH editor, not a primary IDE.

Includes:
- `lazy.nvim` plugin manager
- Treesitter
- LSP (TypeScript, ESLint)
- Telescope
- Minimal keybindings

Intentionally excludes:
- Themes
- Status lines
- File explorers
- Heavy frameworks

Cursor remains the primary editor.

---

## Git

### `git/gitconfig`
Opinionated but safe Git defaults.

Highlights:
- Rebase-by-default pulls
- Fast-forward only
- Delta for diffs and logs
- Safer force push (`--force-with-lease`)
- Dynamic default branch (`main`)
- Clean, battle-tested aliases

### `git/gitignore_global`
Global ignores (OS files, editor folders, dependencies).

---

## Homebrew

### `Brewfile`
Declarative list of:
- CLI tools
- GUI apps (casks)

You can:
- Add missing packages
- Re-run `./install`
- Homebrew will install only what’s missing

Nothing is removed unless explicitly requested.

---

## Local overrides

### `.extra.example`
Template for machine-specific configuration.

Copied to `~/.extra` (not committed).

Use for:
- API keys
- Work-specific paths
- One-off overrides

This file is sourced by `zshrc` if present.

---

## Design principles (tl;dr)

- Explicit over clever
- Declarative over scripts
- Safe defaults over maximal tweaks
- Easy to delete beats hard to debug
- No hidden state in version control

If something isn’t obviously safe to auto-apply, it’s either optional or manual.

---

## Re-running & updating

You are expected to:
- Add Brew packages over time
- Re-run `./install`
- Edit configs incrementally

This repo describes the desired state of the machine.

Re-running setup just brings the machine closer to that state.
