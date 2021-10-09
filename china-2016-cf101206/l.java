import java.io.*;
import java.util.*;

public class l {
  public static void main(String[] args) throws Exception {
    final int one = 60*60;
    final int two = 2*60*60;
    final int three = 3*60*60;
    Scanner sc = new Scanner(System.in);
    int n = sc.nextInt();
    for (int i=0; i<n; i++) {
      System.out.printf("Case #%d: ", i+1);
      String[] date = sc.next().split("-");
      String[] time = sc.next().split(":");
      int year = Integer.parseInt(date[0]);
      int month = Integer.parseInt(date[1]);
      int day = Integer.parseInt(date[2]);
      int minutes = Integer.parseInt(time[0])*60*60 + Integer.parseInt(time[1])*60 + Integer.parseInt(time[2]);
      Calendar calendar = new GregorianCalendar();
      calendar.set(year, month-1, day);
      //System.err.println(calendar.get(Calendar.YEAR) + " " + calendar.get(Calendar.MONTH) + " " + calendar.get(Calendar.DAY_OF_MONTH) + " " + calendar.get(Calendar.DAY_OF_WEEK) + " " + Calendar.SUNDAY + " " + Calendar.THURSDAY);
      //assert calendar.isSet(Calendar.DAY_OF_WEEK);

      int dayofweek = calendar.get(calendar.DAY_OF_WEEK);
      int sundays = getSundays(dayofweek, day);
      //System.err.println(calendar.SUNDAY + " : " + dayofweek + " " + sundays + " " + minutes);
      if (month == 3) {
        if (dayofweek != calendar.SUNDAY) {
          if (sundays < 2) {
            System.out.println("PST");
          } else {
            System.out.println("PDT");
          }
        } else {
          if (sundays < 2) {
            System.out.println("PST");
          } else if (sundays > 2) {
            System.out.println("PDT");
          } else {
            if (minutes < two) {
              System.out.println("PST");
            } else if (minutes < three) {
              System.out.println("Neither");
            } else {
              System.out.println("PDT");
            }
          }
        }
      } else if (month == 11) {
        if (dayofweek != calendar.SUNDAY) {
          if (sundays < 1) {
            System.out.println("PDT");
          } else {
            System.out.println("PST");
          }
        } else {
          if (sundays < 1) {
            System.out.println("PDT");
          } else if (sundays > 1) {
            System.out.println("PST");
          } else {
            if (minutes < one) {
              System.out.println("PDT");
            } else if (minutes < two) {
              System.out.println("Both");
            } else {
              System.out.println("PST");
            }
          }
        }
      } else {
        if (month > 3 && month < 11) {
          System.out.println("PDT");
        } else {
          System.out.println("PST");
        }
      }
    }
  }

  static int getSundays(int dayofweek, int day) {
    day -= dayofweek-1;
    if (day <= 0) return 0;
    else return (day-1)/7 + 1;
  }
}
