#!/bin/bash
set -o nounset
set -o errexit

cd "$(dirname "$0")"


mkdir -p "$PWD"/../data/lib/plugins/editors
mkdir -p "$PWD"/../data/lib/plugins/tools/kitPlugins
rsync -a "$BIN_DIR"/plugins/editors/libev3Metamodel.so                      "$PWD"/../data/lib/plugins/editors/
rsync -a "$BIN_DIR"/plugins/tools/kitPlugins/librobots-ev3-interpreter.so   "$PWD"/../data/lib/plugins/tools/kitPlugins/
rsync -a "$BIN_DIR"/plugins/tools/kitPlugins/librobots-ev3-rbf-generator.so "$PWD"/../data/lib/plugins/tools/kitPlugins/
rsync -a "$BIN_DIR"/librobots-ev3-kit.so*                                   "$PWD"/../data/lib
rsync -a "$BIN_DIR"/librobots-ev3-generator-base.so*                        "$PWD"/../data/lib

cp -L  "$(pkg-config --variable=libdir libusb-1.0)/libusb-1.0.so"         "$PWD"/../data/lib/libusb-1.0.so

# Cleaning up prebuild-common.sh results...
rm -rf "$PWD"/../data/plugins/
mkdir -p "$PWD"/../data/resources/examples/

rsync -av --remove-source-files "$PWD"/../data/examples/ "$PWD"/../data/resources/examples/

cd "$PWD"/../data/lib/
ln -svf libusb-1.0.so libusb-1.0.so.0
