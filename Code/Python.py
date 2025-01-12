import numpy as np
import matplotlib.pyplot as plt
from sklearn.linear_model import LinearRegression

X=np.array([6,8,19,22,25]).reshape(-1,1)

y=[7,9,20,25,26]

regressor=LinearRegression()
regressor.fit(X,y)

# print(regressor.predict([[30]]))
plt.scatter(X,y,color='red')
plt.plot(X,regressor.predict(X),color='blue')
plt.show()