LATEX      = pdflatex
FIG_DIR    = fig


FIG	=	fig/dft_fig1.pdf\
		fig/dft_fig2.pdf\
		fig/dft_fig3.pdf\
		fig/dft_fig4.pdf\
		fig/dft_freq_fig1.pdf\
		fig/dft_freq_fig2.pdf\
		fig/dft_freq_fig3.pdf\
		fig/dft_freq_fig4.pdf\
		fig/dft_prop_fig1.pdf\
		fig/dft_prop_fig2.pdf\
		fig/dft_prop_fig3.pdf\
		fig/dft_prop_fig4.pdf\
		fig/fft_introduction_fig1.pdf\
		fig/fft_introduction_fig2.pdf\
		fig/fft_introduction_fig3.pdf\
		fig/fft_dec_in_time_fig1.pdf\
		fig/fft_dec_in_time_fig2.pdf\
		fig/fft_dec_in_time_fig3.pdf\
		fig/fft_dec_in_time_fig4.pdf\
		fig/fft_dec_in_freq_fig1.pdf\
		fig/fft_dec_in_freq_fig2.pdf\
		fig/fft_dec_in_freq_fig3.pdf\
		fig/fft_performance_fig3.pdf\
		fig/goertzel_dtmf_freq.pdf\
		fig/goertzel_dtmf_time.pdf\
		fig/goertzel_dtmf_symbols.pdf\
		fig/goertzel_fig1.pdf\
		fig/goertzel_fig2.pdf\
		fig/goertzel_fig3.pdf\
		fig/hilbert_fft.pdf\
		fig/resample_lagrange_farrow.pdf\
		fig/resample_lagrange_fig1.pdf\
		fig/resample_lagrange_filter.pdf\


		

all: figures clean

	
figures: $(FIG)	
		

#DFT
fig/%.pdf:%.tex fig_header.tex 	
	$(LATEX)  $< -output-directory=$(FIG_DIR) $@
  
	

clean:
	rm -f  *.aux
	rm -f  *.bbl
	rm -f  *.log
	rm -f  *.toc
	rm -f  *.blg
	rm -f  fig/*.aux 
	rm -f  fig/*.bbl
	rm -f  fig/*.log
	rm -f  fig/*.toc
	rm -f  fig/*.blg