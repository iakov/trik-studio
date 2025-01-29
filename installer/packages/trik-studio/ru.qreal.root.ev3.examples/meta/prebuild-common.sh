#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"

mkdir -p "$PWD"/../data/examples
rsync -a  "$BIN_DIR"/examples/ev3                                             "$PWD"/../data/examples
