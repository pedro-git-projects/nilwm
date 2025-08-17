#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

set_wallpapers() {
  (( "$#" >= 1 )) || { log_warn "set_wallpapers: no files provided"; return 0; }

  local args=()
  for img in "$@"; do
    [[ -f "$img" ]] || { log_warn "wallpaper missing: $img"; continue; }
    args+=( --bg-fill "$img" )
  done

  if ((${#args[@]})); then
    log_info "feh ${args[*]}"
    run_once feh "${args[@]}"
  else
    log_warn "set_wallpapers: nothing to set"
  fi
}