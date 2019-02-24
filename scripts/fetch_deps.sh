#!/bin/bash

cd $(dirname "${BASH_SOURCE[0]}")/..
mkdir -p cutter-deps && cd cutter-deps

FILE=cutter-deps.tar.gz
MD5=4df166631678633d6cf439792b66263c
URL=https://github.com/thestr4ng3r/cutter-deps/releases/download/untagged-59c9e54950e6d2824cb8/cutter-deps.tar.gz

curl -L "$URL" -o "$FILE" || exit 1
echo "$MD5 $FILE" | md5sum -c - || exit 1
tar -xf "$FILE" || exit 1
./relocate.sh || exit 1

