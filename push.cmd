@echo off
git stage *
git commit * -m "commit via push.cmd"
git push origin master
pause