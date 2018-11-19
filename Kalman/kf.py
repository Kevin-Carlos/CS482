# kf.py updated file for robot estimation assignment
# pset[3]
# (C) 2017 David Feil-Seifer


import numpy as np
import math
from scipy import stats
import scipy.stats

# kf_update: update state estimate [u, sigma] with new control [xdot] and measurement [z]
# 	parameters:
#			u : 2x1 vector with state estimate (x) at time t-1 and control (xdot) at time t
#			sigma: 2x2 matrix with covariance at time t-1
#			z (int): observed (uncertain) measurement of state (x) at time t
#	returns: [u sigma] updated state with estimate at time t

def kf_update(u, sigma, z):
	F = np.matrix('1 1; 0 1')
	H = np.matrix('0 1')
	I = np.diag([1, 1])
	#u_of_t : Previous state
	#z_of_t : current measurement
	#Sigma_x : movement uncertainty : G * G^T * little_sigma^2_x. Should be [deltaT^2 ; deltaT / 2] --> G [ 1 ; 1/2 ]
	#Sigma_z : measurement uncertainty : little_sigma^2_z (std. deviation of measurement noise)

	#Sigma : location uncertainty

	#Calculate the Kalman gain
	Fsigma_t = np.multiply(F, sigma)
	Fsigma_tF_T = np.multiply(Fsigma_t, F.T)
	G = np.matrix([1; .5])
	GG_T = np.multiply(G, G.T)
	Sigma_x = GG_T
	K_tplus1 = (Fsigma_tF_T + )

	#location mean information
	Fmu_t = np.multiply(F, u)
	HF = np.multipy(H, F)
	HFmu_t = np.multiply(HF, u)

	mu_tplus1 = Fmu_t + K_tplus1(z_tplus1 - HFmu_t)

	print('u_tplus1 : {u_tplus1}\n'.format(u_tplus1=u_tplus1))
	print('sigma : {sigma}\n'.format(sigma=sigma))
	print('z : {z}\n'.format(z=z))

	return [u, sigma]


# door_update: update estimate of door locations
# 	parameters:
#			u : 2x1 vector with state estimate (x) at time t-1 and control (xdot) at time t-1
#			sigma: 2x2 matrix with covariance at time t-1
#			d (binary): door sensor at time t-1
#			door_dist (array of size 10): probability (0..1) that a door exists at each location (0..9)
#	returns: [door_dist] updated door distribution

def door_update(u, sigma, d, door_dist):
	return door_dist


















