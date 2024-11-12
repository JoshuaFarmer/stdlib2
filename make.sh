gcc -c "src/array.c" -o "bin/array.o" -Wall -Wextra -I "./inc" -g -march=x86-64
gcc -c "src/files.c" -o "bin/files.o" -Wall -Wextra -I "./inc" -g -march=x86-64
gcc -c "src/io.c" -o "bin/io.o" -Wall -Wextra -I "./inc" -g -march=x86-64
gcc -c "src/stdlib2.c" -o "bin/std2.o" -Wall -Wextra -I "./inc" -g -march=x86-64
ar rcs libstd2.a "bin/std2.o" "bin/files.o" "bin/array.o" "bin/io.o"

# gcc example7.c -L. -lstd2 -o myprogram -I "./" -Wall -Wextra
# gcc example2.c -L. -lstd2 -o myprogram2 -I "./" -Wall -Wextra
