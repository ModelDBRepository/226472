function Data_Time_Series(mode)
% This function creates the model data depicted in Figure 5-6 of
%
% Characterization of K-Complexes and Slow Wave Activity in a Neural Mass Model
% A Weigenand, M Schellenberger Costa, H-VV Ngo, JC Claussen, T Martinetz
% PLoS Computational Biology. 2014;10:e1003923

% To ensure availability of the simulation routine it should be called from Create_Data.m

% Parameter settings
switch(mode)
case 1:
	Param_N3 = [ 6.5;	% sigma_e
		     2;		% g_KNa
		     0E-3];	% dphi

case 2:
	Param_N2 = [ 4.6;	% sigma_e
		     1.33;	% g_KNa
		     0E-3];	% dphi
end

% No stimulation so set everything to zero
var_stim      = zeros(8,1);
            
% Duration of the stimulation
T     	      = 15;

% Run the two simulations
[Ve_N2{i}, ~] = Cortex_mex(T, Param_N2, var_stim);
[Ve_N3{i}, ~] = Cortex_mex(T, Param_N3, var_stim);

save('Data/EEG_Data_N2.mat', 'Ve_N2');
save('Data/EEG_Data_N3.mat', 'Ve_N3');
end
