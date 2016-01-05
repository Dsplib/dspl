function [dat, n, m] = dspl_readbin(fn)

fid = fopen(fn);
if(~fid)
	error('cannot to open file');
end
type = fread(fid, 1, 'int32');	
n    = fread(fid, 1, 'int32');
m    = fread(fid, 1, 'int32');

if(type==0)
	dat = zeros(n,m);
	dat = fread(fid, [n,m], 'double');
end
if(type==1)
	datR = zeros(n,m);
	datI = zeros(n,m);
	datR = fread(fid, [n,m], 'double');
	datI = fread(fid, [n,m], 'double');
	
	dat = datR + 1i * datI;
end

fclose(fid);

end