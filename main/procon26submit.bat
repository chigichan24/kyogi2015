@echo off

set /p ispractice="practice or production > "

set host=172.16.1.2
set token=c407ad05b53f4b05

if %ispractice%==practice (
	set host=http://testform26.procon-online.net
	set token=0123456789abcdef
)

set /p input="get or submit > "

if %input%==get (
	set /p number="number of quest > "
	curl '%host%/quest%number%.txt?token=%token%' > input.txt

) else (
	set /p answer="answer file name > "
	curl '%host%/answer' --form-string 'token=%token%' -F 'answer=@%answer%'
)

