for i in data-sets/*
do
	./a.out < $i
	printf "\n"
done
