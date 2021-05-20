CC = gcc

objects = bank.o  bank_aux.o 

banker: $(objects)
	$(CC) -o banker $(objects)


bank.o: b.h

bank_aux.o: b.h

b.o: b.h

.PHONY: clean
clean:
	rm $(objects) banker result.txt
