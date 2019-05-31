function Create_Data()
% This function creates the model data depicted in Figure 4-6 of
%
% Characterization of K-Complexes and Slow Wave Activity in a Neural Mass Model
% A Weigenand, M Schellenberger Costa, H-VV Ngo, JC Claussen, T Martinetz
% PLoS Computational Biology. 2014;10:e1003923

% Move to source folder(assuming it contains the Figures folder
cd ..;

% Check if the executable exists and compile if needed
if(exist('Cortex_mex.mesa64', 'file')==0)
    mex CXXFLAGS="\$CXXFLAGS -std=c++11 -O3" Cortex_mex.cpp Cortical_Column.cpp;
end

% Add the path to the simulation routine
addpath(pwd);

% Go back into figures folder
cd Figures;

% Time series
Data_Time_Series(1);
Data_Time_Series(2);

% Time series
Data_Stimulation();
end
