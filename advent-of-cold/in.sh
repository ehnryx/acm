#!/bin/bash
# (./c)


#cookie=???????
cookie=$ADVENT_OF_COLD_COOKIE

day=$DAY;
year=$YEAR;
if [[ -z $year ]]; then
  year=2023
fi

echo -e "Day $day / $year\n"

url="https://adventofcode.com/$year/day/$day/input"

curl "$url" -H "cookie: session=$cookie" --compressed > s;

# DAY=1 ../in.sh
