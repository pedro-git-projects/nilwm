#!/usr/bin/env bash
set -Eeuo pipefail
IFS=$'\n\t'

restart_or_start_picom() {
  if pgrep -x picom >/dev/null 2>&1; then
    log_info "picom: reload via SIGUSR1"
    kill -USR1 "$(pgrep -x picom | head -n1)" || true
  else
    log_info "picom: starting"
    bg picom --config "$PICOM_CONF" --backend glx --vsync --xrender-sync-fence
  fi
}
