clc;
clear all;
close all;

%% Create a recorder
recorder  = audiorecorder(44664,16,2);

%% Recording
prompt = 'Enter Sample Number:';
SNo = input(prompt);
sno = int2str(SNo);
disp('Record Complete Alphabet when it prints "Say Alphabet"');
for i=1:26
    alphaCode = char(i+64);
    fprintf('Say %s\n',alphaCode);
    recordblocking(recorder,2);
    y = getaudiodata(recorder);
    y=y(1:89328);
    fileType = '.wav';
    common = 'test';
    fileName = strcat(common, sno, alphaCode, fileType);
    audiowrite(fileName,y,40000);
end