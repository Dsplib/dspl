function [bin] = load_dat(fn)

fid = fopen(fn);
if(~fid)
	error('cannot to open file');
endif
varCount = fread(fid, 1, "int32");

for k = 1:varCount
	type = fread(fid, 1, "int32");	
	n    = fread(fid, 1, "int32");
	m    = fread(fid, 1, "int32");
	str = fread(fid, [1, 256], "char");
	ind = find(str == 0);
	
	bin{k}.vn = char(str(1:min(ind)));
	
	if(type==0)
		dat = zeros(n,m);
		dat = fread(fid, [n,m], "double");
	endif
	if(type==1)
		datR = zeros(n,m);
		datI = zeros(n,m);
		datR = fread(fid, [n,m], "double");
		datI = fread(fid, [n,m], "double");
		
		dat = datR + 1i * datI;
	endif
	bin{k}.dat = dat;
endfor

fclose(fid);

endfunction