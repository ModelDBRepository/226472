function Data_Stimulation
% This function creates the model data depicted in Figure 4 of
%
% Characterization of K-Complexes and Slow Wave Activity in a Neural Mass Model
% A Weigenand, M Schellenberger Costa, H-VV Ngo, JC Claussen, T Martinetz
% PLoS Computational Biology. 2014;10:e1003923

% To ensure availability of the simulation routine it should be called from Create_Data.m

% Parameter settings
Param_N3    = [ 6.5;	% sigma_e
                2;	% g_KNa
                0E-3];	% dphi


Param_N2    = [ 4.6;	% sigma_e
                1.33;	% g_KNa
                0E-3];	% dphi

% stimulation parameters
% first number is the mode of stimulation
% 0 == none
% 1 == semi-periodic
% 2 == phase dependend
var_stim = [1;          % mode of stimulation
	    100;        % strength of the stimulus              in Hz (spikes per second)
	    100;       	% duration of the stimulus              in ms
	    7;          % time between stimulation events       in s  (ISI)
	    2;          % range of ISI                          in s  [ISI-range,ISI+range]
	    1;          % Number of stimuli per event
	    0;          % time between stimuli within a event   in ms
	    0];         % time until stimuli after minimum      in ms
            
% Number of runs for stimulation, as well as color set            
N = 15;

% time of the stimulation
T     = 4;
Ve_N2 = cell(N,1);
Ve_N3 = cell(N,1);

for i=1:N 
    var_stim(2)= i*10;
    [Ve_N2{i}, ~]    = Cortex_mex(T, Param_N2, var_stim);
    [Ve_N3{i}, ~]    = Cortex_mex(T, Param_N3, var_stim);
end

save('Data/Stimulation.mat', 'Ve_N2', 'Ve_N3');
end
