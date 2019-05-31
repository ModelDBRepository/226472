function Plot_Bifurcation_2D()
% This function creates Figure 2 of
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
Plot_Opts_Data = { [0.1, 10.5];
		   2:2:10;
		   [0,8.2];	
		   2:2:8}';
Line_Opts_Name = { 'Color';
		   'LineStyle';
		   'LineWidth'}';
Line_Opts_Data = { [0.7,0.7,0.7];
		   '--';
		   1}';

% Create the figure
figure(1)
clf, shg

% Plot the data
plotxppaut('Data/Hopf-diagram.dat','Red','-')
plotxppaut('Data/Saddle-diagram.dat','Black','-')
xlim([0,8.2])
ylim([0.1,10.5])

% Add the vertical lines
plot(xlim,[6.195,6.195], Line_Opts_Name, Line_Opts_Data)
plot(xlim,[3.617,3.617], Line_Opts_Name, Line_Opts_Data)

% Label the regions
text(0.5,5,'I')
text(3.3,7,'II')
text(2.5,5.5,'III')
text(7,5,'IV')
text(0.5,2,'V')
text(3,4.2,'VI')

% Label the axes
ylabel('\sigma_{e} [mV]')
xlabel('g_{KNa} [mS/cm^2]')

% Add the curve for sleep/wake transition
x_marker  = [0.0, 1.33, 2];
y_marker  = [3.8, 4.5, 6.7];

% Interpolate
x1 = linspace(x_marker(1), x_marker(3), 200);
y1 = interp1(x_marker,y_marker, x1, 'pchip'); 

% Plot the line
plot(x_marker, y_marker, 'o', 'color', colormap(summer(1)));
plot(x1, y1, 'color', colormap(summer(1)));

% Add the labels to the line
text( 0.1, 4.2,'wake')
text( 1.2, 5,'N2')
text( 1.9, 7.1,'N3')
end
