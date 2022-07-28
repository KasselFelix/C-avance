S3DIR="../../S3/Solution"
S5DIR="../../S5/Solution"
GCC_FLAGS=-Wall -g -I $(S3DIR) -I $(S5DIR)
LINK_FLAGS=-L $(S3DIR) -L $(S5DIR)
CC=gcc
EXE=main_huffman

all: $(EXE)

%.o: %.c
	$(CC) $(GCC_FLAGS) -c $^

main_huffman: arbre_freq.o huffman.o main_huffman.o
	$(CC) $(GCC_FLAGS)  $(LINK_FLAGS) -o $@ $^ -l liste -l arbre_binaire

clean:
	rm -f *.o $(EXE) *~ 
