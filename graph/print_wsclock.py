import seaborn as sns
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

sns.set_theme(style="darkgrid")
df = pd.read_csv("graph/wsclock.csv")
img = sns.pointplot(x = 'frames', y = 'hit-ratio',data = df,color="blue")
img.set(title ='WS Clock')
plt.savefig('graph/wsclock.png')