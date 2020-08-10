/**
 * This i use to calculates how much X amount increases in Y days, on a Z year(365 days) base interest rate
 *
 * This code is Copyright 2020 under the GNU General Public License
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>
#include <unistd.h>

#define CONVERT_PROCENT2DECIMAL(x) ((x) * 0.01)
#define CONVERT_DECIMAL2PROCENT(x) ((x) * 100.0)

#define HEX_ANNUAL_INFLATION  3.69

// This is the % I think will be reasonable as defult future stake level   ¯\_(ツ)_/¯
#define HEX_DEFULT_STAKING_LEVEL 60.0
#define HEX_DEFULT_INTEREST (CONVERT_PROCENT2DECIMAL(HEX_ANNUAL_INFLATION) / CONVERT_PROCENT2DECIMAL(HEX_DEFULT_STAKING_LEVEL))

int  opt_year_days = 365;
int opt_verbose = 0;

using namespace std;


static void print_help(const char *s = nullptr)
{
	cerr << " Count the percentage growth. The arg are:" << endl
		<< "  (There is otherwise a sloppy calculation of the increase of the percent depending on the amount added)" << endl
		<< " arg1  Number of days to stake." << endl
		<< " arg2  Value amount. You can use T M B (or t m b) as thousand, million and billion. All , and ' will be removed" << endl
		<< "Settings opt:" << endl
		<< " -p  Percentage /year  Default is: " << CONVERT_DECIMAL2PROCENT(HEX_DEFULT_INTEREST)
		<< "  That is based on that " << HEX_DEFULT_STAKING_LEVEL << " % of all Hex are staked" << endl
		<< " -t  The total Hex amont. Used to calculate the percentages, both this and -l must be used" << endl
		<< " -l  The lock  Hex amont. Used to calculate the percentages, both this and -t must be used" << endl
		<< " -d  Year days used in the percent calculation. Default value: " << opt_year_days << "  (Probably nothing you want to change)"<< endl
		<< " -v  Verbose = print more, can use twice for even more info" << endl
		<< " -h  This help" << endl
		<< endl
		<< "And of course these are just guesses!" << endl
		<< "Even with a perfect calculation, there is much else that affects the \"interest rate\" in Hex" << endl;

	if(s)
		cerr << "ERROR: " << s << endl;
}

static void print_help_exit(const char *s = nullptr)
{
	print_help(s);
	exit(0);
}

/**
 * 1,2^(1.0/365.0)
 * 10000×1,000499…^365
 */
class percentCalculation
{
public:
	explicit percentCalculation(double percent, double days = 365)
	: m_percent(percent)
	, m_days(days)
	{ }

	// 1,2^(1÷365)
	inline double getCountPercent(int counts = 1)
	{
		return pow(1.0 + m_percent, static_cast<double>(counts) / m_days);
	}

private:
	double m_percent;
	double m_days;
};

/**
 * This is a somewhat sloppy calculation of the increase of the percent depending on the amount
 *
 * To be scalable use:
 * bonus = (input * (min(input, 150e6)/1500e6)
 * From: https://medium.com/@jimmypomerleau/intro-d37b5b720487
 */
static double get_interest_from_amount(double amount)
{
	const double max_amount = std::min(amount,  150000000.0);
	const double bonus = amount * (max_amount / 1500000000.0);
	return (bonus / amount) + HEX_DEFULT_INTEREST;
}

static void add_number_separator(string &text)
{
	int pos = 0;
	for (; pos < text.size() && '.' != text[pos]; ++pos);

	for (int i = 0; pos ; --pos, ++i)
	{
		if(i && i%3 == 0)
			text.replace(pos, 0, string(","));
	}
}

static string add_number_separator(double value)
{
	stringstream stream;
	stream << std::fixed << std::setprecision(0) << value;
	string str(stream.str());
	add_number_separator(str);
	return str;
}


