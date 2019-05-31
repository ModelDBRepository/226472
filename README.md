# NM_Cortex

This repository contains the reference implementation of the model proposed in Weigenand and Schellenberger Costa et al. 2014, 
available here http://journals.plos.org/ploscompbiol/article?id=10.1371/journal.pcbi.1003923

For convenience we utilize MATLAB for data processing and plotting. Therefore the simulation comes with an additional source-file
Cortex_mex.cpp that can be compiled within MATLAB to utilize their C++-mex interface. The easiest way to reproduce the figures
in the paper is to simply run the Create_Data() function within MATLAB, assuming the mex interface is setup.

Afterwards simply run the respective plot functions for the different figures. Please note that due to the stochastic nature of the
simulation the time series will differ.
