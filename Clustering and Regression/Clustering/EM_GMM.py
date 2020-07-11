import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import sys
import seaborn as sns

X = np.random.rand(1000,5)

def Normal(x,mu,sigma):
  if np.linalg.det(sigma) == 0 :
    print("SINGULAR ERROR\n")
    print(sigma)
    #sys.exit()
  n = len(x)
  k = 1/((np.float_power(2*np.pi,(n/2)))*np.sqrt(abs(np.linalg.det(sigma))))
  pow = np.matmul((x-mu).transpose(), np.matmul(np.linalg.inv(sigma),(x-mu)))
  return k*(np.exp(-0.5*pow))

  def EM_Algo(x,k,delta):

  col = x.shape[1]
  #intialize mu, sigma, pi
  mu = np.random.randn(k,col)
  #sigma = abs(np.random.randn(k,col,col))
  sigma = abs(np.array([p*np.eye(col) for p in np.random.randn(k)]))
  pi = np.random.randn(k)
  err = delta + 1

  # Making Cov matrix Invertible
  for i in range(k):
    det = np.linalg.det(sigma[i])
    #print(det)
    while det==0:
      sigma[i] += 0.01*eye(col)
      det = np.linalg.det(sigma[i])
      #print(det)

  # Calculate log likelihood
  loghood_old = logHood(x,mu,pi,sigma)

  epoch = 1
  while(err > delta):
    print("Epoch No -> ",epoch)
    # Update Step
    for j in range(k):
      print("   Column No : ",j)
      # mu update
      num_mu = np.zeros(mu[0].shape)
      for t in x: num_mu+= Gamma(pi, mu, sigma, t, j)*t
      den = 0
      for t in x: den+= Gamma(pi, mu, sigma, t, j)

      # Sigma Update
      num_sig = np.zeros(sigma[0].shape)
      for t in x: num_sig+= Gamma(pi, mu, sigma, t, j)*np.matmul((t-mu[j]),(t-mu[j].transpose()))

      # Making Cov matrix Invertible
    for i in range(k):
      det = np.linalg.det(sigma[i])
      #print(det)
      while det==0:
        sigma[i] += 0.01*np.eye(col)
        det = np.linalg.det(sigma[i])
        #print(det)
      
      # Pi Update
      pi[j] = (1/(len(x)))*den
      sigma[j] = num_sig/den
      mu[j] = num_mu/den

    # Making Cov matrix Invertible
    for i in range(k):
      det = np.linalg.det(sigma[i])
      #print(det)
      while det==0:
        sigma[i] += 0.01*np.eye(col)
        det = np.linalg.det(sigma[i])
        #print(det)

    loghood_new = logHood(x,mu,pi,sigma)
    err = loghood_new - loghood_old
    loghood_old = loghood_new
    epoch+=1
  
  return mu, sigma, pi

def Gamma(pi, mu, sigma, x, j):
  num = pi[j]*Normal(x, mu[j], sigma[j])
  den = 0
  for k in range(len(pi)): den += pi[k]*Normal(x, mu[k], sigma[k])
  #print("Num = ",num," Den = ",den)
  return (num/den)


def logHood(X, mu, pi, sigma):
  loghood = 0
  for train in X:
    joint_distrn = 0
    for j in range(len(mu)):
      joint_distrn += pi[j]*Normal(train,mu[j],sigma[j])
    loghood += np.log(joint_distrn)
  return loghood

  EM_Algo(X, 3, 0.000000000001)
