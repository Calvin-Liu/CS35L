#!/bin/bash

sed 'N;s/<tr>\r\n *<td>.*<\/td>//g;P;D' | \
grep "<td>" | \
tr '[:upper:]' '[:lower:]' | \
sed 's/<td>//g' | \
sed 's/<\/td>//g' | \
sed 's/<\/u>//g' | \
sed 's/<u>//g' | \
sed 's/,/\n/g' | \
sed "s/\`/\'/g" | \
sed 's/<br>//g' | \
sed 's/[ ]/\n/g' | \
tr -cs "A-Za-z\'" '[\n*]' | \
sort -u