static void replace_string(string &text, const string& search, const string& replace)
{
	for (size_t pos = 0; (pos = text.find(search, pos)) != std::string::npos ;)
	{
		text.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

static void convert_value_str(string &value)
{
	static constexpr struct Convert
	{
		const char *from;
		const char *to;
	} conv[]= {
		{ "B", "000000000" },
		{ "b", "000000000" },
		{ "M", "000000" },
		{ "m", "000000" },
		{ "T", "000" },
		{ "t", "000" },
		{ ",", "" },
		{ "'", "" },
	};

	for (const Convert &a : conv)
		replace_string(value, a.from, a.to);
}

static void run(int argc, char *argv[])
{
	int option_char, days = 0;
	double amount = 10000;
	double percentage = HEX_DEFULT_INTEREST;
	double hex_total = 0.0, hex_lock = 0.0;

	while((option_char = getopt(argc,argv,"ht:l:p:d:v")) != -1)
	{
		switch(option_char)
		{
		case 'h':
			print_help_exit();
		break;

		case 't':
			hex_total = stod(optarg);
		break;

		case 'l':
			hex_lock = stod(optarg);
		break;

		case 'p':
			percentage = CONVERT_PROCENT2DECIMAL(stod(optarg));
		break;

		case 'd':
			opt_year_days = atoi(optarg);
		break;

		case 'v':
			opt_verbose++;
		break;

		default:
			print_help_exit("Unknown option detected!\n");
		}
	}

	int arg_count = optind;

	if(HEX_DEFULT_INTEREST == percentage && hex_total && hex_lock) {
		if(hex_lock > hex_total)
			print_help_exit("Wrong total Hex  lock > total");
		percentage = CONVERT_PROCENT2DECIMAL(HEX_ANNUAL_INFLATION) / (hex_lock / hex_total);
		if(opt_verbose > 1) {
			cout << "Total Hex amont: " << setw(16) << add_number_separator(hex_total) << endl;
			cout << "Lock  Hex amont: " << setw(16) << add_number_separator(hex_lock) << endl;
		}
		if(opt_verbose)
			cout << "The amount of Hex staket: " << CONVERT_DECIMAL2PROCENT(hex_lock / hex_total) << " %   Calculate yearly \"interest\": " << CONVERT_DECIMAL2PROCENT(percentage) << " %" << endl;
	}

	if(arg_count >= argc) {
		print_help_exit("No arg");
	}

	days = stoi(argv[arg_count]);

	++arg_count;
	if(argc > arg_count) {
		string value(argv[arg_count]);
		convert_value_str(value);
		amount = stod(value);
	}

	if(0.0 == percentage)
		percentage = get_interest_from_amount(amount);

	percentCalculation calculat(percentage, opt_year_days);

	double calculated_amount = calculat.getCountPercent(days) * amount;
	cout << "For interest for " << days << " days at " << percentage << " % compound, new  amount: " << setw(12) << std::fixed << std::setprecision(2)
		<< add_number_separator(calculated_amount) << "  difference: " << add_number_separator(calculated_amount - amount) << endl
		<< std::setprecision(4) << " Increase by " << CONVERT_DECIMAL2PROCENT((calculated_amount / amount) - 1.0) << " %"
		<< "  (count back percent " << CONVERT_DECIMAL2PROCENT(1.0 - (amount / calculated_amount)) << " %)" << endl;
}

int main(int argc, char *argv[])
{
	int main_ret = EXIT_FAILURE;
	try
	{
		run(argc, argv);
		main_ret = EXIT_SUCCESS;
	} catch (const exception &e) {
		cerr << "Catch error  \"" << e.what() << "\"  - Sanitize your argument list I guess..?" << endl;
		return EXIT_FAILURE;
	} catch (int e) {
		main_ret = e;
		if(EXIT_FAILURE == e)
			cerr << "Catch error  exit" << endl;
	} catch (...) {
		cerr << "Catch error  Unknown error..?" << endl;
	}
	return main_ret;
}
