#!/bin/bash

twitchURLBase="https://www.twitch.tv/"
username=$1
htmlFile="temp.html"

fullURL=$twitchURLBase$username

while true; do
	curl -Ls $fullURL > $htmlFile
	if grep -q ":true" $htmlFile; then
		echo LIVE
		yt-dlp $fullURL
	else
		#set to 2 seconds for debugging. Will be 5 min later (300s)
		echo OFFLINE - Will check again in 2 seconds $'\n'
		sleep 2
	fi
	rm $htmlFile
done