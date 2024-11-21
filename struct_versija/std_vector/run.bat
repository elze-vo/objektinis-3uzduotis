cmake -DCMAKE_BUILD_TYPE=Release .
cmake --install . --config Release
cmake --build . --config Release
copy src\stud1000.txt Release\stud1000.txt
copy src\stud10000.txt Release\stud10000.txt
cd Release
pause
