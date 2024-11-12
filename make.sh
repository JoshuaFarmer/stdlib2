gcc -c "src/array.c" -o "bin/array.o" -Wall -Wextra -I "./inc" -g -march=x86-64 -Wpedantic
gcc -c "src/files.c" -o "bin/files.o" -Wall -Wextra -I "./inc" -g -march=x86-64 -Wpedantic
gcc -c "src/io.c" -o "bin/io.o" -Wall -Wextra -I "./inc" -g -march=x86-64 -Wpedantic
gcc -c "src/linked.c" -o "bin/linked.o" -Wall -Wextra -I "./inc" -g -march=x86-64 -Wpedantic

gcc -c "src/stdlib2.c" -o "bin/std2.o" -Wall -Wextra -I "./inc" -g -march=x86-64

ar rcs libstd2.a "bin/std2.o" "bin/files.o" "bin/array.o" "bin/io.o" "bin/linked.o"

gcc test.c -L. -lstd2 -o test -I "./inc" -Wall -Wextra
