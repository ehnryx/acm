import java.io.*;
import java.util.*;
import java.text.*;

public class f {
	public static void main(String[] args) throws Exception {
		Scanner in = new Scanner(System.in);
		while (in.hasNext()) {
			String s = in.next();
			Date julian = new SimpleDateFormat("yyyy-MM-dd").parse(s);
			GregorianCalendar greg = new GregorianCalendar();
			greg.setGregorianChange
			System.out.println(julian);
		}
	}
}
