#!/bin/bash

startContentPath=/Application/Epic Games/UnrealEngine/Samples/StarterContent/Content/StarterContent

if [ -n "$1" ]; then
	startContentPath=$1
fi

echo Start Content Path: $startContentPath
ln -s $startContentPath Content/StarterContent
chmod u rx Content/StarterContent
