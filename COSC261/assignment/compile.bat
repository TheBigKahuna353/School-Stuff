@echo off
python ply-compiler.py < program > program.j
java -Xmx100m -jar jasmin.jar program.j
echo Running program
echo:
java -Xmx100m Program