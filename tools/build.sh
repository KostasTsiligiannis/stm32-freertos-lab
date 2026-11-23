#!/usr/bin/env bash
set -euo pipefail

PRESET="${1:-Debug}"
cmake --preset "${PRESET}"
cmake --build --preset "${PRESET}"
