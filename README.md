# Hui-Jun Chen's build of tabbed

The [suckless tabbed](https://tools.suckless.org/tabbed/) with some addition functionality based on dmenu

## Unique functionality

- `Super-Shift-.` to open terminal application embeded in tabbed
- `Super-Shift-.` to open new terminal window with the chosen terminal's path

## Key bindings

- `Super-Shift` to show tabs
- `Super-Shift-Return` to open new tab
- `Super-Shift-j` to previous tab
- `Super-Shift-k` to next tab
- `Super-Shift-h` to move selected tab one to the left
- `Super-Shift-l` to move selected tab one to the right
- `Super-Shift-u` to toggle autofocus of urgent tabs
- `Shift-Tab` to toggle between the selected and last selected tab
- `Super-Shift-,` to open dmenu to either create a new tab appending the entered string or select an already existing tab.
- `Super-Shift-.` to open dmenu to open terminal software. Modify function `OPENTERMSOFT` in `config.h` to fit your software and terminal
- `Super-Shift-/` to open dmenu to open terminal based on existing tabs. Modify function `OPENTERM` in `config.h` to fit your terminal
- `Ctrl-q` to close tab
- `Ctrl-u` to focus next urgent tab
- `Ctrl-[0..9]` to jumps to nth tab

## Requirements

- Xlib header files to build tabbed
- [dmenu](https://tools.suckless.org/dmenu/) to show prompt
- `cut`, `xargs`, `grep`, `pstree`, `sed`, `xprop`, `xwininfo`

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

## Scripts

- `tabbed-slime` to use [vim-slime](https://github.com/jpalardy/vim-slime) with tabbed.
    - Move `tabbed-slime` to your `$PATH` and add the following code into your `~/.vimrc`:
      ```vimL
	let g:slime_target = "x11"
	function SlimeOverrideConfig()
	    let b:slime_config = {"window_id": ""}
	    let b:slime_config["window_id"] = system("tabbed-slime")
	endfunction
      ```

