/*
 *	Copyright (c) 2014 University of Lübeck
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy
 *	of this software and associated documentation files (the "Software"), to deal
 *	in the Software without restriction, including without limitation the rights
 *	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *	copies of the Software, and to permit persons to whom the Software is
 *	furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in
 *	all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *	THE SOFTWARE.
 *
 *	AUTHORS:	Michael Schellenberger Costa: mschellenbergercosta@gmail.com
 *
 *	Based on:	Characterization of K-Complexes and Slow Wave Activity in a Neural Mass Model
 *				A Weigenand, M Schellenberger Costa, H-VV Ngo, JC Claussen, T Martinetz
 *				PLoS Computational Biology. 2014;10:e1003923
 */

/******************************************************************************/
/* Implementation of the simulation as MATLAB routine (mex compiler)		  */
/* mex command is given by:													  */
/* mex CXXFLAGS="\$CXXFLAGS -std=c++11 -O3" Cortex_mex.cpp Cortical_Column.cpp*/
/******************************************************************************/
#include "mex.h"
#include "matrix.h"

#include <iterator>
#include <vector>

#include "Cortical_Column.h"
#include "Data_Storage.h"
#include "Stimulation.h"
mxArray* SetMexArray(int N, int M);
mxArray* get_marker(Stim &stim);

/******************************************************************************/
/*                          Fixed simulation settings						  */
/******************************************************************************/
extern const int onset	= 10;		/* Time until data is stored in  s		  */
extern const int res 	= 1E4;		/* Number of iteration steps per s		  */
extern const int red 	= 1E2;		/* Number of iterations steps not saved	  */
extern const double dt 	= 1E3/res;	/* Duration of a time step in ms		  */
extern const double h	= sqrt(dt); /* Square root of dt for SRK iteration	  */

/******************************************************************************/
/*                              Simulation routine	 						  */
/*								lhs defines outputs							  */
/*								rhs defines inputs							  */
/******************************************************************************/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    /* Set the seed */
    srand(time(NULL));

    /* Fetch inputs */
    const int T				= (int) (mxGetScalar(prhs[0]));	/* Duration of simulation in s 			*/
    const int Time 			= (T+onset)*res;				/* Total number of iteration steps 		*/
    double* Param_Cortex	= mxGetPr (prhs[1]);			/* Parameters of cortical module 		*/
    double* var_stim	 	= mxGetPr (prhs[2]);			/* Parameters of stimulation protocol 	*/

    /* Initialize the population */
    Cortical_Column Cortex(Param_Cortex);

    /* Initialize the stimulation protocol */
    Stim Stimulation(Cortex, var_stim);

    /* Data container in MATLAB format */
    std::vector<mxArray*> dataArray;
    dataArray.reserve(6);
    dataArray.push_back(SetMexArray(1, T*res/red));	// Vp
    dataArray.push_back(SetMexArray(1, T*res/red));	// Na
    dataArray.push_back(SetMexArray(1, T*res/red));	// s_ep
    dataArray.push_back(SetMexArray(1, T*res/red));	// s_ei
    dataArray.push_back(SetMexArray(1, T*res/red));	// s_gp
    dataArray.push_back(SetMexArray(1, T*res/red));	// s_gi

    /* Pointer to the data blocks */
    std::vector<double*> dataPointer;
    dataPointer.reserve(dataArray.size());
    for (auto &dataptr : dataArray) {
        dataPointer.push_back(mxGetPr(dataptr));
    }

    /* Simulation */
    int count = 0;
    for (unsigned t=0; t < Time; ++t) {
        Cortex.iterate_ODE();
        Stimulation.check_stim(t);
        if(t >= onset*res && t%red == 0){
            get_data(count, Cortex, dataPointer);
            ++count;
        }
    }

    /* Return the data containers */
    nlhs = dataArray.size()+1;
    for (auto &dataptr : dataArray) {
        plhs[std::distance(&dataptr, dataArray.data())] = dataptr;
    }
    plhs[dataArray.size()] = get_marker(Stimulation);
    return;
}

/******************************************************************************/
/*                          Create MATLAB data containers					  */
/******************************************************************************/
mxArray* SetMexArray(int N, int M) {
    mxArray* Array	= mxCreateDoubleMatrix(0, 0, mxREAL);
    mxSetM(Array, N);
    mxSetN(Array, M);
    mxSetData(Array, mxMalloc(sizeof(double)*M*N));
    return Array;
}

mxArray* get_marker(Stim &stim) {
    extern const int red;
    mxArray* marker	= mxCreateDoubleMatrix(0, 0, mxREAL);
    mxSetM(marker, 1);
    mxSetN(marker, stim.marker_stimulation.size());
    mxSetData(marker, mxMalloc(sizeof(double)*stim.marker_stimulation.size()));
    double* Pr_Marker = mxGetPr(marker);
    unsigned counter  = 0;
    /* Division by res transforms marker time from dt to sampling rate */
    for(auto & elem : stim.marker_stimulation) {
        Pr_Marker[counter++] = elem/red;
    }
    return marker;
}
