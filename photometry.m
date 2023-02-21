 % make sure to download and install LJM library before running this code
% find LJM library at https://labjack.com/support/software/installers/ljm

% Setting up stream-in and stream-out together, then reading
% stream-in values using .NET.
% for info on LabJack methods for Matlab run >> methodsview(LabJack.LJM)


% Creates two sine waves on DAC0 and DAC1 for LED modulation.  DAC0 = 470nm (167Hz) (used amplitude = 0.275
% offset = 0.5 ,about 50uW), 
% DAC1 = 565nm (223Hz) (used amplitude = 0.275 offset = 0.5 ,about 20uW)
% modify frequency and amplitude individually using local variables amplitude, offset and frequency 
% negative peak of sine wave should not go below 0.15V as LED begins to turn off/labjack bottoms out
% modified to record from all three noseports on 3/5/19

% clc  % Clear the MATLAB command window
% clear all % Clear the MATLAB variables

% Make the LJM .NET assembly visible in MATLAB
ljmAsm = NET.addAssembly('LabJack.LJM');

% Creating an object to nested class LabJack.LJM.CONSTANTS
t = ljmAsm.AssemblyHandle.GetType('LabJack.LJM+CONSTANTS');
LJM_CONSTANTS = System.Activator.CreateInstance(t);

handle = 0;


try
    % Open first found LabJack

    % Any device, Any connection, Any identifier
    [ljmError, handle] = LabJack.LJM.OpenS('ANY', 'ANY', 'ANY', handle);


    showDeviceInfo(handle);

    % Setup stream-out
    numAddressesOut = 2; 
    aNamesOut = NET.createArray('System.String', numAddressesOut);
    aNamesOut(1) = 'DAC0';  %address for 167Hz sine wave
    aNamesOut(2) = 'DAC1';  %address for 223Hz sine wave
    aAddressesOut = NET.createArray('System.Int32', numAddressesOut);
    aTypesOut = NET.createArray('System.Int32', numAddressesOut);  % Dummy
    LabJack.LJM.NamesToAddresses(numAddressesOut, aNamesOut, ...
        aAddressesOut, aTypesOut);

    % Allocate memory for the stream-out buffer DAC0 (OUT0)
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_TARGET', aAddressesOut(1));
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_BUFFER_SIZE', 512);
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_ENABLE', 1);
    
    % Allocate memory for the stream-out buffer DAC1 (OUT1)
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT1_TARGET', aAddressesOut(2));
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT1_BUFFER_SIZE', 512);
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT1_ENABLE', 1);
    
    %Write values to the stream-out buffer OUT0 = 470nm @ 167 Hz
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_LOOP_SIZE', 12);
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_BUFFER_F32', 0.6375); 
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_BUFFER_F32', 0.6190);  
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_BUFFER_F32', 0.5685);  
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_BUFFER_F32', 0.4996);  
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_BUFFER_F32', 0.4308);  
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_BUFFER_F32', 0.3806);  
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_BUFFER_F32', 0.3625);  
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_BUFFER_F32', 0.3814);  
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_BUFFER_F32', 0.4322); 
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_BUFFER_F32', 0.5013);  
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_BUFFER_F32', 0.5700);  
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_BUFFER_F32', 0.6199);  


%     OUT1 = 565nm @ 223 Hz
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT1_LOOP_SIZE', 9);
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT1_BUFFER_F32', 0.6374);  
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT1_BUFFER_F32', 0.6011); 
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT1_BUFFER_F32', 0.5172); 
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT1_BUFFER_F32', 0.4252);  
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT1_BUFFER_F32', 0.3685);  
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT1_BUFFER_F32', 0.3736);  
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT1_BUFFER_F32', 0.4383); 
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT1_BUFFER_F32', 0.5321);  
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT1_BUFFER_F32', 0.6107);  
    

    LabJack.LJM.eWriteName(handle, 'STREAM_OUT0_SET_LOOP', 1);
    LabJack.LJM.eWriteName(handle, 'STREAM_OUT1_SET_LOOP', 1);

    [~, value] = LabJack.LJM.eReadName(handle, ...
        'STREAM_OUT2_BUFFER_STATUS', 0);
    disp(['STREAM_OUT2_BUFFER_STATUS = ' num2str(value)])
    
