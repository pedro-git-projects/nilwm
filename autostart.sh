#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

PRIMARY_OUTPUT="eDP-1"
EXTERNAL_OUTPUTS=("DP-2-1" "DP-2-2")

# Display settings (mode, rate)
MODE="1920x1080"
RATE="60"

# Wallpaper list
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

# Services to start once
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

# One-off background apps
DAEMON_APPS=(
  "slstatus"
  "keepassxc"
)

PICOM_CONF="$HOME/.dwm/picom.conf"

run_once() {
  local cmd=($@)
  local name="${cmd[0]}"
  if ! pgrep -f "$name" >/dev/null; then
    "${cmd[@]}" &
  fi
}

is_connected() {
  xrandr | grep -q "^$1 connected"
}

# configure_external_displays [--rotate]
#   if any EXTERNAL_OUTPUTS are connected, disables PRIMARY_OUTPUT
#   and arranges externals in order, optionally rotated.
#   Otherwise falls back to PRIMARY_OUTPUT auto.
configure_external_displays() {
  local rotate=false
  if [[ "${1-}" == "--rotate" ]]; then
    rotate=true
  fi

  local connected=()
  for out in "${EXTERNAL_OUTPUTS[@]}"; do
    if is_connected "$out"; then
      connected+=("$out")
    fi
  done

  if (( ${#connected[@]} )); then
    cmd=(xrandr --output "$PRIMARY_OUTPUT" --off)
    for i in "${!connected[@]}"; do
      local out=${connected[i]}
      cmd+=(--output "$out" --mode "$MODE" --rate "$RATE")
      $rotate && cmd+=(--rotate left)
      if (( i > 0 )); then
        cmd+=(--left-of "${connected[i-1]}")
      fi
    done
    "${cmd[@]}"
  else
    xrandr --output "$PRIMARY_OUTPUT" --auto
  fi
}

# Keeps eDP-1 on when exactly one external is up,
# places that external to the right. Both off when two.
configure_dual_monitors_horizontal_right() {
  local left="DP-2-1"
  local right="DP-2-2"

  if is_connected "$left" && is_connected "$right"; then
    # two externals → laptop off, both externals side-by-side
    xrandr \
      --output "$PRIMARY_OUTPUT" --off \
      --output "$left"  --mode "$MODE" --rate "$RATE" --rotate normal --left-of "$right" \
      --output "$right" --mode "$MODE" --rate "$RATE" --rotate normal

  elif is_connected "$left"; then
    # only left external → laptop on, external to the right
    xrandr \
      --output "$PRIMARY_OUTPUT" --auto \
      --output "$left" --mode "$MODE" --rate "$RATE" --rotate normal --right-of "$PRIMARY_OUTPUT"

  elif is_connected "$right"; then
    # only right external → laptop on, external to the right
    xrandr \
      --output "$PRIMARY_OUTPUT" --auto \
      --output "$right" --mode "$MODE" --rate "$RATE" --rotate normal --right-of "$PRIMARY_OUTPUT"

  else
    # no externals → just laptop
    xrandr --output "$PRIMARY_OUTPUT" --auto
  fi
}

restart_or_start_picom() {
  if pgrep -x picom >/dev/null; then
    kill -USR1 "$(pgrep -x picom)"
  else
    picom --config "$PICOM_CONF" --backend glx --vsync --xrender-sync-fence &
  fi
}

set_wallpapers() {
  local args=()
  for img in "$@"; do
    args+=(--bg-fill "$img")
  done
  run_once feh "${args[@]}"
}

main() {
  configure_dual_monitors_horizontal_right

  restart_or_start_picom

  for svc in "${SERVICES[@]}"; do
    run_once $svc
  done

  for app in "${DAEMON_APPS[@]}"; do
    "$app" &
  done

  set_wallpapers "${WALLPAPERS[@]}"
}

main


# #!/usr/bin/env bash
# set -euo pipefail
# IFS=$'\n\t'
#
# PRIMARY_OUTPUT="eDP-1"
# EXTERNAL_OUTPUTS=("DP-2-1" "DP-2-2")
#
# # Display settings (mode, rate)
# MODE="1920x1080"
# RATE="60"
#
# # Wallpaper list
# VERT_WALLPAPERS=(
#   "$HOME/Pictures/wallpapers/vert_eoe.png"
#   "$HOME/Pictures/wallpapers/vert_eoe.png"
# )
#
# MIXED_WALLPAPERS=(
#   "$HOME/Pictures/wallpapers/samori.jpg"
#   "$HOME/Pictures/wallpapers/vertical/vert_samori.jpg"
# )
#
# WALLPAPERS=(
#   "$HOME/Pictures/wallpapers/sad_jesus.jpg"
#   "$HOME/Pictures/wallpapers/old_woman_console.jpg"
# )
#
# # Services to start once
# SERVICES=(
#   "nm-applet"
#   "cbatticon"
#   "xfce4-power-manager"
#   "/usr/lib/xfce4/notifyd/xfce4-notifyd"
#   "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1"
#   "numlockx on"
#   "volctl"
#   "wmname LG3D"
#   "unclutter"
# )
#
# # One-off background apps
# DAEMON_APPS=(
#   "slstatus"
#   "keepassxc"
# )
#
# PICOM_CONF="$HOME/.config/dwm/picom.conf"
#
#
# run_once() {
#   local cmd=($@)
#   local name="${cmd[0]}"
#   if ! pgrep -f "$name" >/dev/null; then
#     "${cmd[@]}" &
#   fi
# }
#
# is_connected() {
#   xrandr | grep -q "^$1 connected"
# }
#
# # configure_external_displays [--rotate]
# #   if any EXTERNAL_OUTPUTS are connected, disables PRIMARY_OUTPUT
# #   and arranges externals in order, optionally rotated.
# #   Otherwise falls back to PRIMARY_OUTPUT auto.
# configure_external_displays() {
#   local rotate=false
#   if [[ "${1-}" == "--rotate" ]]; then
#     rotate=true
#   fi
#
#   local connected=()
#   for out in "${EXTERNAL_OUTPUTS[@]}"; do
#     if is_connected "$out"; then
#       connected+=("$out")
#     fi
#   done
#
#   if (( ${#connected[@]} )); then
#     cmd=(xrandr --output "$PRIMARY_OUTPUT" --off)
#     for i in "${!connected[@]}"; do
#       local out=${connected[i]}
#       cmd+=(--output "$out" --mode "$MODE" --rate "$RATE")
#       $rotate && cmd+=(--rotate left)
#       if (( i > 0 )); then
#         cmd+=(--left-of "${connected[i-1]}")
#       fi
#     done
#     "${cmd[@]}"
#   else
#     xrandr --output "$PRIMARY_OUTPUT" --auto
#   fi
# }
#
#
# configure_dual_monitors_vertical_left() {
#   local left="DP-2-2"
#   local right="DP-2-1"
#
#   if is_connected "$left" && is_connected "$right"; then
#     xrandr \
#       --output "$PRIMARY_OUTPUT" --off \
#       --output "$left"  --mode "$MODE" --rate "$RATE" --rotate left \
#       --output "$right" --mode "$MODE" --rate "$RATE" --rotate normal --right-of "$left"
#
#   elif is_connected "$left"; then
#     xrandr \
#       --output "$PRIMARY_OUTPUT" --off \
#       --output "$left" --mode "$MODE" --rate "$RATE" --rotate left
#
#   elif is_connected "$right"; then
#     xrandr \
#       --output "$PRIMARY_OUTPUT" --off \
#       --output "$right" --mode "$MODE" --rate "$RATE" --rotate normal
#
#   else
#     xrandr --output "$PRIMARY_OUTPUT" --auto
#   fi
# }
#
# configure_dual_monitors_horizontal_right() {
#   local left="DP-2-1"
#   local right="DP-2-2"
#
#   if is_connected "$left" && is_connected "$right"; then
#     xrandr \
#       --output "$PRIMARY_OUTPUT" --off \
#       --output "$left"  --mode "$MODE" --rate "$RATE" --rotate normal --left-of "$right" \
#       --output "$right" --mode "$MODE" --rate "$RATE" --rotate normal
#
#   elif is_connected "$left"; then
#     xrandr \
#       --output "$PRIMARY_OUTPUT" --off \
#       --output "$left" --mode "$MODE" --rate "$RATE" --rotate normal
#
#   elif is_connected "$right"; then
#     xrandr \
#       --output "$PRIMARY_OUTPUT" --off \
#       --output "$right" --mode "$MODE" --rate "$RATE" --rotate normal
#
#   else
#     xrandr --output "$PRIMARY_OUTPUT" --auto
#   fi
# }
#
# # restart_or_start_picom
# restart_or_start_picom() {
#   if pgrep -x picom >/dev/null; then
#     kill -USR1 "$(pgrep -x picom)"
#   else
#     picom --config "$PICOM_CONF" --backend glx --vsync --xrender-sync-fence &
#   fi
# }
#
# # apply_wallpapers <list of files>
# set_wallpapers() {
#   local args=()
#   for img in "$@"; do
#     args+=(--bg-fill "$img")
#   done
#   run_once feh "${args[@]}"
# }
#
# main() {
#   configure_dual_monitors_horizontal_right
#
#   restart_or_start_picom
#
#   for svc in "${SERVICES[@]}"; do
#     run_once $svc
#   done
#
#   for app in "${DAEMON_APPS[@]}"; do
#     "$app" &
#   done
#
#   set_wallpapers "${WALLPAPERS[@]}"
# }
#
# main
#
# # configure_dual_monitors_horizontal_right
# # configure_external_displays            
# # configure_external_displays --rotate  
# # configure_dual_monitors_vertical_left
#
# #restart_or_start_picom
#
# # for svc in "${SERVICES[@]}"; do
# #  run_once $svc
# # done
#  
# #for app in "${DAEMON_APPS[@]}"; do
# #  "$app" &
# # done
#
# # set_wallpapers "${WALLPAPERS[@]}"
