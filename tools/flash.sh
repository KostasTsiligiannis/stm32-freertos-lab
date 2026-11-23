#!/usr/bin/env bash
set -euo pipefail

PRESET="${1:-Debug}"
ELF_PATH="build/${PRESET}/stm32f303-freertos-lab.elf"

if [ ! -f "${ELF_PATH}" ]; then
  echo "Δεν βρέθηκε το ${ELF_PATH}. Κάνε πρώτα build."
  exit 1
fi

sudo openocd -f board/st_nucleo_f3.cfg -c "program ${ELF_PATH} verify reset exit"