end

    
    
    % Stream-in  configuration

    % Scan list names to stream-in
    numAddressesIn = 13;
    aScanListNames = NET.createArray('System.String', numAddressesIn);
    aScanListNames(1) = 'AIN0'; % photodiode green channel
    aScanListNames(2) = 'AIN1'; % photodiode red channel
    aScanListNames(3) = 'AIN2'; % copy of DAC0 out to 488 LED
    aScanListNames(4) = 'AIN3'; % copy of DAC1 out to 565 LED
    aScanListNames(5) = 'DIO2'; % read in pulses center port
    aScanListNames(6) = 'DIO0'; % read in pulses right port
    aScanListNames(7) = 'DIO1'; % read in pulses left port
    aScanListNames(8) = 'DIO4'; % read in pulses left lick sensor
    aScanListNames(9) = 'DIO5'; % read in pulses right lick sensor
    aScanListNames(10) = 'DIO6'; % read in pulses center LED
    aScanListNames(11) = 'DIO7'; % read in pulses left LED
    aScanListNames(12) = 'DIO20'; % left valve
    aScanListNames(13) = 'DIO21'; % right valve
% MIO0 = 'DIO20' https://labjack.com/support/datasheets/t-series/digital-io/extended-features
    
    % Scan list addresses to stream
    aScanList = NET.createArray('System.Int32', ...
        (numAddressesIn + numAddressesOut));

    % Get stream-in addresses
    aTypes = NET.createArray('System.Int32', numAddressesIn); % Dummy
    LabJack.LJM.NamesToAddresses(numAddressesIn, aScanListNames, ...
        aScanList, aTypes);

    % Add the scan list outputs to the end of the scan list.
    % STREAM_OUT0 = 4800, STREAM_OUT1 = 4801, ...
    aScanList(numAddressesIn+1) = 4800;  % STREAM_OUT0
    aScanList(numAddressesIn+2) = 4801;  % STREAM_OUT1
    

    scanRate = double(2000);  % Scans per second
    scansPerRead = 2000;  % Scans returned by eStreamRead call

    % Stream reads will be stored in aData. Needs to be at least
    % numAddresses*scansPerRead in size.
    aData = NET.createArray('System.Double', numAddressesIn*scansPerRead);

    try
        % When streaming, negative channels and ranges can be configured for
        % individual analog inputs, but the stream has only one settling time
        % and resolution.

            % Ensure triggered stream is disabled.
            LabJack.LJM.eWriteName(handle, 'STREAM_TRIGGER_INDEX', 0);

            % Enabling internally-clocked stream.
            LabJack.LJM.eWriteName(handle, 'STREAM_CLOCK_SOURCE', 0);

            % All negative channels are single-ended, AIN0 and AIN1 ranges are
            % +/-10 V, stream settling is 0 (default) and stream resolution index
            % is 0 (default).
            numFrames = 11;
            aNames = NET.createArray('System.String', numFrames);
            aNames(1) = 'AIN_ALL_NEGATIVE_CH';
            aNames(2) = 'AIN0_RANGE';
            aNames(3) = 'AIN1_RANGE';
            aNames(4) = 'AIN2_RANGE';
            aNames(5) = 'AIN3_RANGE';
            aNames(6) = 'AIN4_RANGE';
            aNames(7) = 'AIN5_RANGE';
            aNames(8) = 'AIN6_RANGE';
            aNames(9) = 'AIN7_RANGE';
            aNames(10) = 'STREAM_SETTLING_US';
            aNames(11) = 'STREAM_RESOLUTION_INDEX';
            aValues = NET.createArray('System.Double', numFrames);
            aValues(1) = LJM_CONSTANTS.GND;
            aValues(2) = 10.0;
            aValues(3) = 10.0;
            aValues(4) = 10.0;
            aValues(5) = 10.0;
            aValues(6) = 10.0;
            aValues(7) = 10.0;
            aValues(8) = 10.0;
            aValues(9) = 10.0;
            aValues(10) = 0;
            aValues(11) = 0;
       %end
        % Write the analog inputs' negative channels (when applicable), ranges
        % stream settling time and stream resolution configuration.
        LabJack.LJM.eWriteNames(handle, numFrames, aNames, aValues, -1);

        % Configure and start stream
        numAddresses = aScanList.Length;
        [~, scanRate] = LabJack.LJM.eStreamStart(handle, scansPerRead, ...
            numAddresses, aScanList, scanRate);

        disp(['Stream started with a scan rate of ' num2str(scanRate) ...
              ' Hz.'])

        % The number of eStreamRead calls to perform in the stream read
        % loop 1 per second 
        maxRequests = 1800;

        % Make a cell array out of scan list names. Helps performance when
        % converting and displaying in the loop.
        aScanListNamesML = cell(aScanListNames);

        tic

        disp(['Performing ' num2str(maxRequests) ' stream reads.'])

        totalScans = 0;
        curSkippedSamples = 0;
        totalSkippedSamples = 0;
        
        DATAM = zeros(maxRequests,scanRate*numAddressesIn); % initialize data matrix numAddressesOut not recorded
        
        for i = 1:maxRequests
            [~, devScanBL, ljmScanBL] = LabJack.LJM.eStreamRead( ...
                handle, aData, 0, 0);

            totalScans = totalScans + scansPerRead;
            DATAM(i,:)=aData.double;
            temp = aData.double;
            %
            save(sprintf('Raw_%d.mat',i+1000),'temp')
            
            
            % Count the skipped samples which are indicated by -9999
            % values. Skipped samples occur after a device's stream buffer
            % overflows and are reported after auto-recover mode ends.
            % When streaming at faster scan rates in MATLAB, try counting
            % the skipped packets outside your eStreamRead loop if you are
            % getting skipped samples/scan.
            curSkippedSamples = sum(double(aData) == -9999.0);
            totalSkippedSamples = totalSkippedSamples + curSkippedSamples;

