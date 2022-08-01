srcFile=JheamStorchRoss.c
buildFile=build/main

gcc --std=gnu89 $srcFile -o $buildFile -lm

for subfolder in ./Testes/*
do
    for testFolder in $subfolder/*
    do
        echo "Testing $testFolder"
        rm -r $testFolder/saida/
        mkdir $testFolder/saida
        $buildFile $testFolder < $testFolder/movimentos.txt > $testFolder/saida/saida.txt
    done
done

diff -r Testes/ Gabarito/
