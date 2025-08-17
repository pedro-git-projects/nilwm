#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

PRIMARY_OUTPUT="eDP-1"
EXTERNAL_OUTPUTS=( "DP-2-1" "DP-2-2" )

MODE="1920x1080"
RATE="60"

VERT_WALLPAPERS=(
  "$HOME/Pictures/wallpapers/vert_eoe.png"
  "$HOME/Pictures/wallpapers/vert_eoe.png"
)
MIXED_WALLPAPERS=(
  "$HOME/Pictures/wallpapers/samori.jpg"
  "$HOME/Pictures/wallpapers/vertical/vert_samori.jpg"
)
WALLPAPERS=(
  "$HOME/Pictures/wallpapers/sad_jesus.jpg"
  "$HOME/Pictures/wallpapers/old_woman_console.jpg"
)

SERVICES=(
  "nm-applet"
  "cbatticon"
  "xfce4-power-manager"
  "/usr/lib/xfce4/notifyd/xfce4-notifyd"
  "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1"
  "numlockx on"
  "volctl"
  "wmname LG3D"
  "unclutter"
)

DAEMON_APPS=(
  "slstatus"
  "keepassxc"
)

PICOM_CONF="$HOME/.dwm/picom.conf"

# host/user overrides without touching repo
[[ -f "$HOME/.dwm/startup/.env.local" ]] && source "$HOME/.dwm/startup/.env.local"
