@echo off

set startContentPath="F:\Program Files\Epic Games\UE_4.25\Samples\StarterContent\Content\StarterContent"

if "%1" NEQ ""  (
	set startContentPath=%1
)

echo Start Content Path: %startContentPath%

mklink /D /J Content\StarterContent %startContentPath%

attrib +r /D /S Content\StarterContent
Icacls Content\StarterContent\* /L /T /grant:r Everyone:RX

@echo on 