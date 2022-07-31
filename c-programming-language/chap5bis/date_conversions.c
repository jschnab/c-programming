#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day) {
    int i, leap;
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    for (i = 1; i < month; ++i) {
        day += *(*daytab + 13 * leap + i);
    }
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    leap = (year % 4 == 0 && year % 100 != 0) || year % 400 ==0;
    for (i = 1; yearday > daytab[leap][i]; ++i) {
        yearday -= *(*daytab + 13 * leap + i);
    }
    *pmonth = i;
    *pday = yearday;
}

char *month_name(int n) {
    static char *name[] = {
        "Illegal month",
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };
    return (n < 1 || n > 12) ? name[0] : name[n];
}

int main() {
    printf("20th May 1986 is day %d of the year\n", day_of_year(1986, 5, 20));
    int month, day;
    month_day(2022, 69, &month, &day);
    printf("69th day is %d/%d\n", month, day);
    printf("Month 5 is %s\n", month_name(5));
    return 0;
}
