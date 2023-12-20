#!/bin/bash -e

PLACE="/place"
LOCK_PATH="/place/locker"

findFilename() {
  local index=1
  while true; do
    filename=$(printf "%03d" $index)
    if [ ! -f "$PLACE/$filename" ]; then
      break
    fi
    ((index++))
  done
  filename_no_zeros=$((10#$filename))
}

generateRandomContainerID() {
  echo $(shuf -i 10000-99999 -n 1)
}

CONTAINER_ID=$(generateRandomContainerID)

createAndWriteFile() {
  exec {fd}>$LOCK_PATH
  flock "$fd"
  getFilename

  echo "$CONTAINER_ID $filename_no_zeros" > "$PLACE/$filename"

  flock -u "$fd"

  echo "$CONTAINER_ID created $filename"
}

deleteAndDisplayFile() {
  text=$(<"$PLACE/$filename")
  rm -f "$PLACE/$filename"
  echo "$CONTAINER_ID deleted $filename : $text"
}

while true; do
  createAndWriteFile
  sleep 1
  deleteAndDisplayFile
done
