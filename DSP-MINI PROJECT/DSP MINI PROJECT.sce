clc;
clear;
clear all;
[y,fs] = wavread("C:\Users\ASUS\Downloads\dsp01.wav");
playsnd(y,fs);
halt('Original');
//Flanging
z = 0;
n = 1:length(y);
z(n) = y(n);
m = 11:length(y);
x(m) = z(m) + 0.8*z(m-10).*cos(2*%pi*m/fs);
playsnd(x,fs);
halt('Flange');
//Echo
a = 0.5;
[l,fs] = wavread("C:\Users\ASUS\Downloads\dsp01.wav");
len = length(l);
delay = 0.4;
D = ceil(fs*delay);
m = zeros(max(size(l)));
for i = D+1:len
  m(i) = l(i) + a*l(i-D);
end
playsnd(m,fs);
halt('Echo');
//Equalizer
//For Low frequencies
[h,fs] = wavread("C:\Users\ASUS\Downloads\dsp01.wav");
playsnd(h,fs);
j = iir(3,'bp','butt',[.01 .05],[0.03 0.03]);
k = flts(h(1,:),j);
playsnd(k,fs);
halt('Low');
//For High frequencies
[h,fs] = wavread("C:\Users\ASUS\Downloads\dsp01.wav");
playsnd(h,fs);
halt('High');
//For Very low frequencies
j = iir(3,'bp','butt',[.15 .25],[0.03 0.03]);
k = flts(h(1,:),j);
playsnd(k,fs);
halt('Very low');
