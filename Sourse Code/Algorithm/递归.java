public class Demo6 {

	public static void main(String[] args) {
				System.out.println(fact(5));
	}	
	/**
	 * 求n的阶乘f1（n) 求n的阶乘--->fact（n-1）求n-1的阶乘
	 * 1.找重复(规模更小）；n*(n-1)的阶乘，求n-1的阶乘是原问题的重复（规模更小）——子问题
	 * 2.找变化；变化的量应作为参数
	 * 3.找边界；出口
	 */
	public static int fact(int n) {
		if(n == 1) {
			return n = 1;
		}else {
			return n*fact(n-1);
		}
	}
}