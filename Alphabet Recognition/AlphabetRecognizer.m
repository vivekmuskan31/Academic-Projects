clc;
clear all
close all;

%% Main Variables
x = zeros;                      % Test Audio File
Name = strings([26,25]);        % File Names of Training Data
Max_Correlation(26) = zeros;    % Maximum correlation values 
%% Creating voice recorder
recorder  = audiorecorder(44664,16,2);
%% Test Data
prompt = 'Enter 1 for audio file or 2 for recorded voice :';
t = input(prompt);
%% Getting Audio File
if t==1
    prompt = 'Enter the Audio file Name: ';
    fileName = input(prompt,'s');
    x = audioread(fileName);
    sound(x);
    disp('Recognising...');
    x = x(:,1);
end
%% Getting Recorded Voice
if t==2
    disp('Say Now : ');
    recordblocking(recorder,2);
    play(recorder);
    x = getaudiodata(recorder);
    disp('Recognising...');
    x = x(:,1);
end
%% Amplitude Normalisation
%x = x/norm(x);
%% File Names of Training Audio Data
for i=1:26
    alphaCode = char(i+64);
    for j=1:25
        fileType = '.wav';
        common = 'test';
        freqType = int2str(j+5);
        Name(i,j) = strcat(common, freqType, alphaCode, fileType);
    end
end
M(26,25) = zeros;
%% Algorithm to find Maximum Similarity of signals
for i=1:26
    for j=1:25
        y=audioread(Name(i,j));
        y = y(:,1);
        %y = y/norm(y);                                              % Amplitude Normalisation
        M(i,j) = max(xcorr(x,y));   % Sum over all possible data
    end
end

for i=1:26
    for j=1:25
        Max_Correlation(i) = Max_Correlation(i) + M(i,j);
    end
end

%disp(Max_Correlation');
[val, idx] = max(Max_Correlation);
Answer = char(idx+64);
disp(Answer);