def power_exponent(base, exponent):
    result = 1
    for i in range(exponent):
        result *= base
    return result

for i in range(1, 11):
    if power_exponent(14,i) -power_exponent(13,i)==27:
        print(f"14^{i} - 13^{i} = 27")
    else:
        print('none')