%             disp(['eStreamRead ' num2str(i)])
%             slIndex = 1;
%             for j = 1:scansPerRead*numAddressesIn
%                 fprintf('  %s = %.4f,', ...
%                         char(aScanListNamesML(slIndex)), aData(j))
%                 slIndex = slIndex + 1;
%                 if slIndex > numAddressesIn
%                     slIndex = 1;
%                     fprintf('\n')
%                 end
%             end
%             disp(['  Scans Skipped = ' ...
%                   num2str(curSkippedSamples/numAddressesIn) ...
%                   ', Scan Backlogs: Device = ' num2str(devScanBL) ...
%                   ', LJM = ' num2str(ljmScanBL)])
        end

        disp(['Performing ' num2str(maxRequests) ' stream reads.'])

        totalScans = 0;
        curSkippedSamples = 0;
        totalSkippedSamples = 0;
        
        %timeElapsed = toc;

%         disp(['Total scans = ' num2str(totalScans)])
%         disp(['Skipped Scans = ' ...
%               num2str(totalSkippedSamples/numAddressesIn)])
%         disp(['Time Taken = ' num2str(timeElapsed) ' seconds'])
%         disp(['LJM Scan Rate = ' num2str(scanRate) ' scans/second'])
%         disp(['Timed Scan Rate = ' num2str(totalScans/timeElapsed) ...
%               ' scans/second'])
%         disp(['Sample Rate = ' ...
%               num2str(numAddressesIn*totalScans/timeElapsed) ...
%               ' samples/second'])
%     catch e
%         showErrorMessage(e)
%     end

    disp('Stop Stream')
    LabJack.LJM.eStreamStop(handle);

    % Close handle
    LabJack.LJM.Close(handle);
catch e
    showErrorMessage(e)
    LabJack.LJM.CloseAll();
end
