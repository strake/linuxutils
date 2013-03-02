#!/bin/sh

d=''
q=''

while getopts 'dq' o; do
	case $o in
		(d)	d='d';;
		(q)	q='q';;
	esac
done

shift $(dc -e "$OPTIND 1 - p")

exec awk -v x=$1 -v d=$d -v q=$q 'BEGIN { c=1 } { if (x == $5) { if (!q) print "Y"; if (d) print $3; c=0 } } END { if (!q && c) print "N"; exit c }' </proc/self/mountinfo
