.PHONY: all

all: minireport.pdf

%.pdf: %.tex
	latexmk -xelatex -quiet "$*" || { cat "$*.log"; exit 1; }

clean:
	latexmk -C
