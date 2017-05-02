LATEX				= pdflatex
TEX_DIR				= fig
ANIM_TEX_DIR		= anim
	
RU_PDF_DIR			= fig/ru/pdf
RU_SVG_DIR			= fig/ru/svg
RU_TEX_DIR			= fig/ru

RU_ANIM_PDF_DIR		= anim/ru/pdf
RU_ANIM_TEX_DIR		= anim/ru

EN_PDF_DIR			= fig/en/pdf
EN_SVG_DIR			= fig/en/svg
EN_TEX_DIR			= fig/en

EN_ANIM_PDF_DIR		= anim/en/pdf
EN_ANIM_TEX_DIR		= anim/en

TEX_FILES 		:= $(wildcard $(TEX_DIR)/*.tex)
RU_PDF_FILES 	:= $(addprefix $(RU_PDF_DIR)/,$(notdir $(TEX_FILES:.tex=.pdf)))
EN_PDF_FILES 	:= $(addprefix $(EN_PDF_DIR)/,$(notdir $(TEX_FILES:.tex=.pdf)))
RU_SVG_FILES 	:= $(addprefix $(RU_SVG_DIR)/,$(notdir $(TEX_FILES:.tex=.svg)))
EN_SVG_FILES 	:= $(addprefix $(EN_SVG_DIR)/,$(notdir $(TEX_FILES:.tex=.svg)))

ANIM_TEX_FILES		:= $(wildcard $(ANIM_TEX_DIR)/*.tex)
RU_ANIM_PDF_FILES 	:= $(addprefix $(RU_ANIM_PDF_DIR)/,$(notdir $(ANIM_TEX_FILES:.tex=.pdf)))
EN_ANIM_PDF_FILES 	:= $(addprefix $(EN_ANIM_PDF_DIR)/,$(notdir $(ANIM_TEX_FILES:.tex=.pdf)))

all: figures clean
	
figures:	$(RU_PDF_FILES) $(EN_PDF_FILES)\
			$(RU_SVG_FILES) $(EN_SVG_FILES)\
			$(RU_ANIM_PDF_FILES)\
			$(EN_ANIM_PDF_FILES)\
	
#DFT
$(RU_PDF_DIR)/%.pdf:$(TEX_DIR)/%.tex $(RU_TEX_DIR)/header.htex 
	cp $(RU_TEX_DIR)/header.htex	header.htex
	$(LATEX) --output-directory=$(RU_PDF_DIR) $< --shell-escape 
	$(LATEX) --output-directory=$(RU_PDF_DIR) $< --shell-escape 
	
	
$(RU_SVG_DIR)/%.svg:$(RU_PDF_DIR)/%.pdf
	pdf2svg $< $@

	
$(EN_PDF_DIR)/%.pdf:$(TEX_DIR)/%.tex $(EN_TEX_DIR)/header.htex 
	cp $(EN_TEX_DIR)/header.htex	header.htex
	$(LATEX) --output-directory=$(EN_PDF_DIR) $< --shell-escape 
	$(LATEX) --output-directory=$(EN_PDF_DIR) $< --shell-escape 

$(EN_SVG_DIR)/%.svg:$(EN_PDF_DIR)/%.pdf
	pdf2svg $< $@
	
$(RU_ANIM_PDF_DIR)/%.pdf:$(ANIM_TEX_DIR)/%.tex
	cp $(RU_ANIM_TEX_DIR)/header.htex	header.htex
	$(LATEX) --output-directory=$(RU_ANIM_PDF_DIR) $< --shell-escape 
	$(LATEX) --output-directory=$(RU_ANIM_PDF_DIR) $< --shell-escape
	
$(EN_ANIM_PDF_DIR)/%.pdf:$(ANIM_TEX_DIR)/%.tex
	cp $(EN_ANIM_TEX_DIR)/header.htex	header.htex
	$(LATEX) --output-directory=$(EN_ANIM_PDF_DIR) $< --shell-escape 
	$(LATEX) --output-directory=$(EN_ANIM_PDF_DIR) $< --shell-escape	
	
clean:
	rm -f $(RU_ANIM_PDF_DIR)/*.aux
	rm -f $(RU_ANIM_PDF_DIR)/*.bbl
	rm -f $(RU_ANIM_PDF_DIR)/*.log
	rm -f $(RU_ANIM_PDF_DIR)/*.toc
	rm -f $(RU_ANIM_PDF_DIR)/*.blg
	rm -f $(EN_ANIM_PDF_DIR)/*.aux
	rm -f $(EN_ANIM_PDF_DIR)/*.bbl
	rm -f $(EN_ANIM_PDF_DIR)/*.log
	rm -f $(EN_ANIM_PDF_DIR)/*.toc
	rm -f $(EN_ANIM_PDF_DIR)/*.blg
	rm -f $(RU_PDF_DIR)/*.aux
	rm -f $(RU_PDF_DIR)/*.bbl
	rm -f $(RU_PDF_DIR)/*.log
	rm -f $(RU_PDF_DIR)/*.toc
	rm -f $(RU_PDF_DIR)/*.blg
	rm -f $(EN_PDF_DIR)/*.aux
	rm -f $(EN_PDF_DIR)/*.bbl
	rm -f $(EN_PDF_DIR)/*.log
	rm -f $(EN_PDF_DIR)/*.toc
	rm -f $(EN_PDF_DIR)/*.blg	
	rm -f *.htex