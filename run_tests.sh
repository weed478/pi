#!/bin/bash

EXEC=$1
IN_FILE=$2
OUT_FILE=$3

if [ -z "$EXEC" ] || [ ! -x "$EXEC" ]; then
  echo "Invalid executable" >&1
  exit 1
fi

if [ -z "$IN_FILE" ] || [ ! -r "$IN_FILE" ]; then
  echo "Invalid input file" >&1
  exit 1
fi

if [ -z "$OUT_FILE" ] || [ ! -r "$OUT_FILE" ]; then
  echo "Invalid output file" >&1
  exit 1
fi

DIFF=$(diff -EbBa --strip-trailing-cr <( "$EXEC" < "$IN_FILE" ) <( cat "$OUT_FILE" ))
RET=$?

if [ "$RET" -eq 0 ]; then
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
