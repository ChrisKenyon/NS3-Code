%% Lab 4 Measurements

% Declare file names
sinrFile = 'DlRsrpSinrStats.txt';
rlcFile = 'DlRlcStats.txt';

% Load SINR from Phy Traces
fid = fopen(sinrFile);
C = textscan(fid,'%f32%f32%f32%f32%f32%f32','HeaderLines',1);
fclose(fid);
% Chop data appropriately
SinrTimes = C{1};
SinrTimes = SinrTimes(1:2:length(SinrTimes));
SinrData = C{6};
SinrData = SinrData(1:2:length(SinrData));
% Convert to dB
SinrData = 10*log10(SinrData);

% Load RLC stats
fid = fopen(rlcFile);
D = textscan(fid,'%f%f%f%f%f%f%f%f%f%f%[^\n]','HeaderLines',1, 'Delimiter',' ',...
    'MultipleDelimsAsOne',1);
fclose(fid);
% Chop data appropriately
rlcTimes = D{1};
rlcTimes = rlcTimes(1:2:length(rlcTimes));
rlcRxBytes = D{10};
rlcRxBytes = rlcRxBytes(1:2:length(rlcRxBytes));

fprintf('Completed data parsing\n');

% Plot Throughput versus Time
figure(1)
plot(rlcTimes,rlcRxBytes,'r*','markersize',14)
xlabel('Time','FontSize',14)
ylabel('Throughput','FontSize',14)
%xlim([20,50])
title('Throughput Versus Time','FontSize',18)

% Plot SINR versus Time
figure(2)
plot(SinrTimes,SinrData,'bp','markersize',14)
xlabel('Time','FontSize',14)
ylabel('SINR (dB)', 'FontSize', 14)
%ylabel('Average SINR','FontSize',14)
%ylim([0,80])
title('Average SINR Versus Power','FontSize',18)
