LATEX    = pdflatex
OUT_DIR  = out
TMP_DIR  = tmp

LATEX_FLAGS = -output-directory=$(OUT_DIR) -aux-directory=$(TMP_DIR)


#all:	ex_dspl_butter_ap.pdf\
#	ex_dspl_cheby1_ap.pdf\
all:	ex_dspl_cheby2_ap.pdf\
	
#ex_dspl_butter_ap.pdf:ex_dspl_butter_ap.tex
#	$(LATEX) $(LATEX_FLAGS) ex_dspl_butter_ap.tex	
	
#ex_dspl_cheby1_ap.pdf:ex_dspl_cheby1_ap.tex
#	$(LATEX) $(LATEX_FLAGS) ex_dspl_cheby1_ap.tex

ex_dspl_cheby2_ap.pdf:ex_dspl_cheby2_ap.tex
	$(LATEX) $(LATEX_FLAGS) ex_dspl_cheby2_ap.tex
