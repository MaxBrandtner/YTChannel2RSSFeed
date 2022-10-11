#!/bin/bash
# $1 input URL

#name check
echo $1 2>/dev/null | grep "/videos" >/dev/null 2>&1
change_name=$?

if [ $change_name != 0 ]
then
	YT_URL=$(echo "$1/videos")
else
	YT_URL=$(echo "$1")
fi


channelId=$(curl -L $YT_URL 2>/dev/null | grep channelId | sed -e 's/.*channelId//g' -e 's/"//' -e 's/^[^\"]*"//' -e 's/".*//' | head -n 1)

RSS_URL=$(echo "https://www.youtube.com/feeds/videos.xml?channel_id=$channelId")

echo $RSS_URL