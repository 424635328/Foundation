def ismultiplicand(n, m):
    if n % m == 0:
        return True
    else:
        return False
a=0
b=10
for i in range(1,b):
    if ismultiplicand(i, 3):
        a+=1
    elif ismultiplicand(i, 2):
        continue
    else:
        continue
print(a/b)