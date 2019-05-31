function Plot_Bifurcation_1D()
% This function creates Figure 3 of
%
% Characterization of K-Complexes and Slow Wave Activity in a Neural Mass Model
% A Weigenand, M Schellenberger Costa, H-VV Ngo, JC Claussen, T Martinetz
% PLoS Computational Biology. 2014;10:e1003923

% Path to utility functions
if(isempty(strfind(path, [pwd, '/Tools'])))
    addpath([pwd, '/Tools']);
end

% Option array for set
Plot_Opts_Name = { 'YLim';
                   'YTick';
                   'XLim';
                   'XTick'}';
Plot_Opts_Data = { [-80,-40];
		   [-70 -50];
		   [0,5];	
		   []}';
Line_Opts_Name = { 'Color';
		   'LineStyle';
		   'LineWidth'}';
Line_Opts_Data = { [0.7,0.7,0.7];
		   '--';
		   1}';

% Create figure
figure(1);
clf, shg

% Create panel
p = panel('no-manage-font');
p.pack(1,3);

% set margins
p.de.marginbottom = 10;
p.de.margintop    = 10;
p.de.marginleft   = 10;
p.de.marginright  = 10;

% plot the data
p(1).select();
plotxppaut('Data/A-diagram.dat','Black','--');

% Set plot options
set(gca, Plot_Opts_Name, Plot_Opts_Data, 'YTick', 0:5);

% Add the vertical lines
plot([1.378,1.378]  , ylim, Line_Opts_Name, Line_Opts_Data);
plot([0.6643,0.6643], ylim, Line_Opts_Name, Line_Opts_Data);
plot([3.352,3.352]  , ylim, Line_Opts_Name, Line_Opts_Data);

% Label the regions
text(0.07,-41.7,'I');
text(0.85,-41.7,'V');
text(2.2,-41.7,'VI');
text(4,-41.7,'IV');

% Label the axes
title('(a) High gain, \sigma_{e} = 3 mV');
ylabel('V_{e} [mV]');
xlabel('g_{KNa} [mS/cm^2]');

% Plot the data
p(2).select();
plotxppaut('Data/B-diagram.dat','Black','--')

% Set plot options
set(gca, Plot_Opts_Name, Plot_Opts_Data);

% Add the vertical lines
plot([1.702,1.702], Line_Opts_Name, Line_Opts_Data);
plot([3.352,3.352], Line_Opts_Name, Line_Opts_Data);
plot([4.01,4.01]  , Line_Opts_Name, Line_Opts_Data);

% Label the regions
text(0.7,-41.7,'I');
text(2.4,-41.7,'III');
text(3.5,-41.7,'VI');
text(4.3,-41.7,'IV');

% Label the axes
title('(b) Medium gain, \sigma_{e} = 5 mV')
xlabel('g_{KNa} [mS/cm^2]')

% Plot the data
p(3).select();
plotxppaut('Data/C-diagram.dat','Black','--')

% Set plot options
set(gca, Plot_Opts_Name, Plot_Opts_Data, 'XLim', [0, 10], 'XTick', 0:2:10,);

% Add the vertical lines
plot([3.688,3.688], Line_Opts_Name, Line_Opts_Data);
plot([7.877,7.877], Line_Opts_Name, Line_Opts_Data);

% Label the regions
text(0.8,-41.7,'I')
text(5.5,-41.7,'II')
text(9,-41.7,'IV')

% Label the axes
title('(c) Low gain, \sigma_{e} = 9 mV')
xlabel('$g_{KNa} [mS/cm^2]')

end
