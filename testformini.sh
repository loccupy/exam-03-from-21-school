gcc testing2.c -o nooriginal -Wall -Wextra -Werror -lm
gcc our_mini_paint.c -o original -Wall -Wextra -Werror -lm
echo ""
echo "TEST - <ex_1>"
echo "NO original"
./nooriginal ./test2/ex_1
echo "Original"
./original ./test2/ex_1
echo ""
echo "TEST - <ex_2>"
echo "NO original"
./nooriginal ./test2/ex_2
echo "Original"
./original ./test2/ex_2
echo ""
echo "TEST - <NULL>"
echo "NO original"
./nooriginal
echo "Original"
./original
echo ""
echo "TEST - <Error file>"
echo "NO original"
./nooriginal ./test2/ex
echo "Original"
./original ./test2/ex
rm nooriginal
rm original