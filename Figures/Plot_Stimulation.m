function Plot_Stimulation()
% This function creates Figure 4 of
%
% Characterization of K-Complexes and Slow Wave Activity in a Neural Mass Model
% A Weigenand, M Schellenberger Costa, H-VV Ngo, JC Claussen, T Martinetz
% PLoS Computational Biology. 2014;10:e1003923
% Load the data

% Path to utility functions
if(isempty(strfind(path, [pwd, '/Tools'])))
    addpath([pwd, '/Tools']);
end

load('Data/Stimulation.mat', 'Ve_N2', 'Ve_N3');

% Number of runs for stimulation, as well as color set            
N 	    = 15;
ColorSet    = colormap(jet(N));

% Time of the stimulation
T           = 4;
t_stim_N2   = linspace(-1,T-1,T*100);
t_stim_N3   = linspace(3,T+3,T*100);

% generate a stimulus reference
Stimulus    =@(t) 2*(heaviside(t) - heaviside(t-0.05)) + 2*(heaviside(t-4) - heaviside(t-4.05))-40;

% create figure handle
figure(1)
clf,shg
hold on

for i=1:N 
    plot(t_stim_N2, Ve_N2{i}, 'Color', ColorSet(i,:));
    plot(t_stim_N3, Ve_N3{i}, 'Color', ColorSet(i,:));
end

% create the labels
set(gca,'YTick',[-80,-70,-60,-50,-40,-30]);
set(gca,'XTick',[-1, 0, 1, 2, 4, 5, 6, 7]);
set(gca,'XTickLabel',[-1, 0, 1, 2, 0, 1, 2, 3]);
ylim([-80,-30]);    
xlabel('Time [s]');
ylabel('$V_{e}$ [mV]')

% plot the stimulus reference
plot(t_stim_N2, Stimulus(t_stim_N2),'Color',[0.7,0.7,0.7],'LineWidth',1)
plot(t_stim_N3, Stimulus(t_stim_N3),'Color',[0.7,0.7,0.7],'LineWidth',1)

% plot the separating line
plot([3,3],[-80,-30],'-','Color','Black','LineWidth',0.5)

% label the stimulus and the KC peaks
text(-0.9,-31.5,'(a)')
text( 3.1,-31.5,'(b)')
text(-0.5,-35,'Stimulus')
text(0.0,-45,'P200')
text(0.4,-77.5,'N550')
text(1.1,-42.5,'P900')
hold off
end
