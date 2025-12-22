mkcd(){ mkdir -p "$1" && cd "$1"; }
git-root(){ cd "$(git rev-parse --show-toplevel 2>/dev/null)" || return; }
