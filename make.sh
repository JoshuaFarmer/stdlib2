gcc -c "std2/array.c" -o "bin/array.o" -Wall -Wextra -I "./" -g -march=x86-64
gcc -c "std2/files.c" -o "bin/files.o" -Wall -Wextra -I "./" -g -march=x86-64
gcc -c "std2/stdlib2.c" -o "bin/std2.o" -Wall -Wextra -I "./" -g -march=x86-64
ar rcs libstd2.a "bin/std2.o" "bin/files.o" "bin/array.o"

gcc example.c -L. -lstd2 -o myprogram -I "./"
gcc example2.c -L. -lstd2 -o myprogram2 -I "./"