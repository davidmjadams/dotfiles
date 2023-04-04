#!/bin/bash


# to maintain cask ....
#     brew update && brew cleanup


# Install native apps

# daily
brew install --cask readdle-spark
brew install --cask 1password
brew install --cask brave-browser
brew install --cask google-chrome
brew install --cask slack
brew install --cask cron
brew install --cask figma
brew install --cask alfred
brew install --cask caffeine
brew install --cask google-drive

# dev
brew install --cask visual-studio-code
brew install --cask iterm2

# install iterm command linne utilities
curl -L https://iterm2.com/shell_integration/install_shell_integration_and_utilities.sh | bash

brew install --cask postman
brew install --cask beekeeper-studio
brew install --cask imageoptim
brew install --cask muzzle


# less often
brew install --cask disk-inventory-x
brew install --cask screenflow

brew tap homebrew/cask-fonts
brew install --cask font-fira-code
