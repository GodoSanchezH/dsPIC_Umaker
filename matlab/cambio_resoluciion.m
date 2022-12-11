clc
Datos =  round(out.dato/max(out.dato(:))*(2^8-1));
mplab = sprintf('%.0f,',Datos);
mplab = mplab(1:end-1)
