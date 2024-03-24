#!/bin/sh

echo "Getting required tools for development environment..."

pacman -S git clang lldb cmake make ninja vulkan-tools vulkan-headers vulkan-extra-tools
cd ~/
git clone https://aur.archlinux.org/yay.git
cd ~/yay
makepkg -si
yay 
yay -S visual-studio-code-bin
