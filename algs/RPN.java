import java.util.List;
import java.util.Stack;
import java.util.LinkedList;

public class RPN {
	public static double rpn_calc( List<String> ope ) throws IllegalArgumentException, ArithmeticException {
		Stack<Double> stack = new Stack<Double>();
		int size = ope.size();
		for( int i = 0; i < size; i++ ) {
			String c = ope.get(i);
			if( isNum(c) ) stack.push(new Double(c));
			else if( isOpe(c) ) {
				try {
					Double b = stack.pop();
					Double a = stack.pop();
					Double r = calc(a, b, c);
					stack.push(r);
				} catch( ArithmeticException e ) {
					throw e;
				} catch( Exception e ){
					throw new IllegalArgumentException();
				}
			}else{
				throw new IllegalArgumentException();
			}
		}
		return stack.pop().doubleValue();
	}

	public static boolean isNum( String s ) {
		try {
			Double.parseDouble(s);
		} catch(NumberFormatException e) {
			return false;
		}
		return true;
	}

	public static boolean isOpe( String s ) {
		switch(s) {
			case "+":
			case "-":
			case "*":
			case "/": return true;
		}
		return false;
	}

	public static Double calc( Double a, Double b, String c ) throws ArithmeticException{
		switch(c) {
			case "+": return new Double(a.doubleValue()+b.doubleValue());
			case "-": return new Double(a.doubleValue()-b.doubleValue());
			case "*": return new Double(a.doubleValue()*b.doubleValue());
			case "/": {
				if( b.doubleValue() == 0 ) throw new ArithmeticException();
				return new Double(a.doubleValue()/b.doubleValue());
			}
		}
		return 0.0;
	}

	public static void main( String[] argv ) {
		List<String> input = new LinkedList<String>();
		input.add("5");
		input.add("80");
		input.add("40");
		input.add("/");
		input.add("+");

		double result = rpn_calc(input);
		System.out.println(result);
	}
}
