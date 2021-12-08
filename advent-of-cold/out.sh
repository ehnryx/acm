#!/bin/bash
# (./r)


cookie=???????


last=""
while read -r line; do
  echo "$line"
  last="$line"
done

echo -e "\nSubmitting: $last\n"


day=$DAY;
year=$YEAR;
if [[ -z $year ]]; then
  year=2021
fi

echo -e "Day $day / $year\n"

url="https://adventofcode.com/$year/day/$day/answer"

out=$(curl $url -X POST -d "level=$1&answer=$last" -H "cookie: session=$cookie" \
  | tr '\n' ' ' | sed 's/.*<main>//g' | sed 's/<\/main>.*//g' | sed 's/<a href.*//g' \
  | sed 's/.*<article><p>//g' | sed 's/<\/p><\/article>.*//g' \
  | sed 's/You are <span.*//g' | sed 's/there are also some.*//g')

echo -e "\n$out\n"
