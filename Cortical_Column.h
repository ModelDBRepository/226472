/*
 *	Copyright (c) 2015 University of Lübeck
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
/*						Implementation of a cortical module					  */
/******************************************************************************/
#pragma once
#include <cmath>
#include <vector>

#include "Random_Stream.h"

class Cortical_Column {
public:
    Cortical_Column(double* Par)
    : sigma_p (Par[0]), g_KNa (Par[1]), dphi (Par[2]) {set_RNG();}

    void	set_input	(double I) {input = I;}
    void	iterate_ODE	(void);
private:
    void 	set_RNG		(void);

    /* Firing rates */
    double 	get_Qp		(int) const;
    double 	get_Qi		(int) const;

    /* Currents */
    double 	I_ep		(int) const;
    double 	I_ei		(int) const;
    double 	I_gp		(int) const;
    double 	I_gi		(int) const;
    double 	I_L_p		(int) const;
    double 	I_L_i		(int) const;
    double 	I_KNa		(int) const;

    /* Potassium pump */
    double 	Na_pump		(int) const;

    /* Noise function */
    double 	noise_xRK 	(int, int) const;
    double 	noise_aRK 	(int) const;

    /* ODE functions */
    void 	set_RK		(int);
    void 	add_RK	 	(void);

    /* Helper functions */
    inline std::vector<double> init (double value)
    {return {value, 0.0, 0.0, 0.0, 0.0};}

    inline void add_RK (std::vector<double>& var)
    {var[0] = (-3*var[0] + 2*var[1] + 4*var[2] + 2*var[3] + var[4])/6;}

    inline void add_RK_noise (std::vector<double>& var, unsigned noise)
    {var[0] = (-3*var[0] + 2*var[1] + 4*var[2] + 2*var[3] + var[4])/6 + noise_aRK(noise);}

    /* Random number generators */
    std::vector<randomStreamNormal> MTRands;

    /* Container for noise */
    std::vector<double>	Rand_vars;

    /* Declaration and Initialization of parameters */
    /* Membrane time in ms */
    const double 	tau_p 		= 30;
    const double 	tau_i 		= 30;

    /* Maximum firing rate in ms^-1 */
    const double 	Qp_max		= 30.E-3;
    const double 	Qi_max		= 60.E-3;

    /* Sigmoid threshold in mV */
    const double 	theta_p		= -58.5;
    const double 	theta_i		= -58.5;

    /* Sigmoid gain in mV */
    const double 	sigma_p		= 4;
    const double 	sigma_i		= 6;

    /* Scaling parameter for sigmoidal mapping (dimensionless) */
    const double 	C1		= (3.14159265/sqrt(3));

    /* Parameters of the firing adaption */
    const double 	alpha_Na	= 2.;			/* Sodium influx per spike  in mM ms 	*/
    const double 	tau_Na		= 1.;			/* Sodium time constant	    in ms 	*/

    const double 	R_pump   	= 0.09;        	/* Na-K pump constant	    in mM/ms 	*/
    const double 	Na_eq    	= 9.5;         	/* Na-eq concentration	    in mM 	*/

    /* PSP rise time in ms^-1 */
    const double 	gamma_e		= 70E-3;
    const double 	gamma_g		= 58.6E-3;

    /* Conductivities */
    /* Leak  in aU*/
    const double 	g_L    		= 1.;

    /* Synaptic conductivity in ms */
    const double 	g_AMPA 		= 1.;
    const double 	g_GABA 		= 1.;

    /* KNa in mS/cm^-2 */
    const double	g_KNa		= 1.33;

    /* Reversal potentials in mV */
    /* Synaptic */
    const double 	E_AMPA  	= 0;
    const double 	E_GABA  	= -70;

    /* Leak */
    const double 	E_L_p 		= -66;
    const double 	E_L_i 		= -64;

    /* Potassium */
    const double 	E_K    		= -100;

    /* Noise parameters in ms^-1 */
    const double 	mphi		= 0.0;
    const double	dphi		= 20E-1;
    double			input		= 0.0;

    /* Connectivities (dimensionless) */
    const double 	N_pp		= 120;
    const double 	N_ip		= 72;
    const double 	N_pi		= 90;
    const double 	N_ii		= 90;

    /* Interation parameters for SRK4 */
    const std::vector<double> A = {0.5, 0.5, 1.0, 1.0};
    const std::vector<double> B = {0.75, 0.75, 0.0, 0.0};

    /* Population variables */
    std::vector<double> Vp	= init(E_L_p), /* excitatory membrane voltage						*/
                        Vi	= init(E_L_i),	/* inhibitory membrane voltage						*/
                        Na	= init(Na_eq),	/* Na concentration									*/
                        s_ep= init(0.0),	/* PostSP from excitatory to excitatory population	*/
                        s_ei= init(0.0),	/* PostSP from excitatory to inhibitory population	*/
                        s_gp= init(0.0),	/* PostSP from inhibitory to excitatory population	*/
                        s_gi= init(0.0),	/* PostSP from inhibitory to inhibitory population	*/
                        x_ep= init(0.0),	/* derivative of s_ep								*/
                        x_ei= init(0.0),	/* derivative of s_ei								*/
                        x_gp= init(0.0),	/* derivative of s_gp				 				*/
                        x_gi= init(0.0);	/* derivative of s_gi	 							*/
    /* Data storage  access */
    friend void get_data (unsigned, Cortical_Column&, std::vector<double*>);

    /* Stimulation protocol access */
    friend class Stim;
};
