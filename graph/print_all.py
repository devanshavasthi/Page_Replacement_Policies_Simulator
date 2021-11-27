import seaborn as sns
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# sns.set_theme(style="darkgrid")
plt_1 = plt.figure(figsize=(18, 12))
df = pd.read_csv("graph/all.csv")
img = sns.pointplot(x='frames', y='hit-ratio', data=df,
                    palette='Accent', hue="policy")
img.set(title='Policies')
plt.savefig('graph/policy.png')
