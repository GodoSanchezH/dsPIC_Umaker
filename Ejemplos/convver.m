function [y]=convver(x,form)
option = {'mode','roundmode','overflowmode','format'};
value = {'fixid','ceil','saturate',[16 15]};

q=quantizer(option,value)
if form == 'bin'
    y=num2bin(q,x)
end;
if form == 'hex'
      y=num2bin(q,x)
end;  
end

