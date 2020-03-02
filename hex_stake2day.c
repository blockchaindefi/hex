/**
 * This i use to ReStake your Hex to use the bigger pays better bonus
 *
 * This is Copyright under the GNU General Public License
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define A_DAY_IN_SEC (60*60*24)

static int getDayFromStart()
{
	struct tm SetTime = {
	.tm_sec  =  59,
	.tm_min  =  59,
	.tm_hour =  23,
	.tm_mday =   2,
	.tm_mon  =  12 - 1,
	.tm_year =  2019 - 1900
	};
	time_t FromTime = mktime(&SetTime);
	return (difftime(time(NULL), FromTime)+(A_DAY_IN_SEC - 1)) / A_DAY_IN_SEC;
}

static const char *release_date2str(int release_date, char *str, size_t str_size)
{
	time_t mytime = time(NULL) + (A_DAY_IN_SEC * release_date);
	strftime(str, str_size, "%F", localtime(&mytime));
	return str;
}

int main(int argc, char *argv[])
{
	char timestr[64] = "";
	int days = getDayFromStart();

	for (int i = 1; i < argc; ++i)
	{
		int release_date = atoi(argv[i]) - days;
		release_date2str(release_date, timestr, sizeof(timestr));
		printf("Lock for  %4d  days.  The release date is: %s\n", release_date - 1, timestr);
	}

	if('\0' == *timestr)
		printf("NO ARG, days since HEX started: %d    (%s)\n", days, release_date2str(0 - days, timestr, sizeof(timestr)));
	return EXIT_SUCCESS;
}
