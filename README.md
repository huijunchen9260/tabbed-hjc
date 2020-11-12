# Hui-Jun Chen's build of tabbed

A missing tab layout for any windows manager / desktop environment

<!-- vim-markdown-toc GFM -->

* [Unique functionality](#unique-functionality)
* [Key bindings](#key-bindings)
* [Requirements](#requirements)
* [Installation](#installation)
* [Patches applied](#patches-applied)
* [Scripts](#scripts)
* [Configuration](#configuration)
	* [Rofi compatibility](#rofi-compatibility)

<!-- vim-markdown-toc -->

## Unique functionality

- `Super-Shift-.` to ***open terminal application*** embeded in tabbed
- `Super-Shift-/` to open new terminal window with the ***chosen terminal's path***
- `Super-Shift-a` to ***attach window*** from current workplace.
    - Require `wmctrl`.
    - Require windows manager / desktop environment with `EWMH` (Extended windows manager Hint)
    - Should use `-c` argument, i.e., `tabbed -c software -embedarg`.
- `Super-Shift-s` to **attach window** by mouse selection.
    - Should use `-c` argument, i.e., `tabbed -c software -embedarg`.
- `Super-Shift-equal` to ***automatically attach all windows*** from current workplace.
    - Require `wmctrl`.
    - Require windows manager / desktop environment with `EWMH` (Extended windows manager Hint)
    - Should use `-c` argument, i.e., `tabbed -c software -embedarg`.
- `Super-Shift-d` to ***detach child window*** from current tabbed window.
    - Should use `-c` argument, i.e., `tabbed -c software -embedarg`.
- `Super-Shift-minus` to ***automatically detach all child windows*** from current tabbed window.
    - Should use `-c` argument, i.e., `tabbed -c software -embedarg`.
- `Super-Shift-[` to ***hide current tab*** in current tabbed window.
- `Super-Shift-]` to ***show hidden tab*** in current tabbed window by dmenu prompt.
- `Super-Shift-\` to ***show all hidden tabs*** in current tabbed window.

## Key bindings

- `Super-Shift` to show tabs
- `Super-Shift-Return` to open new tab
- `Super-Shift-j` to previous tab
- `Super-Shift-k` to next tab
- `Super-Shift-h` to move selected tab one to the left
- `Super-Shift-l` to move selected tab one to the right
- `Super-Shift-u` to toggle autofocus of urgent tabs
- `Control-Tab` to toggle between the selected and last selected tab
- `Super-Shift-q` to close tab
- `Ctrl-u` to focus next urgent tab
- `Super-Shift-[0..9]` to jumps to nth tab

## Requirements

- Xlib header files to build tabbed
- [dmenu](https://tools.suckless.org/dmenu/) to show prompt
    - Or see [Rofi compatibility](#rofi-compatibility) to use `rofi`
- `cut`, `xargs`, `grep`, `pstree`, `sed`, `wmctrl`, `xdotool`, `xprop`, `xwininfo`

## Installation

```sh
git clone https://github.com/huijunchen9260/tabbed-hjc
cd tabbed-hjc
sudo make install
```

## Patches applied

- [alpha.diff](https://tools.suckless.org/tabbed/patches/alpha/)
- [tabbed-clientnumber-0.6.diff](https://tools.suckless.org/tabbed/patches/clientnumber/)
- [tabbed-keyrelease-20191216-b5f9ec6.diff](https://tools.suckless.org/tabbed/patches/keyrelease/)
- [tabbed-0.6-xft.diff](https://tools.suckless.org/tabbed/patches/xft/)
- [tabbed-hidetabs-20191216-b5f9ec6.diff](https://tools.suckless.org/tabbed/patches/hidetabs/)
- [tabbed-icon-20200905-2da4e96.diff](https://tools.suckless.org/tabbed/patches/icon/) (modified by me, see `patches` folder)

## Scripts

1. `tabbed-slime`: use [vim-slime](https://github.com/jpalardy/vim-slime) with tabbed.
Move `tabbed-slime` to your `$PATH` and add the following code into your `~/.vimrc`:

```vimL
let g:slime_target = "x11"
function SlimeOverrideConfig()
    let b:slime_config = {"window_id": ""}
    let b:slime_config["window_id"] = system("tabbed-slime")
endfunction
```

2. `tabbedize`: make non-tabbed window tabbed.


## Configuration

### Rofi compatibility

`tabbed-hjc` use `dmenu` by default. If you want to use `rofi`, you can modify `config.def.h` (or `config.h`) by either

1. Replacing `dmenu` to `rofi`, with the corresponding arguments. The arguments I use for dmenu is `-i` for case insensitivity, `-l` for vertical prompt, and `-p` for prompt name, or
2. Simply replacing `dmenu` as `rofi -dmenu`, and leave all the other arguments as it.
