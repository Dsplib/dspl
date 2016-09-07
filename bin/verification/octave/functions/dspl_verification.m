function dspl_verification(msg, x, y)

str = msg;
while(length(str) < 48)
	str = [str, '.'];
end

fid = fopen('../../../verification.log', 'a+');

fprintf(fid, '%s', str);
fprintf('%s', str);
maxy = max(abs(y));


if(maxy==0)
	fprintf('STOPED max(y) =0 \n');
	fprintf(fid, 'STOPED max(y) =0 \n');
end

err = max(abs(x-y))/maxy;

if(err < 10E-9)
	fprintf('OK     err = %10.6E\n', err);
	fprintf(fid, 'OK     err = %10.6E\n', err);
else
	fprintf('ERROR  err = %10.6E\n', err);
	fprintf(fid, 'ERROR  err = %10.6E\n', err);
end	