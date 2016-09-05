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
		fig/resample_lagrange_horner.pdf\
		fig/resample_lagrange_farrow.pdf\
		fig/resample_lagrange_fig1.pdf\
		fig/resample_lagrange_fig2.pdf\
		fig/resample_lagrange_fig3.pdf\
		fig/resample_lagrange_filter.pdf\
		fig/resample_lagrange_filter_fd_freq.pdf\
		fig/resample_lagrange_filter_fd_time.pdf\
		fig/resample_lagrange_opt.pdf\

		

all: figures clean

	
figures: $(FIG)	
		

#DFT
fig/%.pdf:%.tex fig_header.tex 	
	$(LATEX)  $< -output-directory=$(FIG_DIR) $@
  
	

clean:
	del *.aux
	del *.bbl
	del *.log
	del *.toc
	del *.blg
	del fig\*.aux 
	del fig\*.bbl
	del fig\*.log
	del fig\*.toc
	del fig\*.blg