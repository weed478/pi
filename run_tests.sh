#!/bin/bash

EXEC=$1
IN_FILE=$2
OUT_FILE=$3

"$EXEC" > /tmp/pi_test.out < "$IN_FILE"

DIFF=$(diff -w /tmp/pi_test.out "$OUT_FILE")

if [ -z "$DIFF" ]; then
  exit 0
else
  echo "Output:"
  cat /tmp/pi_test.out
  echo "Expected:"
  cat "$OUT_FILE"
  echo "Diff:"
  echo "$DIFF"
  exit 1
fi
