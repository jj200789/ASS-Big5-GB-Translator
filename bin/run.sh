#!/bin/bash

cd -- "$(dirname "$0")"
./translator -m $1 -c data/s2hk.json -s $2 -d $2.BIG5.ass
