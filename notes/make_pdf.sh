#!/bin/bash
pdf=".pdf"
for note in "$@"
do
	withoutExt=${note%.*}
	pandoc ${note} -o ${withoutExt}${pdf} -V geometry:margin=1in --highlight-style tango -s
done