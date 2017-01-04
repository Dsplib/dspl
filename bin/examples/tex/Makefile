LATEX      = pdflatex
FIG_DIR    = fig


FIG	=	fig/complex_plane.pdf\
		fig/complex_plane_op.pdf\
		fig/complex_plane_quater.pdf\
		fig/dft_fig1.pdf\
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
		fig/resample_lagrange_ex_fs.pdf\
		fig/resample_lagrange_ex_time_recalc.pdf\
		fig/resample_lagrange_horner.pdf\
		fig/resample_lagrange_farrow.pdf\
		fig/resample_lagrange_fig1.pdf\
		fig/resample_lagrange_fig2.pdf\
		fig/resample_lagrange_fig3.pdf\
		fig/resample_lagrange_filter_fd_freq.pdf\
		fig/resample_lagrange_filter_fd_time.pdf\
		fig/resample_lagrange_filter_interp.pdf\
		fig/resample_lagrange_frac_delay_in.pdf\
		fig/resample_lagrange_frac_delay_out.pdf\
		fig/resample_lagrange_interp_y.pdf\
		fig/resample_lagrange_opt.pdf\
        fig/resample_lagrange_table_frac_delay.pdf\
		fig/resample_spline_ex_fs.pdf\
		fig/resample_spline_filter_interp.pdf\
		fig/resample_spline_filter_fd_freq.pdf\
		fig/resample_spline_interp_y.pdf\
        fig/resample_spline_opt.pdf\
		fig/resample_spline_polynomials.pdf\
        fig/resample_spline_table_frac_delay.pdf\
		

all: figures clean

	
figures: $(FIG)	
		

#DFT
fig/%.pdf:%.tex fig_header.tex 	
	$(LATEX)  $< -output-directory=$(FIG_DIR) $@
  
	

clean:
	rm -f *.aux
	rm -f *.bbl
	rm -f *.log
	rm -f *.toc
	rm -f *.blg
	rm -f fig/*.aux 
	rm -f fig/*.bbl
	rm -f fig/*.log
	rm -f fig/*.toc
	rm -f fig/*.blg