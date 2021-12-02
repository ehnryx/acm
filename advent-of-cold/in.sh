#!/bin/bash
# (./c)


cookie=???????


day=$DAY;
year=$YEAR;
if [[ -z $year ]]; then
  year=2021
fi

echo -e "Day $day / $year\n"

url="https://adventofcode.com/$year/day/$day/input"

curl $url -H "cookie: session=$cookie" --compressed > s;

