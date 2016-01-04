#!/bin/sh
# $FreeBSD: releng/10.2/bin/pkill/tests/pkill-j_test.sh 283312 2015-05-23 09:48:59Z rodrigc $

jail_name_to_jid()
{
	local check_name="$1"
	jls -j "$check_name" -s | tr ' ' '\n' | grep jid= | sed -e 's/.*=//g'
}

base=pkill_j_test

if [ `id -u` -ne 0 ]; then
	echo "1..0 # skip Test needs uid 0."
	exit 0
fi

echo "1..3"

sleep=$(pwd)/sleep.txt
ln -sf /bin/sleep $sleep

name="pkill -j <jid>"
sleep_amount=5
jail -c path=/ name=${base}_1_1 ip4.addr=127.0.0.1 \
    command=daemon -p ${PWD}/${base}_1_1.pid $sleep $sleep_amount &

jail -c path=/ name=${base}_1_2 ip4.addr=127.0.0.1 \
    command=daemon -p ${PWD}/${base}_1_2.pid $sleep $sleep_amount &

$sleep $sleep_amount &

for i in `seq 1 10`; do
	jid1=$(jail_name_to_jid ${base}_1_1)
	jid2=$(jail_name_to_jid ${base}_1_2)
	jid="${jid1},${jid2}"
	case "$jid" in
	[0-9]+,[0-9]+)
		break
		;;
	esac
	sleep 0.1
done
sleep 0.5

if pkill -f -j "$jid" $sleep && sleep 0.5 &&
    ! -f ${PWD}/${base}_1_1.pid &&
    ! -f ${PWD}/${base}_1_2.pid ; then
	echo "ok 1 - $name"
else
	echo "not ok 1 - $name"
fi 2>/dev/null
[ -f ${PWD}/${base}_1_1.pid ] && kill $(cat ${PWD}/${base}_1_1.pid)
[ -f ${PWD}/${base}_1_2.pid ] && kill $(cat ${PWD}/${base}_1_2.pid)
wait

name="pkill -j any"
sleep_amount=6
jail -c path=/ name=${base}_2_1 ip4.addr=127.0.0.1 \
    command=daemon -p ${PWD}/${base}_2_1.pid $sleep $sleep_amount &

jail -c path=/ name=${base}_2_2 ip4.addr=127.0.0.1 \
    command=daemon -p ${PWD}/${base}_2_2.pid $sleep $sleep_amount &

$sleep $sleep_amount &
chpid3=$!
sleep 0.5
if pkill -f -j any $sleep && sleep 0.5 &&
    [ ! -f ${PWD}/${base}_2_1.pid -a
      ! -f ${PWD}/${base}_2_2.pid ] && kill $chpid3; then
	echo "ok 2 - $name"
else
	echo "not ok 2 - $name"
fi 2>/dev/null
[ -f ${PWD}/${base}_2_1.pid ] && kill $(cat ${PWD}/${base}_2_1.pid)
[ -f ${PWD}/${base}_2_2.pid ] && kill $(cat ${PWD}/${base}_2_2.pid)
wait

name="pkill -j none"
sleep_amount=7
daemon -p ${PWD}/${base}_3_1.pid $sleep $sleep_amount
jail -c path=/ name=${base}_3_2 ip4.addr=127.0.0.1 \
    command=daemon -p ${PWD}/${base}_3_2.pid $sleep $sleep_amount &
sleep 1
if pkill -f -j none "$sleep $sleep_amount" && sleep 1 &&
    [ ! -f ${PWD}/${base}_3_1.pid -a -f ${PWD}/${base}_3_2.pid ] ; then
	echo "ok 3 - $name"
else
	ls ${PWD}/*.pid
	echo "not ok 3 - $name"
fi 2>/dev/null
[ -f ${PWD}/${base}_3_1.pid ] && kill $(cat ${base}_3_1.pid)
[ -f ${PWD}/${base}_3_2.pid ] && kill $(cat ${base}_3_2.pid)

rm -f $sleep
