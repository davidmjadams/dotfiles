# David's dotfiles

Mostly just [Paul Irish's dotfiles](https://github.com/paulirish/dotfiles) with a few tweaks.

## Setup

* Login to iCloud
* Setup git
* Restore [makckup](https://github.com/lra/mackup)
### Setup git on the new machine
* [Generate a new ssh key](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent)
* [Add the key to github](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/adding-a-new-ssh-key-to-your-github-account)

### Cloning the repo
Install your dotfiles onto a new system (or migrate to this setup), [original instructions here](https://www.atlassian.com/git/tutorials/dotfiles)

If you already store your configuration/dotfiles in a Git repository, on a new system you can migrate to this setup with the following steps:

Prior to the installation make sure you have committed the alias to your .bashrc or .zsh:
```
alias config='/usr/bin/git --git-dir=$HOME/.cfg/ --work-tree=$HOME'
```
And that your source repository ignores the folder where you'll clone it, so that you don't create weird recursion problems:
```
echo ".cfg" >> .gitignore
```

Now clone your dotfiles into a bare repository in a "dot" folder of your $HOME:
```
git clone --bare git@github.com:davidmjadams/dotfiles.git $HOME/.cfg
```

Define the alias in the current shell scope:
```
alias config='/usr/bin/git --git-dir=$HOME/.cfg/ --work-tree=$HOME'
```

Checkout the actual content from the bare repository to your $HOME:
```
config checkout
```

The step above might fail with a message like:
```
error: The following untracked working tree files would be overwritten by checkout:
    .bashrc
    .gitignore
Please move or remove them before you can switch branches.
Aborting
```

This is because your $HOME folder might already have some stock configuration files which would be overwritten by Git. The solution is simple: back up the files if you care about them, remove them if you don't care. I provide you with a possible rough shortcut to move all the offending files automatically to a backup folder:

```
mkdir -p .config-backup && \
config checkout 2>&1 | egrep "\s+\." | awk {'print $1'} | \
xargs -I{} mv {} .config-backup/{}
```

Re-run the check out if you had problems:
```
config checkout
```

Set the flag showUntrackedFiles to no on this specific (local) repository:
```
config config --local status.showUntrackedFiles no
```

You're done, from now on you can now type config commands to add and update your dotfiles:
```
config status
config add .vimrc
config commit -m "Add vimrc"
config add .bashrc
config commit -m "Add bashrc"
config push
```
Again as a shortcut not to have to remember all these steps on any new machine you want to setup, you can create a simple script, store it a gist and call it like this:

```
curl -Ls https://gist.githubusercontent.com/davidmjadams/eff9fa72a79f1fa7b83041b815fe1e2f/raw/82374aaf3bc5fb39c34551dae95b1a74e1f7cd82/dot%2520files-setup | /bin/bash
```
For completeness this is the script:

```
git clone --bare git@github.com:davidmjadams/dotfiles.git $HOME/.cfg
function config {
   /usr/bin/git --git-dir=$HOME/.cfg/ --work-tree=$HOME $@
}
mkdir -p .config-backup
config checkout
if [ $? = 0 ]; then
  echo "Checked out config.";
  else
    echo "Backing up pre-existing dot files.";
    config checkout 2>&1 | egrep "\s+\." | awk {'print $1'} | xargs -I{} mv {} .config-backup/{}
fi;
config checkout
config config status.showUntrackedFiles no
```

### installing & using
* `cd ~/`
* run `setup-a-new-machine.sh`
* git config needs attention, read the notes.
* use it. yay!

#### shell

This repo contains config for bash and zsh. 


## Fun parts.

### [`.aliases`](https://github.com/paulirish/dotfiles/blob/master/.aliases) and [`.functions`](https://github.com/paulirish/dotfiles/blob/master/.functions)

So many goodies.

### The "readline config" (`.inputrc`)
Basically it makes typing into the prompt amazing.

* tab like crazy for autocompletion that doesnt suck. tab all the things. srsly.
* no more <tab><tab> that says "Display all 1745 possibilities? (y or n)" YAY
* type `cat <uparrow>` to see your previous `cat`s and use them.
* case insensitivity.
* tab all the livelong day.



### Moving around in folders (`z`, `...`, `cdf`)
`z` helps you jump around to whatever folder. It uses actual real magic to determine where you should jump to. Seperately there's some `...` aliases to shorten `cd ../..` and `..`, `....` etc. Then, if you have a folder open in Finder, `cdf` will bring you to it.
```sh
z dotfiles
z blog
....      # drop back equivalent to cd ../../..
z public
cdf       # cd to whatever's up in Finder
```
`z` learns only once its installed so you'll have to cd around for a bit to get it taught.
Lastly, I use `open .` to open Finder from this path. (That's just available normally.)



## overview of files

####  Automatic config
* `.vimrc`, `.vim` - vim config, obv.
* `.inputrc` - behavior of the actual prompt line

#### shell environment
* `.aliases`
* `.bash_profile`
* `.bash_prompt`
* `.bashrc`
* `.exports`
* `.functions`
* `.extra` - not included, explained below

#### manual run
* `setup-a-new-machine.sh` - random apps i need installed
* `symlink-setup.sh`  - sets up symlinks for all dotfiles and vim config.
* `.macos` - run on a fresh mac os setup
* `brew.sh` & `brew-cask.sh` - homebrew initialization

#### git, brah
* `.git`
* `.gitattributes`
* `.gitconfig`
* `.gitignore`


### `.extra` for your private configuration

There will be items that don't belong to be committed to a git repo, because either 1) it shoudn't be the same across your machines or 2) it shouldn't be in a git repo. Kick it off like this:

`touch ~/.extra && $EDITOR $_`

I have some EXPORTS, my PATH construction, and a few aliases for ssh'ing into my servers in there.

I don't know how other folks manage their $PATH, but this is how I do mine:

```shell
# The top-most paths override here.
      PATH=/opt/local/bin
PATH=$PATH:/opt/local/sbin
PATH=$PATH:/bin
PATH=$PATH:~/.rvm/bin
PATH=$PATH:~/code/git-friendly
# ...

export PATH
```


### Sensible OS X defaults

Mathias's repo is the canonical for this, but you should probably run his or Paul's after reviewing it.

```bash
./.macos
```

### `~/bin`

One-off binaries that aren't via an npm global or homebrew. [git open](https://github.com/paulirish/git-open), [wifi-password](https://github.com/rauchg/wifi-password), [coloredlogcat](https://developer.sinnerschrader-mobile.com/colored-logcat-reloaded/507/), [git-overwritten](https://github.com/mislav/dotfiles/blob/master/bin/git-overwritten), and `subl` for Sublime Text.

### Syntax highlighting for these files

If you edit this stuff, install [Dotfiles Syntax Highlighting](https://github.com/mattbanks/dotfiles-syntax-highlighting-st2) via [Package Control](http://wbond.net/sublime_packages/package_control)

### 2020 update

Rust folks have made a few things that are changing things.

 - most folks know `bat`  as a `cat` replacement
 - https://github.com/dandavison/delta seems a lot better than the diff-so-fancy project that i started. :/
 - https://github.com/ogham/exa is better `ls` and gets all the trapd00r/LS_COLORS stuff etc.
 - https://github.com/bigH/git-fuzzy interactive git thing. deprecates my `git recent` script. and probably some other things.

 Also I'd like to migrate to using homesick or https://www.atlassian.com/git/tutorials/dotfiles

 also interested in https://github.com/dandavison/open-in-editor


## Git bare repo setup
[Article here](https://www.atlassian.com/git/tutorials/dotfiles)

