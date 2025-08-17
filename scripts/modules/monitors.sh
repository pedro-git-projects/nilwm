#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

# Use MODE/RATE/PRIMARY_OUTPUT/EXTERNAL_OUTPUTS from config.sh

configure_external_displays() {
  local rotate="${1:-}"  # pass "--rotate" for left rotation
  local connected=()

  for out in "${EXTERNAL_OUTPUTS[@]}"; do
    if is_connected "$out"; then
      connected+=( "$out" )
    fi
  done

  if ((${#connected[@]})); then
    local cmd=( xrandr --output "$PRIMARY_OUTPUT" --off )
    for i in "${!connected[@]}"; do
      local out="${connected[i]}"
      cmd+=( --output "$out" --mode "$MODE" --rate "$RATE" )
      [[ "$rotate" == "--rotate" ]] && cmd+=( --rotate left )
      (( i > 0 )) && cmd+=( --left-of "${connected[i-1]}" )
    done
    log_info "xrandr: ${cmd[*]}"
    "${cmd[@]}"
  else
    log_info "xrandr: no externals; using primary auto"
    xrandr --output "$PRIMARY_OUTPUT" --auto
  fi
}

# keep laptop on when exactly one external is connected; external goes to the right.
# with two externals: laptop off, externals side-by-side.
configure_dual_monitors_horizontal_right() {
  local left="DP-2-1"
  local right="DP-2-2"

  if is_connected "$left" && is_connected "$right"; then
    log_info "xrandr: two externals; laptop off; externals side-by-side"
    xrandr \
      --output "$PRIMARY_OUTPUT" --off \
      --output "$left"  --mode "$MODE" --rate "$RATE" --rotate normal --left-of "$right" \
      --output "$right" --mode "$MODE" --rate "$RATE" --rotate normal

  elif is_connected "$left"; then
    log_info "xrandr: left external only; keep laptop on"
    xrandr \
      --output "$PRIMARY_OUTPUT" --auto \
      --output "$left" --mode "$MODE" --rate "$RATE" --rotate normal --right-of "$PRIMARY_OUTPUT"

  elif is_connected "$right"; then
    log_info "xrandr: right external only; keep laptop on"
    xrandr \
      --output "$PRIMARY_OUTPUT" --auto \
      --output "$right" --mode "$MODE" --rate "$RATE" --rotate normal --right-of "$PRIMARY_OUTPUT"

  else
    log_info "xrandr: no externals; laptop only"
    xrandr --output "$PRIMARY_OUTPUT" --auto
  fi
}

# optional alternate layout:
configure_dual_monitors_vertical_left() {
  local left="DP-2-2"
  local right="DP-2-1"

  if is_connected "$left" && is_connected "$right"; then
    xrandr \
      --output "$PRIMARY_OUTPUT" --off \
      --output "$left"  --mode "$MODE" --rate "$RATE" --rotate left \
      --output "$right" --mode "$MODE" --rate "$RATE" --rotate normal --right-of "$left"

  elif is_connected "$left"; then
    xrandr \
      --output "$PRIMARY_OUTPUT" --off \
      --output "$left" --mode "$MODE" --rate "$RATE" --rotate left

  elif is_connected "$right"; then
    xrandr \
      --output "$PRIMARY_OUTPUT" --off \
      --output "$right" --mode "$MODE" --rate "$RATE" --rotate normal

  else
    xrandr --output "$PRIMARY_OUTPUT" --auto
  fi
}