# Makefile for compiling a LaTeX project

# Main document file (without extension)
MAIN = main

# Compiler settings
LATEX = pdflatex
BIBTEX = bibtex
MAKEINDEX = makeindex

# Flags
LATEX_FLAGS = -interaction=nonstopmode -halt-on-error

# Default target
all: pdf

# Compile the LaTeX document
pdf: $(MAIN).tex
	$(LATEX) $(LATEX_FLAGS) $(MAIN).tex
	$(BIBTEX) $(MAIN)
	$(LATEX) $(LATEX_FLAGS) $(MAIN).tex
	$(LATEX) $(LATEX_FLAGS) $(MAIN).tex

# Clean auxiliary files
clean:
	rm -f $(MAIN).aux $(MAIN).bbl $(MAIN).blg $(MAIN).log $(MAIN).out $(MAIN).toc $(MAIN).lof $(MAIN).lot $(MAIN).idx $(MAIN).ilg $(MAIN).ind $(MAIN).synctex.gz $(MAIN).pag $(MAIN).fls $(MAIN).fdb_latexmk

# Clean everything, including the PDF
cleanall: clean
	rm -f $(MAIN).pdf

# View the PDF
view: pdf
	evince $(MAIN).pdf &  # Use "xdg-open" for Linux, "open" for macOS, or "start" for Windows

.PHONY: all pdf clean cleanall view

