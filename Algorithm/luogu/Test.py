def binary_decimal_conversion(binary_fraction):  
    decimal_fraction = 0  
    base = 0.5  # 2的负一次方，即0.5  
    for digit in binary_fraction:  
        if digit == '1':  
            decimal_fraction += base  
        base /= 2  # 下一位的权重是前一位的一半  
    return decimal_fraction  
  
# 示例：将二进制小数0.1转换为十进制  
binary_fraction = '0.11111101'  
decimal_fraction = binary_decimal_conversion(binary_fraction)  
print(f"Decimal fraction: {decimal_fraction}")