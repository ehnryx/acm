import java.io.*;
import java.util.*;
import java.math.*;
import java.text.*;

public class main {
	static BigDecimal zero = new BigDecimal(0);
	static BigDecimal one = new BigDecimal(1);
	static BigDecimal two = new BigDecimal(2);
	static BigDecimal three = new BigDecimal(3);
	static BigDecimal four = new BigDecimal(4);
	static BigDecimal half = one.divide(two);

	static public void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		PrintWriter out = new PrintWriter(System.out);

		long num = sc.nextLong();
		BigDecimal a = new BigDecimal(num);

		BigDecimal l = get_left(a);
		BigDecimal m = get_middle(a);
		BigDecimal r = get_right(a);

		BigDecimal top = linear(r).subtract(linear(l));
		BigDecimal left = root(a, m).subtract(root(a, l));
		BigDecimal right = quadratic(a, r).subtract(quadratic(a, m));

		BigDecimal area = top.subtract(left).subtract(right);
		String ans = new DecimalFormat("0.0000000000").format(
				area.multiply(two).setScale(10, RoundingMode.HALF_UP));
		out.println(ans);

		out.close();
	}

	static BigDecimal linear(BigDecimal x) {
		return x.multiply(x).divide(two);
	}

	static BigDecimal root(BigDecimal a, BigDecimal x) {
		return a.multiply(x).subtract(
				square_root(x.multiply(x).multiply(x))
				.multiply(two).divide(three, 100, RoundingMode.HALF_EVEN));
	}

	static BigDecimal quadratic(BigDecimal a, BigDecimal x) {
		BigDecimal y = x.subtract(a);
		return y.multiply(y).multiply(y).divide(three, 100, RoundingMode.HALF_EVEN);
	}

	static BigDecimal square_root(BigDecimal x) {
		BigDecimal l = zero;
		BigDecimal r = x;
		if (r.compareTo(one) < 0) {
			r = one;
		}
		for (int bs = 0; bs < 420; bs++) {
			BigDecimal m = l.add(r).divide(two);
			if (m.multiply(m).compareTo(x) < 0) {
				l = m;
			} else {
				r = m;
			}
		}
		return r;
	}

	static BigDecimal get_left(BigDecimal a) {
		return two.multiply(a).add(one)
			.subtract(square_root(four.multiply(a).add(one)))
			.divide(two);
	}

	static BigDecimal get_right(BigDecimal a) {
		return two.multiply(a).add(one)
			.add(square_root(four.multiply(a).add(one)))
			.divide(two);
	}

	static BigDecimal get_middle(BigDecimal a) {
		BigDecimal l = a;
		BigDecimal r = a.multiply(two);
		for (int bs = 0; bs < 420; bs++) {
			BigDecimal x = l.add(r).divide(two);
			BigDecimal d = x.subtract(a);
			BigDecimal left = a.subtract(d.multiply(d));
			if (left.compareTo(zero) > 0 && left.multiply(left).compareTo(x) > 0) {
				l = x;
			} else {
				r = x;
			}
		}
		return r;
	}

};

