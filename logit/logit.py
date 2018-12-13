# hasthags indicate notes about code; the code below imports a few packages we will need for this analysis
import pandas as pd
import statsmodels.api as sm
import pylab as pl
import numpy as np
import sys

# read the data in
sys.stderr.write("Reading: "+sys.argv[1])
df = pd.read_csv(sys.argv[1], sep=";")
  
print(df.columns)

print(df.describe())

print(df.std())

maxcol = df.columns.size

train_cols = df.columns[1:maxcol]

logit = sm.Logit(df['dep'], df[train_cols])

print(logit)

result = logit.fit()
me = res.get_margeff(at='mean').summary()

print(result)
print(result.summary())
print(me)

probit = sm.Probit(df['dep'], df[train_cols])

print(probit)

result = probit.fit()
print(result)
print(result.summary())


#print(df['dep'])
