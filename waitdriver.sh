#! /bin/sh

DEVICE_TO_CHECK='/dev/video0'
GROUP_OK='video'
TIMEOUT=5


############
#   MAIN   #
############

echo '   //--------------------------//'
echo '   //      TWS Automation      //'
echo '   //--------------------------//'

# wait driver to be loaded
echo ''
echo -n '  Please wait ...'

for i in `seq 1 5`
do
	echo -n '.'
	sleep 1
done

# wait GID to became video
echo ''
echo -n '  Hardware driver init ...'

for i in `seq 1 $TIMEOUT`
do
	group=`ls -l $DEVICE_TO_CHECK | awk '{ print $4 }'`
	#echo "video1  GID: " $group " [$i]"

	if [ "$group" != "$GROUP_OK" ]
	then
		echo -n '.'
	else
		break
	fi

	sleep 1
done

echo ''
echo ''
echo ''
